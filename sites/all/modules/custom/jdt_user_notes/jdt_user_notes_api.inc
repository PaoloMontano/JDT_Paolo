<?php
/**
 * @file
 * JDT User Notes API
 */
/**
 * Implements hooks_permission to determine if current user has sufficient
 * permission to access jdt_user_notes database.
 * @return Array 
 */
function jdt_user_notes_permission() {
  return array(
    'administer jdt_user_notes' => array(
      'title' => 'Administer of jdt_user_notes',
      'description' => 'Add user notes to JDT Content Articles',
    ),
  );
}

/**
 * Retrieves the current count of user notes created.
 * @return int Current number of user notes.
 */
function jdt_user_notes_get_note_id() {
  $result = db_query(
    "SELECT COUNT(*)
     FROM {JDT_USER_NOTES_TABLE}"
  );
  return $result;
}

/**
 * Gets current nid for content.
 * @return int nid for current node.
 */
function jdt_user_notes_get_nid() {
  global $node;
  return $node->nid;
}

/**
 * Gets uid of current logged in user.
 * @return int Current user's uid.
 */
function jdt_user_notes_get_uid() {
  global $user;
  return $user->uid;
}

function jdt_user_notes_insert_vals($form) {
  $ar_vals = array(
    'article_id' => $form['jdt_article_id'],
    'author_id' => $form['jdt_u_uid'],
    'note_text' => $form['jdt_user_note'],
  );
  drupal_write_record('jdt_user_notes', $ar_vals);
}
