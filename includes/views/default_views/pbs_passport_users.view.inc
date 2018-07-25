<?php

/**
 * @file
 * View definition pbs_passport_users.
 */

$view = new view();
$view->name = 'pbs_passport_users';
$view->description = 'Drupal users with associated PBS Passport data.';
$view->tag = 'default';
$view->base_table = 'users';
$view->human_name = 'PBS Passport: Users';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'PBS Passport Users';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'menu';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '25';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['quantity'] = '9';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'name' => 'name',
  'first_name' => 'first_name',
  'last_name' => 'last_name',
  'email' => 'email',
  'login_provider' => 'login_provider',
  'passport_state' => 'passport_state',
  'passport_activated' => 'passport_activated',
  'vppa_accepted' => 'vppa_accepted',
  'passport_start_date' => 'passport_start_date',
  'passport_expire_date' => 'passport_expire_date',
  'passport_grace_date' => 'passport_grace_date',
  'membership_type' => 'membership_type',
  'membership_id' => 'membership_id',
  'pid' => 'pid',
);
$handler->display->display_options['style_options']['default'] = 'passport_start_date';
$handler->display->display_options['style_options']['info'] = array(
  'name' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'first_name' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'last_name' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'email' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'login_provider' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'passport_state' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'passport_activated' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'vppa_accepted' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'passport_start_date' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'passport_expire_date' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'passport_grace_date' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'membership_type' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'membership_id' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'pid' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['label'] = 'Drupal User';
$handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
/* Field: PBS Passport: First Name */
$handler->display->display_options['fields']['first_name']['id'] = 'first_name';
$handler->display->display_options['fields']['first_name']['table'] = 'pbs_passport_user';
$handler->display->display_options['fields']['first_name']['field'] = 'first_name';
/* Field: PBS Passport: Last Name */
$handler->display->display_options['fields']['last_name']['id'] = 'last_name';
$handler->display->display_options['fields']['last_name']['table'] = 'pbs_passport_user';
$handler->display->display_options['fields']['last_name']['field'] = 'last_name';
/* Field: PBS Passport: Email Address */
$handler->display->display_options['fields']['email']['id'] = 'email';
$handler->display->display_options['fields']['email']['table'] = 'pbs_passport_user';
$handler->display->display_options['fields']['email']['field'] = 'email';
/* Field: PBS Passport: Login Provider */
$handler->display->display_options['fields']['login_provider']['id'] = 'login_provider';
$handler->display->display_options['fields']['login_provider']['table'] = 'pbs_passport_user';
$handler->display->display_options['fields']['login_provider']['field'] = 'login_provider';
/* Field: PBS Passport: Passport State */
$handler->display->display_options['fields']['passport_state']['id'] = 'passport_state';
$handler->display->display_options['fields']['passport_state']['table'] = 'pbs_passport_user';
$handler->display->display_options['fields']['passport_state']['field'] = 'passport_state';
/* Field: PBS Passport: Activated */
$handler->display->display_options['fields']['passport_activated']['id'] = 'passport_activated';
$handler->display->display_options['fields']['passport_activated']['table'] = 'pbs_passport_user';
$handler->display->display_options['fields']['passport_activated']['field'] = 'passport_activated';
$handler->display->display_options['fields']['passport_activated']['not'] = 0;
/* Field: PBS Passport: VPPA Accepted */
$handler->display->display_options['fields']['vppa_accepted']['id'] = 'vppa_accepted';
$handler->display->display_options['fields']['vppa_accepted']['table'] = 'pbs_passport_user';
$handler->display->display_options['fields']['vppa_accepted']['field'] = 'vppa_accepted';
$handler->display->display_options['fields']['vppa_accepted']['not'] = 0;
/* Field: PBS Passport: Start Date */
$handler->display->display_options['fields']['passport_start_date']['id'] = 'passport_start_date';
$handler->display->display_options['fields']['passport_start_date']['table'] = 'pbs_passport_user';
$handler->display->display_options['fields']['passport_start_date']['field'] = 'passport_start_date';
$handler->display->display_options['fields']['passport_start_date']['date_format'] = 'custom';
$handler->display->display_options['fields']['passport_start_date']['custom_date_format'] = 'j M Y';
$handler->display->display_options['fields']['passport_start_date']['second_date_format'] = 'long';
/* Field: PBS Passport: Expire Date */
$handler->display->display_options['fields']['passport_expire_date']['id'] = 'passport_expire_date';
$handler->display->display_options['fields']['passport_expire_date']['table'] = 'pbs_passport_user';
$handler->display->display_options['fields']['passport_expire_date']['field'] = 'passport_expire_date';
$handler->display->display_options['fields']['passport_expire_date']['date_format'] = 'custom';
$handler->display->display_options['fields']['passport_expire_date']['custom_date_format'] = 'j M Y';
$handler->display->display_options['fields']['passport_expire_date']['second_date_format'] = 'long';
/* Field: PBS Passport: Grace Period Date */
$handler->display->display_options['fields']['passport_grace_date']['id'] = 'passport_grace_date';
$handler->display->display_options['fields']['passport_grace_date']['table'] = 'pbs_passport_user';
$handler->display->display_options['fields']['passport_grace_date']['field'] = 'passport_grace_date';
$handler->display->display_options['fields']['passport_grace_date']['date_format'] = 'custom';
$handler->display->display_options['fields']['passport_grace_date']['custom_date_format'] = 'j M Y';
$handler->display->display_options['fields']['passport_grace_date']['second_date_format'] = 'long';
/* Field: PBS Passport: Membership Type */
$handler->display->display_options['fields']['membership_type']['id'] = 'membership_type';
$handler->display->display_options['fields']['membership_type']['table'] = 'pbs_passport_user';
$handler->display->display_options['fields']['membership_type']['field'] = 'membership_type';
/* Field: PBS Passport: Member ID */
$handler->display->display_options['fields']['membership_id']['id'] = 'membership_id';
$handler->display->display_options['fields']['membership_id']['table'] = 'pbs_passport_user';
$handler->display->display_options['fields']['membership_id']['field'] = 'membership_id';
/* Field: PBS Passport: PBS Account PID */
$handler->display->display_options['fields']['pid']['id'] = 'pid';
$handler->display->display_options['fields']['pid']['table'] = 'pbs_passport_user';
$handler->display->display_options['fields']['pid']['field'] = 'pid';
/* Sort criterion: User: Created date */
$handler->display->display_options['sorts']['created']['id'] = 'created';
$handler->display->display_options['sorts']['created']['table'] = 'users';
$handler->display->display_options['sorts']['created']['field'] = 'created';
$handler->display->display_options['sorts']['created']['order'] = 'DESC';
/* Filter criterion: User: Active */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'users';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = '1';
$handler->display->display_options['filters']['status']['group'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
/* Filter criterion: PBS Passport: User */
$handler->display->display_options['filters']['uid']['id'] = 'uid';
$handler->display->display_options['filters']['uid']['table'] = 'pbs_passport_user';
$handler->display->display_options['filters']['uid']['field'] = 'uid';
$handler->display->display_options['filters']['uid']['operator'] = '!=';
$handler->display->display_options['filters']['uid']['value']['value'] = '0';
$handler->display->display_options['filters']['uid']['group'] = 1;
/* Filter criterion: PBS Passport: Member ID */
$handler->display->display_options['filters']['membership_id']['id'] = 'membership_id';
$handler->display->display_options['filters']['membership_id']['table'] = 'pbs_passport_user';
$handler->display->display_options['filters']['membership_id']['field'] = 'membership_id';
$handler->display->display_options['filters']['membership_id']['group'] = 1;
$handler->display->display_options['filters']['membership_id']['exposed'] = TRUE;
$handler->display->display_options['filters']['membership_id']['expose']['operator_id'] = 'membership_id_op';
$handler->display->display_options['filters']['membership_id']['expose']['label'] = 'Member ID';
$handler->display->display_options['filters']['membership_id']['expose']['operator'] = 'membership_id_op';
$handler->display->display_options['filters']['membership_id']['expose']['identifier'] = 'membership_id';
$handler->display->display_options['filters']['membership_id']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  9 => 0,
  11 => 0,
  5 => 0,
  15 => 0,
  13 => 0,
  7 => 0,
  16 => 0,
  21 => 0,
);
/* Filter criterion: PBS Passport: Last Name */
$handler->display->display_options['filters']['last_name']['id'] = 'last_name';
$handler->display->display_options['filters']['last_name']['table'] = 'pbs_passport_user';
$handler->display->display_options['filters']['last_name']['field'] = 'last_name';
$handler->display->display_options['filters']['last_name']['operator'] = 'starts';
$handler->display->display_options['filters']['last_name']['group'] = 1;
$handler->display->display_options['filters']['last_name']['exposed'] = TRUE;
$handler->display->display_options['filters']['last_name']['expose']['operator_id'] = 'last_name_op';
$handler->display->display_options['filters']['last_name']['expose']['label'] = 'Last Name';
$handler->display->display_options['filters']['last_name']['expose']['operator'] = 'last_name_op';
$handler->display->display_options['filters']['last_name']['expose']['identifier'] = 'last_name';
$handler->display->display_options['filters']['last_name']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  9 => 0,
  11 => 0,
  5 => 0,
  15 => 0,
  13 => 0,
  7 => 0,
  16 => 0,
  21 => 0,
);
/* Filter criterion: PBS Passport: Email Address */
$handler->display->display_options['filters']['email']['id'] = 'email';
$handler->display->display_options['filters']['email']['table'] = 'pbs_passport_user';
$handler->display->display_options['filters']['email']['field'] = 'email';
$handler->display->display_options['filters']['email']['operator'] = 'contains';
$handler->display->display_options['filters']['email']['group'] = 1;
$handler->display->display_options['filters']['email']['exposed'] = TRUE;
$handler->display->display_options['filters']['email']['expose']['operator_id'] = 'email_op';
$handler->display->display_options['filters']['email']['expose']['label'] = 'Email Address';
$handler->display->display_options['filters']['email']['expose']['operator'] = 'email_op';
$handler->display->display_options['filters']['email']['expose']['identifier'] = 'email';
$handler->display->display_options['filters']['email']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  9 => 0,
  11 => 0,
  5 => 0,
  15 => 0,
  13 => 0,
  7 => 0,
  16 => 0,
  21 => 0,
);
/* Filter criterion: PBS Passport: Passport State */
$handler->display->display_options['filters']['passport_state']['id'] = 'passport_state';
$handler->display->display_options['filters']['passport_state']['table'] = 'pbs_passport_user';
$handler->display->display_options['filters']['passport_state']['field'] = 'passport_state';
$handler->display->display_options['filters']['passport_state']['group'] = 1;
$handler->display->display_options['filters']['passport_state']['exposed'] = TRUE;
$handler->display->display_options['filters']['passport_state']['expose']['operator_id'] = 'passport_state_op';
$handler->display->display_options['filters']['passport_state']['expose']['label'] = 'Passport State';
$handler->display->display_options['filters']['passport_state']['expose']['operator'] = 'passport_state_op';
$handler->display->display_options['filters']['passport_state']['expose']['identifier'] = 'passport_state';
$handler->display->display_options['filters']['passport_state']['is_grouped'] = TRUE;
$handler->display->display_options['filters']['passport_state']['group_info']['label'] = 'Passport State';
$handler->display->display_options['filters']['passport_state']['group_info']['identifier'] = 'passport_state';
$handler->display->display_options['filters']['passport_state']['group_info']['group_items'] = array(
  1 => array(
    'title' => 'Activated',
    'operator' => '=',
    'value' => array(
      'value' => '10',
      'min' => '',
      'max' => '',
    ),
  ),
  2 => array(
    'title' => 'Not Activated',
    'operator' => '=',
    'value' => array(
      'value' => '20',
      'min' => '',
      'max' => '',
    ),
  ),
  3 => array(
    'title' => 'Grace Period',
    'operator' => '=',
    'value' => array(
      'value' => '30',
      'min' => '',
      'max' => '',
    ),
  ),
  4 => array(
    'title' => 'Expired',
    'operator' => '=',
    'value' => array(
      'value' => '90',
      'min' => '',
      'max' => '',
    ),
  ),
);
/* Filter criterion: PBS Passport: Login Provider */
$handler->display->display_options['filters']['login_provider']['id'] = 'login_provider';
$handler->display->display_options['filters']['login_provider']['table'] = 'pbs_passport_user';
$handler->display->display_options['filters']['login_provider']['field'] = 'login_provider';
$handler->display->display_options['filters']['login_provider']['group'] = 1;
$handler->display->display_options['filters']['login_provider']['exposed'] = TRUE;
$handler->display->display_options['filters']['login_provider']['expose']['operator_id'] = 'login_provider_op';
$handler->display->display_options['filters']['login_provider']['expose']['label'] = 'Login Provider';
$handler->display->display_options['filters']['login_provider']['expose']['operator'] = 'login_provider_op';
$handler->display->display_options['filters']['login_provider']['expose']['identifier'] = 'login_provider';
$handler->display->display_options['filters']['login_provider']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  9 => 0,
  11 => 0,
  5 => 0,
  15 => 0,
  13 => 0,
  7 => 0,
  16 => 0,
  21 => 0,
);
$handler->display->display_options['filters']['login_provider']['is_grouped'] = TRUE;
$handler->display->display_options['filters']['login_provider']['group_info']['label'] = 'Login Provider';
$handler->display->display_options['filters']['login_provider']['group_info']['identifier'] = 'login_provider';
$handler->display->display_options['filters']['login_provider']['group_info']['group_items'] = array(
  1 => array(
    'title' => 'Google',
    'operator' => '=',
    'value' => 'Google',
  ),
  2 => array(
    'title' => 'Facebook',
    'operator' => '=',
    'value' => 'Facebook',
  ),
  3 => array(
    'title' => 'PBS',
    'operator' => '=',
    'value' => 'PBS',
  ),
);

/* Display: PBS Passport Users */
$handler = $view->new_display('page', 'PBS Passport Users', 'page_1');
$handler->display->display_options['path'] = 'admin/people/pbs-passport-users';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'PBS Passport Users';
$handler->display->display_options['menu']['description'] = 'Drupal users with associated PBS Passport data.';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['name'] = 'management';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

$views[$view->name] = $view;
