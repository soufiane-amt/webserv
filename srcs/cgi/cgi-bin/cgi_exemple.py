# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    cgi_exemple.py                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 15:45:56 by fech-cha          #+#    #+#              #
#    Updated: 2023/05/25 15:45:57 by fech-cha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!python

#produce http header 
print("Content-type: text/html\r\n")
print("\r\n")

#output the html 
a = """
<!DOCTYPE html>
<head>
    <title>Document</title>
</head>
<body>
    <p>
      this is a test
    </p>
</body>
</html>
""";

print(a);

