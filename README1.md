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


http different versions:

HTTP/1.0:

Connection: In HTTP/1.0, a separate connection is established for each request-response cycle. 
After the response is received, the connection is closed.

Persistent Connections: HTTP/1.0 does not have built-in support for persistent connections. 
This means that for each request, a new connection must be established, which can result in increased latency.
Request Pipelining: HTTP/1.0 does not support request pipelining. This means that the client has to wait for the response of one request before sending the next request.

Caching: Caching mechanisms in HTTP/1.0 are limited compared to later versions. It primarily relies on the "If-Modified-Since" header to determine if a resource has been modified since it was last requested.

HTTP/1.1:

Connection: HTTP/1.1 introduced persistent connections, allowing multiple requests to be sent over the same connection. 
This reduces the overhead of establishing new connections for each request.

Request Pipelining: HTTP/1.1 supports request pipelining, which means multiple requests can be sent without waiting for the response of each individual request. 
This helps in reducing latency and improving performance.

Chunked Transfer Encoding: HTTP/1.1 introduced the chunked transfer encoding mechanism, which allows the server to send data in chunks instead of sending the entire response at once. This enables better streaming and dynamic content delivery.

Host Header: HTTP/1.1 added the Host header, which allows multiple domains to be hosted on the same IP address, improving server efficiency.
Caching: HTTP/1.1 enhanced caching mechanisms by introducing cache control headers, such as "Cache-Control" and "ETag", providing more granular control over caching behavior.


HTTP/2:

Connection: HTTP/2 uses a binary framing layer that allows multiplexing of multiple requests and responses over a single connection. This eliminates the need for multiple connections and reduces latency.
Request Prioritization: HTTP/2 introduces request and response prioritization. It allows the client to assign priorities to different requests, ensuring that critical resources are delivered faster.
Server Push: HTTP/2 enables server push, where the server can proactively send resources to the client before they are requested. This can significantly improve page load times.
Header Compression: HTTP/2 introduces header compression, which reduces the overhead of header information, resulting in improved performance.
Stream Dependencies: HTTP/2 allows streams to depend on each other, enabling more efficient handling of dependencies between different resources.
Security: While HTTPS is optional in HTTP/1.x, HTTP/2 mandates the use of encryption over TLS (Transport Layer Security).
HTTP/2 is designed to be more efficient, faster, and better suited for modern web applications. Its features, such as multiplexing, prioritization, and server push, make it ideal for delivering complex web pages and reducing latency. However, it's important to note that HTTP/1.1 is still widely used, and the adoption of HTTP/2 depends on server and client support.






Accept headers
Accept headers give the client a way to tell servers their preferences and capabilities:
what they want, what they can use, and, most importantly, what they don’t want.
Servers can then use this extra information to make more intelligent decisions about
what to send. Accept headers benefit both sides of the connection. Clients get what
they want, and servers don’t waste their time and bandwidth sending something the
client can’t use. Table 3-14 lists the various accept headers.


Accept Tells the server what media types are okay to send
Accept-Charset Tells the server what charsets are okay to send
Accept-Encoding Tells the server what encodings are okay to send
Accept-Language Tells the server what languages are okay to send
TEa Tells the server what extension transfer codings are okay to use


Conditional request headers
Sometimes, clients want to put some restrictions on a request. For instance, if the client already has a copy of a document, it might want to ask a server to send the document only if it is different from the copy the client already has. Using conditional
request headers, clients can put such restrictions on requests, requiring the server to
make sure that the conditions are true before satisfying the request. Table 3-15 lists
the various conditional request headers.


Header Description
Expect Allows a client to list server behaviors that it requires for a request
If-Match Gets the document if the entity tag matches the current entity tag for the documenta
a See Chapter 7 for more on entity tags. The tag is basically an identifier for a version of the resource.
If-Modified-Since Restricts the request unless the resource has been modified since the specified date
If-None-Match Gets the document if the entity tags supplied do not match those of the current document
If-Range Allows a conditional request for a range of a document
If-Unmodified-Since Restricts the request unless the resource hasnot been modified since the specified date
Range Requests a specific range of a resource, if the server supports range requests.



Response Headers
Response messages have their own set of response headers. Response headers provide clients with extra information, such as who is sending the response, the capabilities of the responder, or even special instructions regarding the response. These
headers help the client deal with the response and make better requests in the future.
Table 3-18 lists the response informational headers.



TCP Connections.