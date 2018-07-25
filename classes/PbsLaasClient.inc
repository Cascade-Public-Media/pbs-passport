<?php

/**
 * @file
 * Class with methods for working with PBS's Login As A Service (LAAS)
 */

/**
 * Class PbsLaasClient
 *
 * This class was originally developed for WordPress by William Tam and Benny
 * Wong for WNET New York Public Media, with modifications from the Bear Group,
 * Inc.
 *
 * @url https://github.com/tamw-wnet/pbs-passport-authenticate
 * @url https://www.beargroup.com/
 * @url https://docs.pbs.org/display/MV/Custom+Implementation
 */
class PbsLaasClient {

  /**
   * @var string
   *   ID provided by PBS.
   */
  private $client_id;

  /**
   * @var string
   *   Secret key provided by PBS.
   */
  private $client_secret;

  /**
   * @var string
   *   Base URI of PBS endpoint.
   */
  private $oauthroot;

  /**
   * @var string
   *   Callback URI (most be registered with PBS).
   */
  private $redirect_uri;

  /**
   * PbsLaasClient constructor.
   *
   * @param array $args
   */
  public function __construct($args) {
    $this->client_id = $args['client_id'];
    $this->client_secret = $args['client_secret'];
    $this->oauthroot = $args['oauthroot'];
    $this->redirect_uri = $args['redirect_uri'];
    date_default_timezone_set('UTC');
  }

  /**
   * Get new access and refresh tokens.
   *
   * Takes an OAuth2 grant code and uses it to get access and refresh tokens
   * from PBS and then stores tokens and userinfo in Drupal session variable.
   *
   * @param $code
   *   OAuth2 grant code.
   *
   * @return array $tokeninfo
   *   An array of token info with messages or user info.
   */
  public function authenticate($code) {
    $token = $this->get_token($code);
    $this->update_token($token);
    $user = $this->get_user($token['access_token']);

    $_SESSION['pbs_passport']['token'] = $token;
    $_SESSION['pbs_passport']['user'] = $user;

    return $user;
  }

  /**
   * Verify the PBS authentication state.
   *
   * @return bool|array $user
   *   An array of user information or FALSE for unauthenticated users.
   */
  public function check_login() {
    $token = $_SESSION['pbs_passport']['token'];
    if (!$token) {
      return FALSE;
    }

    $this->update_token($token);
    if ($token['access_token'] != $_SESSION['pbs_passport']['token']['access_token']) {
      $_SESSION['pbs_passport']['token'] = $token;
    }

    $user = $this->get_user($token['access_token']);

    return $user;
  }

  /**
   * Get a token from PBS using a provided code.
   *
   * @param string $code
   *   Code provided by PBS OAuth2 endpoint.
   *
   * @return array|bool
   *   The access token data on success, false on error.
   */
  private function get_token($code='') {
    $data =[];
    $error = [];

    $response = drupal_http_request($this->oauthroot . 'token/', [
      'method' => 'POST',
      'headers' => ['Content-Type' => 'application/x-www-form-urlencoded'],
      'data' => drupal_http_build_query([
        'code' => $code,
        'redirect_uri' => $this->redirect_uri,
        'client_id' => $this->client_id,
        'client_secret' => $this->client_secret,
        'grant_type' => 'authorization_code'
      ])
    ]);

    if (isset($response->error)) {
      $error = [
        'type' => 'pbs_passport',
        'message' => 'Access token request failed. Error code: @code, message:
          @message, data: @data.',
        'variables' => [
          '@code' => $response->code,
          '@message' => $response->error,
          '@data' => $response->data
        ],
        'severity' => WATCHDOG_CRITICAL
      ];
    }
    else {
      $data = json_decode($response->data, TRUE);
      if (!isset($data['access_token'])) {
        $error = [
          'type' => 'pbs_passport',
          'message' => 'Access token missing from PBS code authentication response.
            Response: @data',
          'variables' => ['@data' => $response->data],
          'severity' => WATCHDOG_CRITICAL
        ];
      }
    }

    if (!empty($error)) {
      watchdog(
        $error['type'],
        $error['message'],
        $error['variables'],
        $error['severity']
      );
      return FALSE;
    }

    return $data;
  }

