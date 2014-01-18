<?php
/**
 * @file
 * JDT User Notes API
 */

/**
 * Implements hooks_permission to determine if current user has sufficient
 * permission to access jdt_user_notes database.
 * @return Array Drupal user permissions.
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
    'SELECT MAX(note_id) AS current_note
     FROM {jdt_user_notes}'
  );
  $jdt_int_val = $result->fetchAssoc();

  return $jdt_int_val['current_note'];
}

/**
 * Gets current nid for content.
 * @return int nid for current node.
 */
function jdt_user_notes_get_nid($jdt_cid) {
  $result = db_query(
    'SELECT article_id
     FROM {jdt_user_notes}
     WHERE note_id = :note_cid',
    array('note_cid' => $jdt_cid)
  );
  $jdt_int_val = $result->fetchAssoc();
  return $jdt_int_val['article_id'];
}

/**
 * Gets user text from specific note ID.
 * @param  Int    $jdt_note_id Unique Note ID.
 * @return String              User note text.
 */
function jdt_user_notes_get_note($jdt_note_id) {
  $result = db_query(
    'SELECT note_text AS user_note
     FROM   {jdt_user_notes}
     WHERE  note_id = :content',
    array(
      ':content' => $jdt_note_id
    )
  );
  $jdt_string_val = $result->fetchAssoc();
  return $jdt_string_val['user_note'];
}

/**
 * Inserts a new JDT User Note.
 * @param  Array $form Form representation from Form API.
 */
function jdt_user_notes_insert_vals($form) {
  $ar_vals = array(
    'article_id' => $form['jdt_article_id'],
    'author_id'  => $form['jdt_u_uid'],
    'note_text'  => $form['jdt_user_note'],
  );
  drupal_write_record('jdt_user_notes', $ar_vals);
}

/**
 * [jdt_user_notes_edit_vals description]
 * @param  Array $form Form representation from Form API.
 */
function jdt_user_notes_edit_vals($form) {
  db_update('jdt_user_notes')
  ->fields(
    array(
      'note_text' => $form['jdt_user_note'],
    )
  )
  ->condition('note_id', $form['jdt_note_id'])
  ->execute();
}

/**
 * Checks if Note ID exists.
 * @param  int    $jdt_note_id Unique Note ID
 * @return int                 Note_ID from database schema.
 */
function jdt_user_notes_check_note_id($jdt_note_id) {
  $result = db_query(
    'SELECT note_id AS ID
     FROM {jdt_user_notes}
     WHERE note_id = :jdt_req',
    array('jdt_req' => $jdt_note_id)
  );
  $jdt_return_value = $result->fetchAssoc();
  return $jdt_return_value['ID'];
}

/**
 * Returns an array of JDT User notes containing its Note ID and Note Text.
 * @param  int    $jdt_req Node ID being requested.
 * @return Array           Index array which contains Note ID and Note Text.
 */
function jdt_user_notes_get_user_article($jdt_req) {
  $jdt_test = array();
  $results = db_query(
    'SELECT note_id, note_text
     FROM {jdt_user_notes}
     WHERE article_id = :req',
    array('req' => $jdt_req)
  );
  while ($single = $results->fetchAssoc()) {
    $jdt_test[] = array(
      'note_text' => $single['note_text'],
      'note_link' => l('Edit this note', 'node/' . $jdt_req . '/jdt_user_note_edit/' . $single['note_id']),
      'note_div' => 'jdt_div_' . $single['note_id'],
    );
  }
  return $jdt_test;
}
