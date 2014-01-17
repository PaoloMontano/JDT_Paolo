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
