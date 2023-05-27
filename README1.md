This section is an introduction to the HTTP protocol.


The world’s web browsers, servers, and related web applications all talk to each
other through HTTP, the Hypertext Transfer Protocol. HTTP is the common language of the modern global Internet.


Web Clients and Servers:
Web content lives on web servers. Web servers speak the HTTP protocol, so they are
often called HTTP servers. These HTTP servers store the Internet’s data and provide
the data when it is requested by HTTP clients. The clients send HTTP requests to
servers, and servers return the requested data in HTTP responses.


When you browse to a page, such as “http://www.server.com/index.html,” your
browser sends an HTTP request to the server www.server.com . The
server tries to find the desired object (in this case, “/index.html”) and, if successful,
sends the object to the client in an HTTP response, along with the type of the object,
the length of the object, and other information.


Web Resources
Web servers host web resources. A web resource is the source of web content. The
simplest kind of web resource is a static file on the web server’s filesystem. These
files can contain anything: they might be text files, HTML files, Microsoft Word
files, Adobe Acrobat files, JPEG image files, AV or any other format you
can think of.
However, resources don’t have to be static files. 
Resources can also be software programs that generate content on demand (e.g. CGI's).


Media Types
Because the Internet hosts many thousands of different data types, HTTP carefully
tags each object being transported through the Web (http meassage) with a data format label a (header field) called a
MIME type. 
MIME (Multipurpose Internet Mail Extensions) was originally designed
to solve problems encountered in moving messages between different electronic mail
systems. MIME worked so well for email that HTTP adopted it to describe and label
its own multimedia content

When a web browser gets an object back from a server, it looks at the associated MIME type
to see if it knows how to handle the object. Most browsers can handle hundreds of
popular object types: displaying image files, parsing and formatting HTML files,
playing audio files through the computer’s speakers, or launching external plug-in
software to handle special formats.





URI and a URL:
Let me provide an example to clarify the difference between a URI and a URL:

URI: isbn:978-0-13-475759-9
Explanation: This URI represents the unique identifier for a book using the "isbn" scheme.
It identifies the book using its International Standard Book Number (ISBN). However, it doesn't provide a specific location
or address on the web. It is a URI because it identifies a resource (in this case, a book) using a unique identifier (the ISBN), but it is not a URL because it doesn't include the necessary components (such as the scheme, domain name, and path) to locate the book on the web.

In contrast, let's consider a URL example:

URL: https://www.example.com/images/picture.jpg
Explanation: This URL represents the address of an image file on the web. It begins with the scheme "https://" and includes the domain name "www.example.com." The path "/images/picture.jpg" specifies the specific location of the image file within the website's directory structure. This is a URL because it provides both the scheme and the necessary components to locate and access the image file on the internet.

To summarize, the main difference is that a URI is a generic identifier for a resource, while a URL is a specific type of URI that includes the necessary components to locate and access a resource on the web.


Messages
Now let’s take a quick look at the structure of HTTP request and response messages.
HTTP messages are simple, line-oriented sequences of characters. Because they are
plain text, not binary, they are easy for humans to read and write.

####################
Client Request:
GET /test/hi-there.txt HTTP/1.1
Accept: text/*
Accept-Language: en,fr

###################
Server Response:
HTTP/1.0 200 OK
Content-type: text/plain
Content-length: 19

Hi! I’m a message!

-----

HTTP messages sent from web clients to web servers are called request messages.
Messages from servers to clients are called response messages.

HTTP messages consist of three parts:

*Start line
The first line of the message is the start line, indicating what to do for a request
or what happened for a response.
e.g : GET /test/hi-there.txt HTTP/1.1



*Header fields
header fields follow the start line. Each header field consists of a
name and a value, separated by a colon (:) for easy parsing. The headers end
with a blank line. Adding a header field is as easy as adding another line.
e.g: Host: servername

*Body
it contains a plain text, html page , image, or any binary file and any format support of MEMI supported by the user-agent(browser)


