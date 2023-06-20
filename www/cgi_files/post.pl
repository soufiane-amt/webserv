#!/usr/bin/perl

use CGI qw(:standard);

print "HTTP/1.1 200 OK\r\n";
print "Content-type: text/html\r\n\r\n";
print "\r\n";
print "<html>";
print "<head>";
print "<title>Hello py cgi</title>";
print "</head>";
print "<body>";

if ($ENV{'REQUEST_METHOD'} eq 'POST') {
    print "<H1>hello " . param("first_name") . " " . param("last_name") . "</H1>";
}

print "Testing <b>Perl CGI Programming in webserv</b></p>";

print "</body>";
print "</html>";