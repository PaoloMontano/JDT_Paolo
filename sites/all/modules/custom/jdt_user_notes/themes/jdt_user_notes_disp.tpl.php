<?php
/**
 * @file
 * Template for displaying user notes.
 */
  if (arg(0) == 'node' && is_numeric($jdt_req = arg(1))) {
    print '<br />';
    $jdt_notes_array = jdt_user_notes_get_notes($jdt_req);
    foreach ($jdt_notes_array as $jdt_note) {
      print '<p>' . $jdt_note[1] . '</p>';
      print '<p><a href="./jdt_user_note_edit/' . $jdt_note[0] . '">edit this note</a></p>';
      print '<br />';
    }
  }
?>
