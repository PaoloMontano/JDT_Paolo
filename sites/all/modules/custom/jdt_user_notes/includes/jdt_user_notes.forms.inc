<?php

/**
 * Associative array for new notes form.
 * @return Associative Array for New Notes form.
 */
function jdt_user_notes_add_my_form($node, &$form_state, $jdt_node) {
  global $user;
  $form['jdt_form_new'] = array(
    '#type' => 'fieldset',
    '#title' => t('New JDT User Notes'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  if (!node_load($jdt_node)) {
    form_set_error('jdt_form_new', 'Article does not exist');
  } else {
    $form['jdt_form_new']['jdt_u_uid'] = array(
      '#type' => 'textfield',
      '#title' => t('User ID'),
      '#default_value' => $user->uid,
      '#size' => 3,
      '#maxlength' => 3,
      '#disabled' => TRUE,
    );
    $form['jdt_form_new']['jdt_article_id'] = array(
      '#type' => 'textfield',
      '#title' => t('JDT Article Node ID'),
      '#default_value' => $jdt_node,
      '#disabled' => TRUE,
      '#size' => 4,
      '#maxlength' => 4,
    );
    $form['jdt_form_new']['jdt_user_note'] = array(
      '#type' => 'textarea',
      '#title' => 'Your user notes.',
      '#required' => TRUE,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Submit',
    );
  }
  return $form;
}

/**
 * Associative array for edit notes form.
 * @return Associative Array for Edit Notes form.
 */
function jdt_user_notes_edit_my_form($node, &$form_state, $jdt_cid) {
  $form['jdt_form_edit'] = array(
    '#type' => 'fieldset',
    '#title' => t('Edit a JDT Note'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  module_load_include('inc', 'jdt_user_notes', 'jdt_user_notes.api');
  if (!jdt_user_notes_check_note_id($jdt_cid)) {
    form_set_error('jdt_form_edit', 'Not a valid Note ID.');
    return $form;
  } else {
    $form['jdt_form_edit']['jdt_article_id'] = array(
      '#type' => 'textfield',
      '#title' => t('Edit JDT Article ID'),
      '#default_value' => jdt_user_notes_get_nid($jdt_cid),
      '#size' => 4,
      '#maxlength' => 4,
      '#disabled' => TRUE,
    );
    $form['jdt_form_edit']['jdt_note_id'] = array(
      '#type' => 'textfield',
      '#title' => 'Edit JDT Note ID',
      '#default_value' => $jdt_cid,
      '#disabled' => TRUE,
      '#size' => 3,
      '#maxlength' => 3,
    );
    $form['jdt_form_edit']['jdt_user_note'] = array(
      '#type' => 'textarea',
      '#title' => 'Edit user notes.',
      '#default_value' => jdt_user_notes_get_note($jdt_cid),
      '#required' => TRUE,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Submit',
    );
    return $form;
  }
}

/**
 * Add new note submit function for when the submit button is clicked.
 * @param  Array  $form       Form representation from Form API.
 * @param  Array  $form_state Form representation about Form.
 */
function jdt_user_notes_add_my_form_submit($form, &$form_state) {
  module_load_include('inc', 'jdt_user_notes', 'jdt_user_notes.api');
  jdt_user_notes_insert_vals($form_state['values']);
  drupal_set_message('Note ID: '.jdt_user_notes_get_note_id());
}

/**
 * Edit note submit function for when the submit button is clicked.
 * @param  Array  $form       Form representation from Form API.
 * @param  Array  $form_state Form representation about Form.c
 */
function jdt_user_notes_edit_my_form_submit($form, &$form_state) {
  module_load_include('inc', 'jdt_user_notes', 'jdt_user_notes.api');
  jdt_user_notes_edit_vals($form_state['values']);
  drupal_set_message(
    'Note ID: '.$form_state['values']['jdt_note_id'].' has been changed.'
  );
}
