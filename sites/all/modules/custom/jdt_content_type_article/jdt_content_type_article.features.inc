<?php
/**
 * @file
 * jdt_content_type_article.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function jdt_content_type_article_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function jdt_content_type_article_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function jdt_content_type_article_image_default_styles() {
  $styles = array();

  // Exported image style: jdt_image.
  $styles['jdt_image'] = array(
    'name' => 'jdt_image',
    'label' => 'JDT Image',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 200,
          'height' => 200,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function jdt_content_type_article_node_info() {
  $items = array(
    'jdt_article' => array(
      'name' => t('JDT Article'),
      'base' => 'node_content',
      'description' => t('Junior Developer Tasks - Article
Using Features'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