  /**
   * Generate an access token from a refresh token.
   *
   * @param array $token
   *   Current token data.
   *
   * @see update_pbs_tokeninfo()
   */
  public function generate_access_token_from_refresh_token(&$token) {
    $error = [];

    $response = drupal_http_request($this->oauthroot . 'token/', [
      'method' => 'POST',
      'headers' => ['Content-Type' => 'application/x-www-form-urlencoded'],
      'data' => drupal_http_build_query([
        'refresh_token' => $token['refresh_token'],
        'client_id' => $this->client_id,
        'client_secret' => $this->client_secret,
        'grant_type' => 'refresh_token'
      ])
    ]);

    if (isset($response->error)) {
      $error = [
        'type' => 'pbs_passport',
        'message' => 'Access token refresh failed. Error code: @code, message:
          @message, data: @data.',
        'variables' => [
          '@code' => $response->code,
          '@message' => $response->error,
          '@data' => $response->data
        ],
        'severity' => WATCHDOG_CRITICAL
      ];
    }
    else {
      $data = json_decode($response->data, TRUE);
      if (!isset($data['access_token'])) {
        $error = [
          'type' => 'pbs_passport',
          'message' => 'Access token missing from PBS code refresh response.
            Response: @data',
          'variables' => ['@data' => $response->data],
          'severity' => WATCHDOG_CRITICAL
        ];
      }
      elseif (isset($data['expires_in'])) {
        $token['expires_timestamp'] = strtotime(
          "+" . $data['expires_in'] . " seconds"
        );
      }
    }

    if (!empty($error)) {
      watchdog(
        $error['type'],
        $error['message'],
        $error['variables'],
        $error['severity']
      );
    }
  }

  /**
   * Update PBS access token data.
   *
   * Gets a new access token if the current token has less than 5% of its life
   * left. The default lifespan of a token is 10 hours.
   *
   * @param array $token
   *   Current token data.
   */
  private function update_token(&$token) {
    $token_expire_window = strtotime("+30 minute");
    if (isset($token['expires_in']) && ($token['expires_in'] < 36000)) {
      // In case PBS decides to give the access token a shorter lifespan, change
      // the expire window to 5% of that so a 1 hr lifespan has a 3 minute grace
      // period.
      $seconds = round($token['expires_in'] / 20);
      $token_expire_window = strtotime("+" . $seconds . " seconds");
    }

    // Refresh the access token if it is expired or will expire soon.
    if (isset($token['expires_timestamp'])
      && ($token['expires_timestamp'] < $token_expire_window)) {
      $this->generate_access_token_from_refresh_token($token);
    }

    // Calculate the expiration date and add to token.
    if (!isset($token['expires_timestamp'])) {
      $token['expires_timestamp'] = strtotime(
        "+" . $token['expires_in'] . " seconds"
      );
    }
  }

  /**
   * Get user info from PBS.
   *
   * @param string $access_token
   *
   * @return array
   *   PBS user info.
   */
  public function get_user($access_token = '') {
    $user = [];
    $error = [];

    $response = drupal_http_request($this->oauthroot . 'user/info/', [
      'method' => 'GET',
      'headers' => ['Authorization' => 'Bearer ' . $access_token]
    ]);

    if (isset($response->error)) {
      $error = [
        'type' => 'pbs_passport',
        'message' => 'PBS user info request failed. Error code: @code, message:
          @message, data: @data.',
        'variables' => [
          '@code' => $response->code,
          '@message' => $response->error,
          '@data' => $response->data
        ],
        'severity' => WATCHDOG_CRITICAL
      ];
    }
    else {
      $user = json_decode($response->data, TRUE);

      if (isset($user['email'])) {
        // Append the VPPA status.
        $this->derive_and_append_vppa_status($user);
      }
    }

    if (!empty($error)) {
      watchdog(
        $error['type'],
        $error['message'],
        $error['variables'],
        $error['severity']
      );
    }

    return $user;
  }

  /**
   * Get and append VPPA status to user info.
   *
   * @param array $user
   *   PBS user info.
   */
  public function derive_and_append_vppa_status(&$user) {
    $vppa_status = 'false';

    if (!empty($user['vppa']['vppa_last_updated'])) {
      $vppa_status = 'valid';

      if (strtotime($user['vppa']['vppa_last_updated']) < strtotime('-2 years')) {
        $vppa_status = 'expired';
      }

      if ($user['vppa']['vppa_accepted'] !== TRUE) {
        $vppa_status = 'rejected';
      }
    }

    $user['vppa_status'] = $vppa_status;
  }
}
