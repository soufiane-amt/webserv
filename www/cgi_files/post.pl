#!/usr/bin/perl

use CGI qw(:standard);

print "HTTP/1.1 200 OK\r\n";
print "Content-type: text/html\r\n\r\n";
print "\r\n";
print "<html>";
print "<head>";
print "<title>Hello py cgi</title>";
print "<style>";
print "    body {";
print "        font-family: Arial, sans-serif;";
print "        background-color: #f2f2f2;";
print "        margin: 0;";
print "        padding: 20px;";
print "    }";
print "";
print "    h1 {";
print "        color: #333;";
print "        font-size: 32px;";
print "        margin-top: 50px;";
print "        text-align: center;";
print "    }";
print "";
print "    p {";
print "        color: #666;";
print "        font-size: 18px;";
print "        margin-top: 20px;";
print "    }";
print "</style>";
print "</head>";
print "<body>";

if ($ENV{'REQUEST_METHOD'} eq 'POST') {
    print "<h1>Hello " . param("first_name") . " " . param("last_name") . "</h1>";
}

print "<p>Testing <b>Perl CGI Programming in webserv</b></p>";

print "</body>";
print "</html>";