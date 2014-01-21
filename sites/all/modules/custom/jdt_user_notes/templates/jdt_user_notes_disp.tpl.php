<?php
/**
 * @file
 * Template for JDT User Notes
 */
?>

<?php foreach ($jdt_articles as $jdt_article): ?>
  <br />
  <p><?php print $jdt_article['note_text']; ?></p>
  <!-- <p><?php print $jdt_article['note_link']; ?></p> -->
  <div id="<?php print $jdt_article['note_div']; ?>"></div>
  <div id="<?php print $jdt_article['note_ajax_div']; ?>">
    <?php print $jdt_article['note_ajax'] ?>
  </div>
  <br />

<?php endforeach; ?>
