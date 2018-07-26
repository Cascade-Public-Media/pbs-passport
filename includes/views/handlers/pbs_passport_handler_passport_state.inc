<?php

/**
 * @file
 * Definition of pbs_passport_handler_passport_state handler.
 */

/**
 * Translate Passport state information to a human-readable string.
 */
class pbs_passport_handler_passport_state extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function get_value($values, $field = NULL) {
    $state = NULL;
    $alias = isset($field) ? $this->aliases[$field] : $this->field_alias;
    if (isset($values->{$alias})) {
      $state = $values->{$alias};
    }
    return pbs_passport_state_to_string($state);
  }

}
