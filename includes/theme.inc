<?php

/**
 * @file
 * Includes theme overrides for Customer Admin
 */

/**
 * Returns HTML for a breadcrumb trail.
 *
 * @ingroup themeable
 */
function material_admin_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    $breadcrumb[] = drupal_get_title();
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

    // Override Drupal core breadcrumb item imploding (no arrow).
    $output .= '<ol class="breadcrumb"><li>' . implode(' &gt; </li> <li>', $breadcrumb) . '</li></ol>';
    return $output;
  }
}

/**
 * Returns HTML for a list or nested list of items.
 *
 * @ingroup themeable
 */
function material_admin_item_list($variables) {
  $items = $variables['items'];
  $title = $variables['title'];
  $type = $variables['type'];
  $attributes = $variables['attributes'];

  // Only output the list container and title, if there are any list items.
  // Check to see whether the block title exists before adding a header.
  // Empty headers are not semantic and present accessibility challenges.
  $output = '';
  if (isset($title) && $title !== '') {
    // No more extra headings!
    $attributes['data-header'] = $title;
    $attributes['class'][] = 'item-list--has-header';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $i = 0;
    foreach ($items as $item) {
      $attributes = array();
      $children = array();
      $data = '';
      $i++;
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      if (count($children) > 0) {
        // Render nested list.
        $data .= theme_item_list(array(
          'items' => $children,
          'title' => NULL,
          'type' => $type,
          'attributes' => $attributes,
        ));
      }
      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
    }
    $output .= "</$type>";
  }
  return $output;
}

/**
 * Returns HTML for status and/or error messages, grouped by type.
 *
 * @ingroup themeable
 */
function material_admin_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );
  $status_icon = array(
    'status' => 'fa-check-circle',
    'error' => 'fa-times-circle',
    'warning' => 'fa-exclamation-triangle',
  );

  foreach (drupal_get_messages($display) as $type => $messages) {
    $output .= '<div class="messages messages--' . $type . '">';

    if (!empty($status_icon[$type])) {
      $output .= '<i class="fa ' . $status_icon[$type] . '"></i>';
    }

    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>";
    }
    if (count($messages) > 1) {
      $output .= '<ul>';
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . '</li>';
      }
      $output .= '</ul>';
    }
    else {
      $output .= $messages[0];
    }
    $output .= '</div>';
  }

  return $output;
}

/**
 * Returns HTML for primary and secondary local tasks.
 *
 * @ingroup themeable
 */
function material_admin_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<span class="element-invisible">' . t('Primary tabs') . '</span>';
    $variables['primary']['#prefix'] .= '<ul class="tabs tabs--primary  links--inline">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<span class="element-invisible">' . t('Secondary tabs') . '</span>';
    $variables['secondary']['#prefix'] .= '<ul class="tabs tabs--secondary links--inline">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }

  return $output;
}

/**
 * Returns HTML for the status report.
 *
 * @param $variables
 *   An associative array containing:
 *   - requirements: An array of requirements.
 *
 * @ingroup themeable
 */
function material_admin_status_report($variables) {
  $requirements = $variables['requirements'];
  $severities = array(
    REQUIREMENT_INFO => array(
      'title' => t('Info'),
      'class' => 'info',
    ),
    REQUIREMENT_OK => array(
      'title' => t('OK'),
      'class' => 'ok',
    ),
    REQUIREMENT_WARNING => array(
      'title' => t('Warning'),
      'class' => 'warning',
    ),
    REQUIREMENT_ERROR => array(
      'title' => t('Error'),
      'class' => 'error',
    ),
  );

  $status_icon = array(
    REQUIREMENT_OK => 'fa-check-circle',
    REQUIREMENT_ERROR => 'fa-times-circle',
    // @todo: Is there a better one?
    REQUIREMENT_INFO => 'fa-exclamation-triangle',
    REQUIREMENT_WARNING => 'fa-exclamation-triangle',
  );

  $output = '<table class="system-status-report">';

  foreach ($requirements as $requirement) {
    if (empty($requirement['#type'])) {
      $severity_level = isset($requirement['severity']) ? (int) $requirement['severity'] : 0;
      $severity = $severities[$severity_level];
      $severity['icon'] = '<i title="' . $severity['title'] . '" class="fa ' . $status_icon[$severity_level] . '"><span class="element-invisible">' . $severity['title'] . '</span></i>';

      // Output table row(s)
      if (!empty($requirement['description'])) {
        $output .= '<tr class="' . $severity['class'] . ' merge-down"><td class="status-icon">' . $severity['icon'] . '</td><td class="status-title">' . $requirement['title'] . '</td><td class="status-value">' . $requirement['value'] . '</td></tr>';
        $output .= '<tr class="' . $severity['class'] . ' merge-up"><td colspan="3" class="status-description">' . $requirement['description'] . '</td></tr>';
      }
      else {
        $output .= '<tr class="' . $severity['class'] . '"><td class="status-icon">' . $severity['icon'] . '</td><td class="status-title">' . $requirement['title'] . '</td><td class="status-value">' . $requirement['value'] . '</td></tr>';
      }
    }
  }

  $output .= '</table>';
  return $output;
}
