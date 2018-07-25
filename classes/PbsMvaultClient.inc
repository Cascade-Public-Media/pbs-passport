<?php

/**
 * @file
 * Class with methods for working with PBS's Membership Vault (MVault) service.
 */

/**
 * Class PbsMvaultClient
 *
 * This class was originally developed by William Tam and Benny Wong for WNET
 * New York Public Media, with modifications from the Bear Group, Inc.
 *
 * @url https://github.com/tamw-wnet/pbs-passport-authenticate
 * @url https://www.beargroup.com/
 * @url https://docs.pbs.org/display/MV
 */
class PbsMvaultClient {

  /**
   * @var string
   *   Membership vault production base address.
   */
  const MVAULT_PROD = 'https://mvault.services.pbs.org/api/';

  /**
   * @var string
   *   Membership vault QA base address.
   */
  const MVAULT_QA = 'https://mvault-qa.services.pbs.org/api/';

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
   *   Station ID from PBS.
   */
  private $station_id;

  /**
   * @var string
   *   Base URI of PBS MVault endpoint.
   */
  private $uri;

  /**
   * @var string
   *   Combination of $client_id and $client_secret.
   */
  private $auth_string;

  /**
   * PbsMvaultClient constructor.
   *
   * @param string $client_id
   *   ID provided by PBS.
   *
   * @param string $client_secret
   *   Secret key provided by PBS.
   *
   * @param string $station_id
   *   The PBS member station ID.
   *
   * @param string $environment
   *   The enviornment to connect to. Should be 'qa' or 'prod' and will always
   *   default to 'qa'.
   */
  public function __construct($client_id = '', $client_secret = '', $station_id = '', $environment = 'qa') {
    $this->client_id = $client_id;
    $this->client_secret = $client_secret;
    $this->station_id = $station_id;
    $this->auth_string = base64_encode(
      $this->client_id . ":" . $this->client_secret
    );

    if ($environment == 'prod') {
      $this->uri = self::MVAULT_PROD . $this->station_id;
    }
    else {
      $this->uri = self::MVAULT_QA . $this->station_id;
    }

    date_default_timezone_set('UTC');
  }

