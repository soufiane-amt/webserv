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
         $_SESSION['userName'] = "fechcha69";
         echo $_SESSION['userName'];

         if (!isset($_SESSION['userName']))
         {
            echo "Not logged in!";
         }
         else
        {
            echo "Logged in";
        }
        ?>
    </body>
</html>