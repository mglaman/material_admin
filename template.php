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
function customer_admin_css_alter(&$css) {
  //dpm($css);
  unset($css['modules/system/system.messages.css']);
  unset($css['modules/system/system.base.css']);
}
