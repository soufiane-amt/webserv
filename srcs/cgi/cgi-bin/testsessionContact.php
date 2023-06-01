<?php 
    session_start();
?>

<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>Session PHP</title>
    </head>
    <body>
        <ul>
            <li><a href="testsession.php">HOME</li>
            <li><a href="testsessionContact.php">CONTACT</li>
        </ul>
        <?php
         echo $_SESSION['userName'];
        ?>
    </body>
</html>