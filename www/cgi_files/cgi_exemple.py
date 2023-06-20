# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    cgi_exemple.py                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 15:45:56 by fech-cha          #+#    #+#              #
#    Updated: 2023/06/21 00:41:50 by fech-cha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/usr/local/bin/python3
import cgi
import os

form = cgi.FieldStorage()

# produce http header
print("HTTP/1.1 200 OK\r")
print("Content-type: text/html\r\n\r")

# output the html
a = """
<html>
<head>
    <title>Document</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f2f2f2;
            margin: 0;
            padding: 20px;
        }
        
        p {
            font-size: 18px;
            color: #333333;
            text-align: center;
        }
    </style>
</head>
<body>
    <p>
        Welcome to CGI!
    </p>
</body>
</html>
"""

print(a)

