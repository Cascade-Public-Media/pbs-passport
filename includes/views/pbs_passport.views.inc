<?php

/**
 * @file
 * Views hooks implemented for the PBS Passport module.
 */

/**
 * Implements hook_views_data().
 */
function pbs_passport_views_data() {
  $data['pbs_passport_user']['table']['group'] = t('PBS Passport');
  $data['pbs_passport_user']['table']['base'] = array(
    'field' => 'uid',
    'title' => t('PBS Passport'),
    'help' => t('PBS Passport account data associated to Drupal users.'),
  );
  $data['pbs_passport_user']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  // Drupal user UID.
  $data['pbs_passport_user']['uid'] = array(
    'title' => t('User'),
    'help' => t('The user this data relates to.'),
    'relationship' => array(
      'base' => 'users',
      'field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('User/PBS account relationship'),
    ),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'sort' => array('handler' => 'views_handler_sort'),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
      'name field' => 'name',
      'numeric' => TRUE,
      'validate type' => 'uid',
    ),
  );

  // PBS account PID.
  $data['pbs_passport_user']['pid'] = array(
    'title' => t('PBS Account PID'),
    'help' => t('PBS account unique identifier.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  // PBS Passport membership ID.
  $data['pbs_passport_user']['membership_id'] = array(
    'title' => t('Member ID'),
    'help' => t('PBS Passport account unique identifier.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  // PBS account email address.
  $data['pbs_passport_user']['email'] = array(
    'title' => t('Email Address'),
    'help' => t('Email address from PBS account data.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  // PBS account first name.
  $data['pbs_passport_user']['first_name'] = array(
    'title' => t('First Name'),
    'help' => t('First name from PBS account data.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  // PBS account last name.
  $data['pbs_passport_user']['last_name'] = array(
    'title' => t('Last Name'),
    'help' => t('Last name from PBS account data.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  // VPPA status.
  $data['pbs_passport_user']['vppa_accepted'] = array(
    'title' => t('VPPA Accepted'),
    'help' => t('Indicates if the user has accepted the VPPA agreement.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'type' => 'yes-no',
      'accept null' => TRUE,
      'use equal' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
  );

  // PBS Passport membership type.
  $data['pbs_passport_user']['membership_type'] = array(
    'title' => t('Membership Type'),
    'help' => t('PBS Passport membership type name.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  // PBS Passport state.
  $data['pbs_passport_user']['passport_state'] = array(
    'title' => t('Passport State'),
    'help' => t('Overall PBS Passport membership state.'),
    'field' => array(
      'handler' => 'pbs_passport_handler_passport_state',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'argument' => array('handler' => 'views_handler_argument_numeric'),
  );

  // Passport activation status.
  $data['pbs_passport_user']['passport_activated'] = array(
    'title' => t('Activated'),
    'help' => t('Indicates if the user has activated Passport.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'type' => 'yes-no',
      'accept null' => TRUE,
      'use equal' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
  );

  // Passport start date
  $data['pbs_passport_user']['passport_start_date'] = array(
    'title' => t('Start Date'),
    'help' => t('The date this Passport membership started.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort_date'),
    'filter' => array('handler' => 'views_handler_filter_date'),
  );

  // Passport expire date
  $data['pbs_passport_user']['passport_expire_date'] = array(
    'title' => t('Expire Date'),
    'help' => t('The date this Passport membership will expire/expired.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort_date'),
    'filter' => array('handler' => 'views_handler_filter_date'),
  );

  // Passport grace period date
  $data['pbs_passport_user']['passport_grace_date'] = array(
    'title' => t('Grace Period Date'),
    'help' => t('The date this Passport grace period ends.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort_date'),
    'filter' => array('handler' => 'views_handler_filter_date'),
  );

  // PBS Passport login provider.
  $data['pbs_passport_user']['login_provider'] = array(
    'title' => t('Login Provider'),
    'help' => t('The login provider used by Passport (e.g. PBS, Facebook,
      etc.).'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array('handler' => 'views_handler_sort'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'argument' => array('handler' => 'views_handler_argument_string'),
  );

  return $data;
}
