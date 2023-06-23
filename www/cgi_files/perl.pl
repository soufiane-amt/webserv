#!/usr/bin/perl

local ($buffer, @pairs, $pair, $name, $value, %FORM);
# Read in text
$ENV{'REQUEST_METHOD'} =~ tr/a-z/A-Z/;
if ($ENV{'REQUEST_METHOD'} eq "POST") {
   read(STDIN, $buffer, $ENV{'CONTENT_LENGTH'});
} else {
   $buffer = $ENV{'QUERY_STRING'};
}
# Split information into name/value pairs
@pairs = split(/&/, $buffer);
foreach $pair (@pairs) {
   ($name, $value) = split(/=/, $pair);
   $value =~ tr/+/ /;
   $value =~ s/%(..)/pack("C", hex($1))/eg;
   $FORM{$name} = $value;
}
$subject = $FORM{dropdown};

print "HTTP/1.1 200 OK\r\n";
print "Content-type: text/html\r\n\r\n";
print "\r\n";
print "<html>";
print "<head>";
print "<title>Dropdown Box - Sixth CGI Program</title>";
print "<style>";
print "    body {";
print "        font-family: Arial, sans-serif;";
print "        background-color: #f2f2f2;";
print "        margin: 0;";
print "        padding: 20px;";
print "    }";
print "";
print "    h2 {";
print "        color: #333;";
print "        font-size: 24px;";
print "        margin-top: 0;";
print "        text-align: center;";
print "    }";
print "</style>";
print "</head>";
print "<body>";
print "<h2> Selected Subject is $subject</h2>";
print "</body>";
print "</html>";

1;