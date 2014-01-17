<?php
/**
 * @file
 * Template for JDT User Notes
 */
?>

<?php if (arg(0) == 'node' && is_numeric($jdt_req = arg(1))): ?>
  <br />
  <?php $jdt_notes_array = jdt_user_notes_get_notes($jdt_req); ?>
  <?php foreach ($jdt_notes_array as $jdt_note): ?>
    <p><?php print $jdt_note[1]; ?></p>
    <p><a href="./jdt_user_note_edit/<?php print $jdt_note[0]; ?>">Edit this note</a></p>
    <br />
  <?php endforeach; ?>
<?php endif; ?>
