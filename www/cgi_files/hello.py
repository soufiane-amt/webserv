#!/usr/local/bin/python3
# Import modules for CGI handling
import cgi
# Create instance of FieldStorage
form = cgi.FieldStorage()

first_name = form.getvalue('first_name')
last_name  = form.getvalue('last_name')

print("HTTP/1.1 200 OK\r")
print("Content-type: text/html\r\n\r")
print ("\r\n")
print ("<html>")
print ("<head>")
print ("<title>Hello py cgi</title>")
print ("</head>")
print ("<body>")
print ("<h1>Hello %s%s</h1>" % (first_name, last_name))
print ("</body>")
print ("</html>")