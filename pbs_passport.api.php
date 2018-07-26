<?php

/**
 * @file
 * Hooks provided by the PBS Passport module.
 */

/**
 * Alter a Drupal user before it is created by the PBS Passport module.
 *
 * @param array $edit
 *   An array of basic user information just before it is saved.
 * @param array $pbs_user
 *   PBS account user information.
 *
 * @see pbs_passport_oauth2_callback()
 */
function hook_pbs_passport_user_presave_alter(array &$edit, array $pbs_user) {

}

/**
 * Take action after a Drupal user is created by the PBS Passport module.
 *
 * @param object $user
 *   A fully-loaded user object.
 * @param array $pbs_user
 *   PBS account user information.
 *
 * @see pbs_passport_oauth2_callback()
 */
function hook_pbs_passport_user_insert_alter(&$user, array $pbs_user) {

}

/**
 * Take action after PBS authentication and before final Drupal login.
 *
 * This happens before the local database cache of PBS user data is updated.
 *
 * @param object $user
 *   A fully-loaded user object.
 * @param array $pbs_user
 *   PBS account user information.
 *
 * @see pbs_passport_oauth2_callback()
 */
function hook_pbs_passport_user_login($user, array $pbs_user) {

}
