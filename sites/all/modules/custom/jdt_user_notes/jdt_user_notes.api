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
    'SELECT MAX(note_id) AS HIGH
     FROM {jdt_user_notes}'
  );
  $jdt_int_val = $result->fetchAssoc();

  return $jdt_int_val['HIGH'];
}

/**
 * Gets current nid for content.
 * @return int nid for current node.
 */
function jdt_user_notes_get_nid($jdt_cid) {
  $result = db_query(
    'SELECT article_id AS jdt_nid
     FROM {jdt_user_notes}
     WHERE note_id = :note_cid',
     array('note_cid' => $jdt_cid)
  );
  $jdt_int_val = $result->fetchAssoc();
  return $jdt_int_val['jdt_nid'];
}

/**
 * [jdt_user_notes_get_note description]
 * @param  Int    $jdt_cid Unique Note ID.
 * @return String          User note text.
 */
function jdt_user_notes_get_note($jdt_cid) {
  $result = db_query(
    'SELECT note_text AS user_note
     FROM   {jdt_user_notes}
     WHERE  note_id = :content',
    array(
      ':content' => $jdt_cid
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
 * @return int                 Note_ID from {jdt_user_notes}
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