  /**
   * Make a GET request to an MVault endpoint.
   *
   * @param string $endpoint
   *   The endpoint to hit.
   *
   * @return array|bool
   *   An array of response data or FALSE on error.
   */
  private function get_request($endpoint) {
    $data = [];
    $error = [];

    $response = drupal_http_request($this->uri . $endpoint, [
      'method' => 'GET',
      'headers' => ['Authorization' => 'Basic ' . $this->auth_string]
    ]);

    if (isset($response->error)) {
      $details = json_decode($response->data);

      // "No resource found" can be returned for a regular PBS account user
      // without a (Passport) membership.

      // Some endpoints provide "errors" for non-error results:
      $non_errors = array(
        'No resource found',
        'No memberships exist for this user'
      );
      if (isset($details->errors) && !in_array($details->errors, $non_errors)) {
        $error = [
          'type' => 'pbs_passport',
          'message' => 'MVault GET request failed. Endpoint: @endpoint, error
            code: @code, message: @message, data: @data.',
          'variables' => [
            '@endpoint' => $endpoint,
            '@code' => $response->code,
            '@message' => $response->error,
            '@data' => $response->data
          ],
          'severity' => WATCHDOG_CRITICAL
        ];
      }
    }
    else {
      $data = json_decode($response->data, TRUE);
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
   * Make a PATCH request to an MVault endpoint.
   *
   * @param string $endpoint
   *   The endpoint to hit.
   *
   * @param array $data
   *   Fields to include in the request.
   *
   * @return bool
   *   FALSE for any known errors, TRUE otherwise. PATCH does not return data.
   */
  private function patch_request($endpoint, $data) {
    $data = json_encode($data, JSON_UNESCAPED_UNICODE);
    $data_length = drupal_strlen($data);
    $error = [];

    $response = drupal_http_request($this->uri . $endpoint, [
      'method' => 'PATCH',
      'headers' => [
        'Authorization' => 'Basic ' . $this->auth_string,
        'Content-Type' => 'application/json',
        'Content-Length' => $data_length
      ],
      'data' => $data
    ]);

    if (isset($response->error)) {
      $error = [
        'type' => 'pbs_passport',
        'message' => 'MVault PATCH request failed. Endpoint: @endpoint, error
          code: @code, message: @message, data sent: @sent, data received: @received.',
        'variables' => [
          '@endpoint' => $endpoint,
          '@code' => $response->code,
          '@message' => $response->error,
          '@sent' => $data,
          '@received' => $response->data
        ],
        'severity' => WATCHDOG_CRITICAL
      ];
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

    return TRUE;
  }

  /**
   * Get membership info by membership ID.
   *
   * @param string $membership_id
   *
   * @return array
   *   An empty array is no membership data is found.
   *
   * @url https://docs.pbs.org/display/MV/Membership+Vault+API#MembershipVaultAPI-get
   */
  public function get_membership($membership_id) {
    $membership  = $this->get_request('/memberships/' . $membership_id . '/');
    if ($membership) {
      $this->_modify_membership_response_data($membership);
    }
    return $membership;
  }

  /**
   * Get membership info by UID.
   *
   * @param int $uid
   *
   * @return array
   *   An empty array is no membership data is found.
   *
   * @url https://docs.pbs.org/display/MV/Membership+Vault+API#MembershipVaultAPI-get
   */
  public function get_membership_by_uid($uid) {
    $data = $this->get_request('/memberships/filter/uid/' . $uid . '/');

    // This endpoint returns an array of arrays.
    if ($data) {
      $data = $data[0];
      $this->_modify_membership_response_data($data);
    }

    return $data;
  }

  /**
   * Get membership info by email address.
   *
   * @param string $email
   *
   * @return array
   *   An empty array is no membership data is found.
   *
   * @url https://docs.pbs.org/display/MV/Membership+Vault+API#MembershipVaultAPI-get
   */
  public function get_membership_by_email($email) {
    $data = $this->get_request('/memberships/filter/email/' . $email . '/');

    // This endpoint returns a different array of arrays than the others. It is
    // possible for it to return multiple memberships.
    if ($data) {
      $data = $data['objects'];

      foreach ($data as $idx => $info) {
        $this->_modify_membership_response_data($data[$idx]);
      }
    }

    return $data;
  }

  /**
   * Activate a membership.
   *
   * @param string $membership_id
   * @param int $uid
   * @param bool $check_is_active
   *
   * @return array|bool|mixed
   *
   * @url https://docs.pbs.org/display/MV/Technical+Deep+Dive%3A+how+%27activation%27+works
   */
  public function activate($membership_id, $uid, $check_is_active = TRUE) {

    // Check if this membership is already activated.
    if ($check_is_active) {
      $membership = $this->get_membership($membership_id);

      if (!$membership) {
        watchdog(
          'pbs_passport',
          'Membership is already activated. Membership ID: @id.',
          ['@id' => $membership_id],
          WATCHDOG_INFO
        );
        return FALSE;
      }
    }

    // Check if this $uid is already associated with a membership.
    $membership = $this->get_membership_by_uid($uid);
    if (!$membership) {
      watchdog(
        'pbs_passport',
        'UID is already associated with membership. UID: @uid.',
        ['@uid' => $uid],
        WATCHDOG_INFO
      );
      return FALSE;
    }

    // Activate the membership.
    $data = ['uid' => $uid];
    $activation = $this->patch_request(
      '/memberships/' . $membership_id . '/',
      $data
    );
    if (!$activation) {
      return FALSE;
    }

    // Return the updated membership data.
    return $this->get_membership($membership_id);
  }

  /**
   * Modifies the response of a membership from the MVault API.
   *
   * @param $data
   */
  private function _modify_membership_response_data(&$data) {
    $this->_add_membership_state($data);
    $this->_add_activation_url($data);
    $this->_normalize_login_provider($data);
  }

  /**
   * Normalizes various provider strings from PBS.
   *
   * PBS has used many different strings for the "login_provider" returned in
   * the pbs_profile block. This matches those variants and returns either
   * "google", "facebook", or "pbs".
   *
   * @param array $data
   *   An array of API response data from a membership endpoint.
   */
  private function _normalize_login_provider(&$data) {
    $provider_string = NULL;
    if (!empty($data) && !empty($data['pbs_profile'])) {
      $provider_string = drupal_strtolower(trim(
        $data['pbs_profile']['login_provider']
      ));
    }

    switch ($provider_string) {
      case 'facebook':
        $provider_string = 'Facebook';
        break;
      case 'google':
      case 'googleplus':
      case 'google-oauth2':
        $provider_string = 'Google';
        break;
      case 'pbs':
      case 'openid':
        $provider_string = 'PBS';
        break;
      default:
        $provider_string = t('Unrecognized (@provider)', array(
          '@provider' => $provider_string
        ));
        break;
    }

    $data['pbs_profile']['login_provider'] = $provider_string;
  }

  /**
   * Adds the PBS.org-based activation URL to a response array.
   *
   * @param $data
   */
  private function _add_activation_url(&$data) {
    if (!empty($data)) {
      $data['activation_url'] = NULL;
      if (!empty($data['token'])) {
        $data['activation_url'] = PBS_PASSPORT_ACTIVATION_BASEURL
          . $data['token'] . '/';
      }
    }
  }

  /**
   * Adds a standardized "state" to a response array.
   *
   * PBS uses three variables to determine the state of a membership, but only
   * provides a bool state result. This method provides a more detailed state
   * based on the values.
   *
   * @param array $data
   *   An array of API response data from a membership endpoint.
   *
   * @url https://docs.pbs.org/display/MV/Membership+Vault+API
   */
  private function _add_membership_state(&$data) {
    if (!empty($data)) {
      $activated = $data['current_state']['explanation']['token_activated'];
      switch ($data['current_state']['explanation']['timing']) {
        case 'within_start_expire_dates':
          if ($activated) {
            $state = PBS_PASSPORT_MEMBERSHIP_ACTIVATED;
          }
          else {
            $state = PBS_PASSPORT_MEMBERSHIP_NOT_ACTIVATED;
          }
          break;
        case 'within_grace_period':
          if ($activated) {
            $state = PBS_PASSPORT_MEMBERSHIP_GRACE_PERIOD;
          }
          else {
            $state = PBS_PASSPORT_MEMBERSHIP_NOT_ACTIVATED;
          }
          break;
        case 'grace_period_over':
          $state = PBS_PASSPORT_MEMBERSHIP_EXPIRED;
          break;
        default:
          $state = PBS_PASSPORT_MEMBERSHIP_UNKNOWN;
      }
      $data['state'] = $state;
    }
  }
}
