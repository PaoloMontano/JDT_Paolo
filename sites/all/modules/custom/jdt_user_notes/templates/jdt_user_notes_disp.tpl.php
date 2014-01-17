<?php
/**
 * @file
 * Template for JDT User Notes
 */
?>

<?php foreach ($jdt_articles as $jdt_article): ?>
  <br />
  <p><?php print $jdt_article[1]; ?></p>
  <p><?php print l('Edit this note', 'node/' . $jdt_article_id . '/jdt_user_note_edit/' . $jdt_article[0]) ?></p>
<?php endforeach; ?>
