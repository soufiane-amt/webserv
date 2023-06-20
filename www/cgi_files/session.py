#!/usr/local/bin/python3

import cgi
import hashlib, datetime, os
from http import cookies

form = cgi.FieldStorage()

first_name = form.getvalue('first_name')
last_name  = form.getvalue('last_name')


expires = datetime.datetime.now() + datetime.timedelta(days=365)

cookie = cookies.SimpleCookie()
client_cookie = cookies.SimpleCookie()

string_cookie = os.environ.get('HTTP_COOKIE')
# Load the client's cookies into the cookie object
if string_cookie:
    client_cookie.load(string_cookie)

if not client_cookie.get('sid'):
    # The sid will be a hash of the server time
    sid = hashlib.sha256(repr(datetime.datetime.now()).encode('utf-8')).hexdigest()
    # Set the cookie with the session ID and expiration date
    cookie['sid'] = sid
    cookie['sid']['expires'] = expires.strftime("%a, %d-%b-%Y %H:%M:%S PST")
    cookie['sid']['path'] = '/'
    cookie['sid']['HttpOnly'] = True;

# print(cookie)
print("HTTP/1.1 200 OK\r")
print("Content-type: text/html\r\n\r")
print('<html><body>')
print ("<h1>Session of  %s %s</h1>" % (first_name, last_name))
if client_cookie.get('sid'):
    print('<p>Welcome back!</p>')
else:
    print('<p>First time here?</p>')
print('</body></html>')