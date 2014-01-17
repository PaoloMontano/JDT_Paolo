<?php
/**
 * @file
 * Functions for JDT User Notes Custom Theme.
 */

/**
 * Returns all notes written for a specific note.
 * @param  int    $jdt_req Specific node ID.
 * @return Array           
 */
function jdt_user_notes_get_notes($jdt_req) {
  module_load_include('inc', 'jdt_user_notes', 'jdt_user_notes.api');
  $jdt_notes_ar = array();
  $jdt_notes_ar = jdt_user_notes_get_user_article($jdt_req);
  return $jdt_notes_ar;
}
