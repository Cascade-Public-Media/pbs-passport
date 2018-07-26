<?php

/**
 * @file
 * Theme functions for the PBS Passport module.
 */

/**
 * Implements template_preprocess().
 *
 * Preprocessor for PBS Passport login page. The theme must receive a 'state'
 * key in $variables that will be verified after authentication is complete.
 *
 * @see pbs-passport-login.tpl.php
 * @see pbs_passport_login()
 */
function template_preprocess_pbs_passport_login(&$variables) {
  $path = drupal_get_path('module', 'pbs_passport');
  drupal_add_css($path . '/css/pbs_passport.css');

  $oauth_base = PBS_PASSPORT_OAUTH2_BASEURL;

  $options = [
    'absolute' => TRUE,
    'query' => [
      'redirect_uri' => PBS_PASSPORT_REDIRECT_URI,
      'response_type' => 'code',
      'client_id' => variable_get('pbs_passport_oauth_client_id'),
      'scope' => variable_get('pbs_passport_oauth_scope') . ' vppa',
      'state' => $variables['state'],
    ],
  ];

  $variables['login_urls'] = [
    'pbs' => url($oauth_base . 'authorize/', $options),
    'google' => url($oauth_base . 'social/login/google-oauth2/', $options),
    'facebook' => url($oauth_base . 'social/login/facebook/', $options),
  ];

  $options['query'] = [];
  $options['query']['next'] = $variables['login_urls']['pbs'];
  $variables['login_urls']['create_pbs'] = url(
    $oauth_base . 'register/',
    $options
  );

  $variables['station'] = pbs_passport_get_station_data();
}

/**
 * Implements template_preprocess().
 *
 * Preprocessor for PBS Passport User debug page.
 *
 * @see pbs-passport-user-debug.tpl.php
 */
function template_preprocess_pbs_passport_user_debug(&$variables) {
  global $user;

  try {
    $result = db_select('pbs_passport_user', 'ppu')
      ->fields('ppu')
      ->condition('uid', $user->uid, '=')
      ->range(0, 1)
      ->execute();

    if ($result->rowCount() != 1) {
      $variables['db_data'] = [
        'not_pbs' => [
          '#type' => 'html_tag',
          '#tag' => 'p',
          '#value' => 'There is no PBS Passport data in the database for this
          user.',
        ],
      ];
    }
    else {
      $variables['db_data'] = [
        '#theme' => 'table',
        '#header' => [t('field'), t('value')],
        '#rows' => [],
      ];
      foreach ($result->fetchAssoc() as $field => $value) {
        $variables['db_data']['#rows'][] = [$field, $value];
      }
    }
  }
  catch (Exception $e) {
    watchdog_exception('pbs_passport', $e);
  }

  if (!isset($_SESSION['pbs_passport'])) {
    $variables['session_data'] = [
      'not_pbs' => [
        '#type' => 'html_tag',
        '#tag' => 'p',
        '#value' => 'This session does not appear to have been initiated with
          a PBS OAuth code.',
      ],
    ];
  }
  else {
    $header = [t('key'), t('value')];
    $variables['session_data'] = [
      'token info' => [
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => [],
        '#prefix' => t('<h4>Token Data</h4>'),
      ],
      'user info' => [
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => [],
        '#prefix' => t('<h4>User Data</h4>'),
      ],
      'membership info' => [
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => [],
        '#prefix' => t('<h4>Membership Data</h4>'),
      ],
    ];

    foreach ($_SESSION['pbs_passport']['token'] as $key => $val) {

      if ($key == 'expires_timestamp') {
        $val = format_date($val, 'long');
      }
      elseif ($key == 'expires_in') {
        $val = format_interval($val);
      }

      $key = ucwords(str_replace('_', ' ', $key));
      $variables['session_data']['token info']['#rows'][] = [$key, $val];
    }

    foreach ($_SESSION['pbs_passport']['user'] as $key => $val) {

      if ($key == 'vppa') {
        if ($_SESSION['pbs_passport']['user']['vppa']['vppa_accepted']) {
          $t = $_SESSION['pbs_passport']['user']['vppa']['vppa_last_updated'];
          $val = t('Accepted<br/>@time<br/>@interval ago', [
            '@time' => $t,
            '@interval' => format_interval(time() - strtotime($t)),
          ]);
        }
        else {
          $val = t('Not accepted');
        }
      }

      $key = ucwords(str_replace('_', ' ', $key));
      $variables['session_data']['user info']['#rows'][] = [$key, $val];
    }

    foreach ($_SESSION['pbs_passport']['membership'] as $key => $val) {

      if ($key == 'current_state') {
        $current_state = $_SESSION['pbs_passport']['membership'][$key];
        $val = t('@access<br/>@status (@timing)<br/>@token', [
          '@access' => ($current_state['has_access'] ? t('Has access') : ''),
          '@status' => $current_state['explanation']['status'],
          '@timing' => $current_state['explanation']['timing'],
          '@token' => ($current_state['explanation']['token_activated']
            ? t('Token activated') : ''),
        ]);
      }
      elseif ($key == 'pbs_profile') {
        $pbs_profile = $_SESSION['pbs_passport']['membership'][$key];
        $val = t('@first @last<br/>@uid<br/>Login provider: @provider', [
          '@first' => $pbs_profile['first_name'],
          '@last' => $pbs_profile['last_name'],
          '@uid' => $pbs_profile['UID'],
          '@provider' => $pbs_profile['login_provider'],
        ]);
      }

      $key = ucwords(str_replace('_', ' ', $key));
      $variables['session_data']['membership info']['#rows'][] = [$key, $val];
    }
  }
}

/**
 * Implements template_preprocess().
 *
 * Preprocessor for PBS Passport membership lookup form page.
 *
 * @see pbs-passport-lookup-form.tpl.php
 * @see pbs_passport_lookup_form()
 */
function template_preprocess_pbs_passport_lookup_form(&$variables) {
  $variables['station'] = pbs_passport_get_station_data();
}
