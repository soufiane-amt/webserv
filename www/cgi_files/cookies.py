#!/usr/bin/env python
from http import cookies
import datetime
import os

values = {'a': 'a', 'b': 'b'}
expires = datetime.datetime.now() + datetime.timedelta(days=365)

client_cookie = cookies.SimpleCookie()
string_cookie = os.environ.get('HTTP_COOKIE')
# Load the client's cookies into the cookie object
if string_cookie:
    client_cookie.load(string_cookie)

cookie = cookies.SimpleCookie()
for key in values:
    cookie[key] = values[key]
    cookie[key]['expires'] = expires.strftime("%a, %d-%b-%Y %H:%M:%S PST")
    cookie[key]['path'] = '/'
    cookie[key]['HttpOnly'] = True


# Output the HTTP message containing the cookie
print("HTTP/1.1 200 OK\r")
print("Content-type: text/html")
print(cookie)
print()
print('<html>')
print('<head>')
print('    <title>Set Cookie</title>')
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
if len(client_cookie) == 0:
    print('<h1>Cookie: Not Set</h1>')
else:
    for key in values:
        print('<h1>Cookie: %s = %s</h1>' % (key, values[key]))
print('</body>')
print('</html>')