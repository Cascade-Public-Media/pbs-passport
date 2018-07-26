<?php

/**
 * @file
 * Passport User Debug page template.
 *
 * Available custom variables:
 * - $session_data: Information about current session variables.
 * - $db_data: Information about synced data is local database.
 *
 * @see template_preprocess_pbs_passport_user_debug()
 */
?>

<h3>Session Data</h3>

<div>
  <?php print render($session_data); ?>
</div>

<h3>Database Data</h3>

<div>
  <?php print render($db_data); ?>
</div>
