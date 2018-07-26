PBS Passport
============

CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Installation
 * Configuration
 * Functionality
 * Acknowledgments
 * Maintainers
 * License

INTRODUCTION
------------

The PBS Passport module enables OAuth2-based authentication using PBS.org 
accounts via PBS.org, Google, and Facebook. This module is intended for PBS 
member stations that have been granted access to the OAuth2 and MVault services 
by PBS.

 * For a full description of the module, visit the project page:
   https://www.drupal.org/project/pbs_passport
   
 * To submit bug reports and feature suggestions, or to track changes:
   https://www.drupal.org/project/issues/pbs_passport

REQUIREMENTS
------------

This module requires the following modules:

 * [Token](https://drupal.org/project/token)
 * [Views](https://drupal.org/project/views)

OAuth2 client and MVault credentials from PBS are required to configure and use 
this module.

 * For information about how to obtain credentials, see:
   https://docs.pbs.org/display/MV/Custom+Implementation

INSTALLATION
------------

1. Install as you would normally install a contributed Drupal module.
2. Obtain OAuth2 client and MVault credentials from PBS.
3. Contact PBS to whitelist the **full URL** of the OAuth2 redirect URL for your
   website (e.g. https://www.explample.com/pbs-passport/auth).
4. Configure credentials in the module settings (see CONFIGURATION).

CONFIGURATION
-------------

Four configuration pages are provided. These pages can be used to configure
important settings for the module.

 * `Administration » Configuration » People » PBS Passport » General Settings`
   Configure a station call sign and ID (required).
   
 * `Administration » Configuration » People » PBS Passport » MVault Settings`
   Configure the production and development MVault API credentials as provided
   by PBS (required).
   
 * `Administration » Configuration » People » PBS Passport » OAuth2 Settings`
   Configure the OAuth2 client credentials and scope as provided by PBS 
   (required).
   
 * `Administration » Configuration » People » PBS Passport » Email Templates`
   Configure contents of emails sent from PBS Passport.

Three templates are provided. These templates can be overridden by custom theme
implementations.

 * `pbs-passport-login.tpl.php`
   The default authorization page served from /pbs-passport/login.
   
 * `pbs-passport-lookup-form.tpl.php`
   The default membership lookup form served from /pbs-passport/lookup.
   
 * `pbs-passport-user-debug.tpl.php`
   A basic debugging page served from /pbs-passport/debug (based on the "view pbs 
   passport debug data" permission).
   
Three hooks are provided. These hooks can be used by other modules to add 
behaviors triggered by PBS Passport events.

 * `hook_pbs_passport_user_presave_alter()`
   Alter a Drupal user before it is created by the PBS Passport module.
   
 * `hook_pbs_passport_user_insert_alter()`
   Take action after a Drupal user is created by the PBS Passport module.
   
 * `hook_pbs_passport_user_login()`
   Take action after PBS authentication and before final Drupal login.

FUNCTIONALITY
-------------

When a user authorizes via PBS OAuth, the PBS Passport module will look for a 
Drupal account with the same email address and log in with that account. If a 
Drupal account does not exist, a new one is created and logged in.

During login, information from the PBS OAuth2 and MVault services is cached in 
`$_SESSION['pbs_passport']` for the duration of the user's session. Some data is
also stored in the local `pbs_passport_user` database table. This data is 
evaluated/updated each time the user logs in and attached as an array with the 
`pbs_passport` key to a user object loaded with `user_load()`.

This module provides two sets of tokens in its root `pbs_passport` type:

 * `pbs_passport_station`
    Provides tokenized data about the member station (see CONFIGURATION section 
    for station settings info). E.g. `[pbs_passport:station:call_sign]`
   
 * `pbs_passport_membership`
    Provides tokenzied data about a logged-in user's Passoport membership. E.g. 
    `[pbs_passport:membership:email]`.
   
Some Passport data is also exposed for Views with a users base table. A simple, 
searchable view of locally-stored data about Passport-authorized users is 
available at `Administration » People » PBS Passport Users`.

ACKNOWLEDGEMENTS
----------------

This module is based on code originally developed for WordPress by William Tam 
and Benny Wong for WNET New York Public Media, with modifications from the Bear 
Group, Inc.

 * The full, original code can be found at: 
   https://github.com/tamw-wnet/pbs-passport-authenticate

MAINTAINERS
-----------

Current maintainers:

 * Christopher Charbonneau Wells (wells) - https://www.drupal.org/u/wells

Development is sponsored by:

 * [Cascade Public Media](https://www.drupal.org/cascade-public-media) for 
 [KCTS9.org](https://kcts9.org/) and [Crosscut.com](https://crosscut.com/).
 
LICENSE
-------

All code in this repository is licensed 
[GPLv2](http://www.gnu.org/licenses/gpl-2.0.html). A LICENSE file is not 
included in this repository per Drupal's module packaging specifications.

See [Licensing on Drupal.org](https://www.drupal.org/about/licensing).
