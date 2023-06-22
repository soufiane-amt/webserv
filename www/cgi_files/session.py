#!/usr/local/bin/python3

import sys
import cgi
import hashlib
import datetime
import os
from http import cookies

form = cgi.FieldStorage()

first_name = form.getvalue('first_name')
last_name = form.getvalue('last_name')

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
    cookie['sid']['HttpOnly'] = True

print("HTTP/1.1 200 OK\r")
print("Content-type: text/html")
print(cookie)
print()
print('<html>')
print('<head>')
print('    <title>Session</title>')
print('    <style>')
print('        body {')
print('            font-family: Arial, sans-serif;')
print('            background-color: #222;')
print('            margin: 0;')
print('            padding: 20px;')
print('        }')
print('')
print('        h1 {')
print('            color: #fff;')
print('            font-size: 32px;')
print('            margin-top: 0;')
print('            text-align: center;')
print('        }')
print('')
print('        p {')
print('            color: #ccc;')
print('            font-size: 18px;')
print('            margin-top: 20px;')
print('            text-align: center;')
print('        }')
print('    </style>')
print('</head>')
print('<body>')
print('    <h1>Session of %s %s</h1>' % (first_name, last_name))
if client_cookie.get('sid'):
    print('    <p>Welcome back!</p>')
else:
    print('    <p>First time here?</p>')
print('</body>')
print('</html>')