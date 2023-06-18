#!/usr/bin/env python

import cgi
import cgitb
cgitb.enable()

print("HTTP/1.1 200 OK\r")
print("Content-type: text/html\r\n\r")

print("""
<html>
<head>
<title>File Upload</title>
</head>
<body>
<h1>File Upload</h1>
<form enctype="multipart/form-data" method="post" action="up2.py">
    <input type="file" name="file" />
    <input type="submit" value="Upload" />
</form>
</body>
</html>
""")

form = cgi.FieldStorage()

if "file" in form:
    file_item = form["file"]
    
    # Check if the file was uploaded
    if file_item.filename:
        # Save the file to a desired location
        file_path = '/path/to/save/' + file_item.filename
        with open(file_path, 'wb') as file:
            file.write(file_item.file.read())
        
        print("<p>File uploaded successfully!</p>")
        print("<p>Uploaded file name: {}</p>".format(file_item.filename))
        print("<p>Uploaded file size: {} bytes</p>".format(file_item.file_size))
    else:
        print("<p>No file was uploaded.</p>")
else:
    print("<p>Please choose a file to upload.</p>")