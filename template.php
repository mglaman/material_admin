<?php

/**
 * @file
 * Contains magic for Customer Admin theme.
 */

require_once dirname(__FILE__) . '/includes/elements.inc';
require_once dirname(__FILE__) . '/includes/preprocess.inc';
require_once dirname(__FILE__) . '/includes/process.inc';
require_once dirname(__FILE__) . '/includes/theme.inc';

/**
 * Implements hook_css_alter().
 */
function material_admin_css_alter(&$css) {
  //dpm($css);
  unset($css['modules/system/system.messages.css']);
  unset($css['modules/system/system.base.css']);
}

/**
 * Implements hook_page_alter().
 */
function material_admin_page_alter(&$page) {

  // First check if using Libraries to load Font Awesome
  if (module_exists('libraries') && ($library = libraries_detect('fontawesome')) && !empty($library['installed'])) {
    // Load our library
    libraries_load('fontawesome');
  }
  // If there isn't a library, use the CDN. This can be disabled in case a
  // theme is providing FontAwesome via CDN and not libraries.
  elseif (!variable_get('material_admin_cdn', FALSE)) {
    // Use super awesome CDN.
    drupal_add_css('//maxcdn.bootstrapcdn.com/font-awesome/4.1.0/css/font-awesome.min.css', array('type' => 'external'));
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Customize the update settings form.
 */
function material_admin_form_update_settings_alter(&$form, &$form_state) {
  $form['admin_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'clearfix',
      ),
    ),
  );
  $form['admin_container']['admin_left'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'admin__left',
      ),
    ),
  );
  $form['admin_container']['admin_right'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'admin__right',
      ),
    ),
  );

  // Left
  $form['admin_container']['admin_left']['update_check_frequency'] = $form['update_check_frequency'];
  unset($form['update_check_frequency']);
  $form['admin_container']['admin_left']['update_check_disabled'] = $form['update_check_disabled'];
  unset($form['update_check_disabled']);
  // Right
  $form['admin_container']['admin_right']['update_notify_emails'] = $form['update_notify_emails'];
  unset($form['update_notify_emails']);
  $form['admin_container']['admin_right']['update_notification_threshold'] = $form['update_notification_threshold'];
  unset($form['update_notification_threshold']);
}
