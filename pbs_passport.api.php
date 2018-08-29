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

/**
 * Alter the response after a Passport membership lookup.
 *
 * Data used for the lookup email is pulled from the first record in the
 * $response array ($response[0]). This hook can be used for custom processing
 * of multiple memberships or for modifications of membership data.
 *
 * @param array $response
 *   The response array from the lookup.
 * @param array $form
 *   The lookup form array.
 * @param array $form_state
 *   The lookup form state array.
 *
 * @see pbs_passport_lookup_form_submit()
 */
function hook_pbs_passport_lookup_alter(array &$response, array $form, array $form_state) {

}
