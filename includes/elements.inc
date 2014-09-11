<?php

/**
 * @file
 * Overrides for form lements
 */

/**
 * Implements hook_element_info_alter().
 */
function material_admin_element_info_alter(&$type) {
  // Add our own process to textfields so that placeholders are always set.
  $type['textfield']['#process'][] = 'material_admin_fix_textfield_placeholders';
}

/**
 * Element callback to attach placerholders to textfields.
 *
 * Form API marks elements as #processed after these run, not when it hits the
 * theme layer.
 */
function material_admin_fix_textfield_placeholders($element, &$form_state) {
  if (isset($element['#title'])) {
    $element['#attributes']['placeholder'] = $element['#title'];
  }
  return $element;
}
