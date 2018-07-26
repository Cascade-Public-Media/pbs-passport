<?php

/**
 * @file
 * Template file for the theming the Passport membership lookup form.
 *
 * Available custom variables:
 * - $form: The form render array.
 * - $station: An array of station data.
 *
 * @see template_preprocess_pbs_passport_lookup_form()
 */
?>
<p>
    Provide your email address below to check for an existing
    <?php print $station['short_common_name']; ?> Passport membership. If a
    membership record is found, an email will be sent to the provided address
    with additional details, including an activation code if the membership is
    not yet activated.
</p>

<?php print drupal_render_children($form); ?>
