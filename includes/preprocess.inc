<?php

/**
 * @file
 * Preprocess hook functions for Customer admin.
 */

/**
 * Implements hook_preprocess_block().
 */
function material_admin_preprocess_block(&$variables) {
  $variables['title_attributes_array']['class'][] = 'block__title';
  $variables['content_attributes_array']['class'][] = 'block__content';

  $module_css_clean = drupal_clean_css_identifier($variables['block']->module);


}

/**
 * Implements hook_preprocess_button().
 *
 * Button classes are form-{button_type}, provide more appropriate classes.
 * @todo: Improve by creating proper elements.. or something.
 *        Maybe preprocess_actions() and set flag vs text identifier?
 */
function material_admin_preprocess_button(&$variables) {
  $element = &$variables['element'];

  // Remove/Delete
  if (in_array($element['#value'], array('Delete', 'Remove'))) {
    $element['#button_type'] = 'delete';
  }
  // Preview
  elseif ($element['#value'] == 'Preview') {
    $element['#button_type'] = 'preview';
  }
}

/**
 * Implements hook_preprocess_html().
 */
function material_admin_preprocess_html(&$variables) {

}

/**
 * Implements hook_preprocess_page().
 */
function material_admin_preprocess_page(&$variables) {
  // You can use preprocess hooks to modify the variables before they are passed
  // to the theme function or template file.
}
