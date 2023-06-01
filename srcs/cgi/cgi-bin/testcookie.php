
<html>
<body>
<title>Cookie testing</title>    
    
<?php

/*Cookies and Sessions*/
//Cookies are on the user interface (browser) and they have a time limit of survival
//Sessions are on the server, and they end as soon as you close your browser

//making cookies                        day in ms
setcookie("cookieName", "cookieValue", time() + 86400);
//destroy cookies
setcookie("cookieName", "cookieValue", time() - 1);

//making sessions           //sessionID
$_SESSION['sessionName'] = "69";

?>

</body>
</html>