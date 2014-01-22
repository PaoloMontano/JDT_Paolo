<?php
/**
 * @file
 * JDT User notes from Junior Drupal Tasks.
 */

/**
 * Associative array for new notes form.
 * @return Associative Array for New Notes form.
 */
function jdt_user_notes_add_my_form($node, &$form_state, $jdt_node) {
  $cur_user = $GLOBALS['user'];
  $form['jdt_form_new'] = array(
    '#type' => 'box',
    '#title' => t('New JDT User Notes'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  if (!node_load($jdt_node)) {
    form_set_error('jdt_form_new', 'Article does not exist');
  }
  else {
    $form['jdt_form_new']['jdt_u_uid'] = array(
      '#type' => 'textfield',
      '#title' => t('User ID'),
      '#default_value' => $cur_user->uid,
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
  }
  else {
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
  drupal_set_message(t('Note ID: ' . jdt_user_notes_get_note_id()));
}

/**
 * Edit note submit function for when the submit button is clicked.
 * @param  Array  $form       Form representation from Form API.
 * @param  Array  $form_state Form representation about Form.c
 */
function jdt_user_notes_edit_my_form_submit($form, &$form_state) {
  jdt_user_notes_edit_vals($form_state['values']);
  drupal_set_message(
    t('Note ID ' . $form_state['values']['jdt_note_id'] . ' has been changed.')
  );
}

/**
 * Ajax form that is created when user clicks on "Edit Note".
 * @param  Array  $form       Form representation from Form API.
 * @param  Array  $form_state Form representation about Form.
 * @param  int    $jdt_cid    Note ID.
 * @return Associative Array for Edit Notes form.
 */
function jdt_user_notes_ajax_form($form, &$form_state, $jdt_cid) {
  module_load_include('inc', 'jdt_user_notes', 'jdt_user_notes.api');
  $form['jdt_form_edit'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="jdt_div_' . $jdt_cid . '">',
    '#suffix' => '</div>',
  );
  $form['jdt_form_edit']['jdt_user_note'] = array(
    '#type' => 'textarea',
    '#default_value' => jdt_user_notes_get_note($jdt_cid),
    '#rows' => 8,
  );
  $form['jdt_form_edit']['jdt_note_id'] = array(
    '#type' => 'hidden',
    '#value' => $jdt_cid,
  );
  $form['jdt_form_edit']['submit'] = array(
    '#type' => 'submit',
    '#ajax' => array(
      'callback' => 'jdt_user_notes_ajax_callback',
      'method' => 'replace',
      'wrapper' => 'jdt_div_' . $jdt_cid,
      'effect' => 'slide',
    ),
    '#value' => t('Submit'),
  );
  return $form;
}

/**
 * Submit handler for Ajax form.
 * @param  Array  $form       Form representation from Form API.
 * @param  Array  $form_state Form representation about Form.
 */
function jdt_user_notes_ajax_form_submit($form, &$form_state) {
  module_load_include('inc', 'jdt_user_notes', 'jdt_user_notes.api');
  jdt_user_notes_edit_vals($form_state['values']);
}

/**
 * Ajax callback for Ajax form.
 * @param  Array  $form       Form representation from Form API.
 * @param  Array  $form_state Form representation about Form.
 * @return String             HTML Markup.
 */
function jdt_user_notes_ajax_callback($form, &$form_state) {
  $element['#markup'] = '<div id="jdt_div_' . $form_state['values']['jdt_note_id'] . '">';
  $element['#markup'] .= $form_state['values']['jdt_user_note'];
  $element['#markup'] .= '</div>';
  return $element;
}

/**
 * Renders a link with 'use-ajax' class.
 * @param  int    $jdt_cid Specific Note ID.
 * @return String          Drupal renderable link.
 */
function jdt_render_link($jdt_cid) {
  drupal_add_library('system', 'drupal.ajax');
  $link = l(
    t('Edit this note'),
    'jdt/' . $jdt_cid . '/jdt_ajax/nojs/',
    array(
      'attributes' => array(
        'class' => array('use-ajax'),
      )
    )
  );
  return $link;
}

/**
 * Ajax callback for when user clicks on "Edit this note".
 * @param  int    $jdt_cid Specific Note ID.
 * @param  String $type    Ajax for nojs
 * @return Rendderable     Drupal output.
 */
function jdt_link_response($jdt_cid, $type = 'ajax') {
  if ($type == 'ajax') {
    module_load_include('inc', 'jdt_user_notes', 'jdt_user_notes.api');
    $output = drupal_render(drupal_get_form('jdt_user_notes_ajax_form', $jdt_cid));
    $commands = array();
    $commands[] = ajax_command_replace('#jdt_div_' . $jdt_cid, $output);
    $page = array(
      '#type' => 'ajax',
      '#commands' => $commands,
    );
    ajax_deliver($page);
  }
  else {
    $output = t("This is some content delivered via a page load. JDT.");
    return $output;
  }
}
