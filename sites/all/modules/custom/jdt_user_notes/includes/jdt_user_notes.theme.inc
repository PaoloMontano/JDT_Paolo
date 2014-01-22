<?php
/**
 * @file
 * Functions for JDT User Notes Custom Theme.
 */

/**
 * Implements MODULE_preprocess_hook().
 * @param  int    $vars Passed from hook_menu().
 */
function jdt_user_notes_preprocess_jdt_user_notes_view(&$vars) {
  module_load_include('inc', 'jdt_user_notes', 'jdt_user_notes.api');
  $vars['jdt_articles'] = array();
  $vars['jdt_articles'] = $jdt_notes_ar = jdt_user_notes_get_user_article($vars['jdt_article_id']);
}

/**
 * Ajax call to add new JDT Note.
 * @param  int    $jdt_cid Node ID for content.
 * @param  String $ajax    Determined by %ctools wildcard in hook_menu().
 * @return String          Only if JavaScript is disabled.
 */
function jdt_user_notes_modal_add($jdt_cid, $ajax) {
  if ($ajax) {
    module_load_include('inc', 'jdt_user_notes', 'includes/jdt_user_notes.forms');
    ctools_include('modal');
    ctools_include('ajax');
    $modal_title = 'Add JDT Note';
    $modal_attributes = array(
      'class' => array(
        'ctools-close-modal',
      ),
    );
    $modal_content = drupal_get_form('jdt_user_notes_add_my_form', $jdt_cid);
    $modal_content['cancel'] = array(
      '#type' => 'button',
      '#value' => t('Cancel'),
      '#attributes' => $modal_attributes,
    );
    ctools_modal_render($modal_title, $modal_content);

  }
  else {
    $output = t("This isn't Ajax");
    return $output;
  }

}
