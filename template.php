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
