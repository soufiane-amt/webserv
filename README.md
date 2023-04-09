# webserv
This is when you finally understand why a URL starts with HTTP!


What is an RFC?

RFCs are often the result of collaborative efforts among members of the technical community, who contribute their expertise and feedback to refine a proposal. It is the type of document that is used by technical community to propose new ideas, standars, protocols and provide solutions for given problems RFCs are published by the Internet Engineering Task Force (IETF) and other organizations involved in developing and maintaining Internet standards.
RFC contains technical specifications about a certain problem and provides solutions and new ideas to help solving it, 

//RFC ressource. https://www.rfc-editor.org/rfc/rfc2616

Why is RFC important?

As I mentiend before the RFC is a document that provide specification about a protocol It is a type of reference to any developer that includes guidance on best practices and common pitfalls and dangers to avoid when implementing a protocol or standard. By following these recommendations, you can improve the performance, secURIty, and reliability of your software.

if you are creating a server, you may need to implement a protocol such as HTTP to communicate with other servers and clients. The RFCs that describe these protocols provide detailed  specifications that you can follow to ensure that your server is compliant with the protocol and can interoperate with other servers and clients.

RFC && Http ?
the HTTP protocol was first proposed in RFC 1945 in May 1996, and has since been revised and updated in subsequent RFCs to reflect changes and improvements to the protocol.


The http protocol belongs to the Application layer of the OSI model , and even if we implement it, it will not be able to do its job wthout t its  Transport Layer  which is TCP protocol.

TCP implemenation :
To implement TCP, we have to learn TCP socket programming first .

What is a socket?

A socket it a mechanism that provides computer applications a way to the Network, it is an end point communication between two or more  processes (or Applications  ) from and to anywhere in the world (e.g, sending an email to a friend) .

It allows messages to be sent and received between applications ,  A good  analogy of creating a socket is that of requesting a telephone line from the phone company.



/******* Request and Response ********/
Http protocol plays the role of communication language between the server and client(s) to implement is properly we have to receive a request and prepare and send a response :
To do that we have to:

-Get the request and parse it ;


//getmime_type
application/octet-stream is a MIME type that is used to indicate that the data in a file is in binary format and cannot be easily interpreted or displayed as text. The MIME type consists of two parts: "application" indicates that the data is an application-level data, and "octet-stream" indicates that the data is a stream of arbitrary bytes.

In practical terms, application/octet-stream is often used as a catch-all MIME type for files that cannot be identified by their extension or for files that do not fit into any other defined MIME type. For example, if a server receives a file with an unknown extension, it may set the MIME type to application/octet-stream to indicate that the file is binary data that cannot be directly displayed by a web browser.

In most cases, application/octet-stream is used as a default MIME type when the server does not know the specific MIME type of a file or when the file format is not a recognized type. However, it is generally recommended to use more specific MIME types whenever possible to ensure that the client application can correctly interpret and handle the data.








/*** Random***/
idempotent Mothods :

Methods that you call as many times as you wnat without changing the server state (data base associated with the server) are called idempotent like GET PUT DELETE
non-idempotent like post 



/*Request Header structure*/
Request       = Request-Line              ; Section 5.1
                        *(( general-header        ; Section 4.5
                         | request-header         ; Section 5.3
                         | entity-header ) CRLF)  ; Section 7.1
                        CRLF
                        [ message-body ]          ; Section 4.3
Request-Line: This is the first line of an HTTP request message, and it includes the HTTP method, the URL or path of the requested resource, and the HTTP version being used. For example, GET /index.html HTTP/1.1.

general-header: These are headers that can be used in both request and response messages, such as Date, Cache-Control, and Connection.

request-header: These are headers specific to HTTP request messages, such as User-Agent, Host, and Accept.

entity-header: These are headers that describe the content or encoding of the message body, such as Content-Type, Content-Length, and Content-Encoding.

CRLF: This represents a carriage return (\r) followed by a line feed (\n), which is used to indicate the end of a line in HTTP messages.

message-body: This is the optional data that can be included in an HTTP request message, such as form data or file uploads.

So, in summary, the definition you provided describes the structure of an HTTP request message, which includes a request line, a series of headers (which can be general, request-specific, or entity-specific), a blank line (indicated by CRLF), and an optional message body.





Autoindex:
I have found out a little detail about autoindex, however very important if the location defined in config file 
has autoindex on anything typed in the search bar after that location will support autoindexing .e.g
location /
{
    autoindex on;
}
----> localhost:8080/  <<---this will display a list of files in the repo
----> localhost:8080/An/Other/Folder/  <<---this will display a list of files in the repo as long as the path is valid 


//Questions
what is  a domaine and a subdomaine 
why URL starts with www
MIME