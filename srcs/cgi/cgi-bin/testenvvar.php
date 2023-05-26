<?php

print "<html>";
print "<head>";
print "<title>Testing env vars</title>";
print "</head>";
print "<body>";

    if ($_SERVER['REQUEST_METHOD'] == 'GET')
        print "<h2>CGI Script is using GET Method </h2>";
    else if ($_SERVER['REQUEST_METHOD'] == 'POST')
        print "<h2>CGI Script is using POST Method </h2>";

print "</body>";

?>