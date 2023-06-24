#!/usr/local/bin/python3

import cgi

print("HTTP/1.1 200 OK\r")
print("Content-type: text/html\r\n\r")
print("<html>")
print("<head>")
print('<title style="color: #2c3e50; font-family: Arial, sans-serif;">CGI Programming is Fun</title>')
print('<link rel="stylesheet" type="text/css" href="styles.css">')
print("</head>")
print('<body style="background-color: #ecf0f1;">')
print('<div class="container">')
print('<h1 style="color: #3498db; font-family: Impact, Charcoal, sans-serif; text-shadow: 2px 2px #e67e22;">Welcome To Webserv CGI Execution!</h1>')

form = cgi.FieldStorage()

if form.getvalue("name"):
    name = form.getvalue("name")
    print('<h2>Hi <span class="name" style="color: #e74c3c; font-size: 28px;">' + name + '</span>! Enjoy our experience :)</h2><br>')
if form.getvalue("Linux"):
    print('<p class="message" style="color: #27ae60; font-weight: bold;">Man of culture!</p>')
if form.getvalue("Windows"):
    print('<p class="message" style="color: #c0392b; font-style: italic;">Trash!</p>')

print('<form method="post" action="cgi_second.py">')
print('<p class="form-field">Name: <input type="text" name="name" style="border: 1px solid #ccc; border-radius: 4px; padding: 8px;"></p>')
print('<input type="checkbox" name="Linux"/> <span class="checkbox-label" style="font-weight: bold;">Linux</span>')
print('<input type="checkbox" name="Windows"/> <span class="checkbox-label" style="font-weight: bold;">Windows</span>')
print('<input type="Submit" value="Submit" class="submit-btn" style="background-color: #2980b9; color: #fff; border: none; border-radius: 4px; padding: 10px 20px; cursor: pointer;">')
print("</form>")

print("</div>")
print("</body>")
print("</html>")