<?php

/**
 * @file
 * Class with methods for working with PBS's Membership Vault (MVault) service.
 */

/**
 * PBS Membership Vault API client.
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
   * Membership vault production base address.
   *
   * @var string
   */
  const MVAULT_PROD = 'https://mvault.services.pbs.org/api/';

  /**
   * Membership vault QA base address.
   *
   * @var string
   */
  const MVAULT_QA = 'https://mvault-qa.services.pbs.org/api/';

  /**
   * Client ID for API connection.
   *
   * @var string
   */
  private $clientId;

  /**
   * Client secret for API connection.
   *
   * @var string
   */
  private $clientSecret;

  /**
   * PBS member station ID.
   *
   * @var string
   */
  private $stationId;

  /**
   * Base URI of PBS MVault endpoint.
   *
   * @var string
   */
  private $uri;

  /**
   * Auth string combining $clientId and $clientSecret.
   *
   * @var string
   */
  private $authString;

  /**
   * PbsMvaultClient constructor.
   *
   * @param string $client_id
   *   Client ID for API connection.
   * @param string $client_secret
   *   Client secret for API connection.
   * @param string $station_id
   *   PBS member station ID.
   * @param string $environment
   *   The enviornment to connect to. Should be 'qa' or 'prod' and will always
   *   default to 'qa'.
   */
  public function __construct($client_id = '', $client_secret = '', $station_id = '', $environment = 'qa') {
    $this->clientId = $client_id;
    $this->clientSecret = $client_secret;
    $this->stationId = $station_id;
    $this->authString = base64_encode(
      $this->clientId . ":" . $this->clientSecret
    );

    if ($environment == 'prod') {
      $this->uri = self::MVAULT_PROD . $this->stationId;
    }
    else {
      $this->uri = self::MVAULT_QA . $this->stationId;
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
  private function getRequest($endpoint) {
    $data = [];
    $error = [];

    $response = drupal_http_request($this->uri . $endpoint, [
      'method' => 'GET',
      'headers' => ['Authorization' => 'Basic ' . $this->authString],
    ]);

    if (isset($response->error)) {
      $details = json_decode($response->data);

      /* "No resource found" can be returned for a regular PBS account user
      without a (Passport) membership. Some endpoints provide "errors" for
      non-error results. */

      $non_errors = array(
        'No resource found',
        'No memberships exist for this user',
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
            '@data' => $response->data,
          ],
          'severity' => WATCHDOG_CRITICAL,
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
   * @param array $data
   *   Fields to include in the request.
   *
   * @return bool
   *   FALSE for any known errors, TRUE otherwise. PATCH does not return data.
   */
  private function patchRequest($endpoint, array $data) {
    $data = json_encode($data, JSON_UNESCAPED_UNICODE);
    $data_length = drupal_strlen($data);
    $error = [];

    $response = drupal_http_request($this->uri . $endpoint, [
      'method' => 'PATCH',
      'headers' => [
        'Authorization' => 'Basic ' . $this->authString,
        'Content-Type' => 'application/json',
        'Content-Length' => $data_length,
      ],
      'data' => $data,
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
          '@received' => $response->data,
        ],
        'severity' => WATCHDOG_CRITICAL,
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
   *   The membership ID to query for.
   *
   * @return array
   *   An empty array if no membership data is found.
   *
   * @url https://docs.pbs.org/display/MV/Membership+Vault+API#MembershipVaultAPI-get
   */
  public function getMembership($membership_id) {
    $membership = $this->getRequest('/memberships/' . $membership_id . '/');
    if ($membership) {
      $this->modifyMembershipResponseData($membership);
    }
    return $membership;
  }

  /**
   * Get membership info by UID.
   *
   * @param int $uid
   *   The UID to query for.
   *
   * @return array
   *   An empty array if no membership data is found.
   *
   * @url https://docs.pbs.org/display/MV/Membership+Vault+API#MembershipVaultAPI-get
   */
  public function getMembershipByUid($uid) {
    $data = $this->getRequest('/memberships/filter/uid/' . $uid . '/');

    // This endpoint returns an array of arrays.
    if ($data) {
      $data = $data[0];
      $this->modifyMembershipResponseData($data);
    }

    return $data;
  }

  /**
   * Get membership info by email address.
   *
   * @param string $email
   *   The email address to query for.
   *
   * @return array
   *   An empty array if no membership data is found.
   *
   * @url https://docs.pbs.org/display/MV/Membership+Vault+API#MembershipVaultAPI-get
   */
  public function getMembershipByEmail($email) {
    $data = $this->getRequest('/memberships/filter/email/' . $email . '/');

    // This endpoint returns a different array of arrays than the others. It is
    // possible for it to return multiple memberships.
    if ($data) {
      $data = $data['objects'];

      foreach ($data as $idx => $info) {
        $this->modifyMembershipResponseData($data[$idx]);
      }
    }

    return $data;
  }

  /**
   * Activate a membership.
   *
   * @param string $membership_id
   *   The Membership ID of the membership to activate.
   * @param int $uid
   *   The UID of the membership to activate.
   * @param bool $check_is_active
   *   Whether or not to check if the membership is already activated.
   *
   * @return array|bool
   *   FALSE if the $check_is_active is TRUE and the membership is already
   *   activated, the UID is already associated with a different membership, or
   *   the membership is activation endpoint fails. An array of membership data
   *   otherwise.
   *
   * @url https://docs.pbs.org/display/MV/Technical+Deep+Dive%3A+how+%27activation%27+works
   */
  public function activate($membership_id, $uid, $check_is_active = TRUE) {

    // Check if this membership is already activated.
    if ($check_is_active) {
      $membership = $this->getMembership($membership_id);

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
    $membership = $this->getMembershipByUid($uid);
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
    $activation = $this->patchRequest(
      '/memberships/' . $membership_id . '/',
      $data
    );
    if (!$activation) {
      return FALSE;
    }

    // Return the updated membership data.
    return $this->getMembership($membership_id);
  }

  /**
   * Modifies the response of a membership from the MVault API.
   *
   * @param array $data
   *   An array of membership data.
   */
  private function modifyMembershipResponseData(array &$data) {
    $this->addMembershipState($data);
    $this->addActivationUrl($data);
    $this->normalizeLoginProvider($data);
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
  private function normalizeLoginProvider(array &$data) {
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
          '@provider' => $provider_string,
        ));
        break;
    }

    $data['pbs_profile']['login_provider'] = $provider_string;
  }

  /**
   * Adds the PBS.org-based activation URL to a response array.
   *
   * @param array $data
   *   An array of API response data from a membership endpoint.
   */
  private function addActivationUrl(array &$data) {
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
  private function addMembershipState(array &$data) {
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
