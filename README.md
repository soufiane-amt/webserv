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


Why servers don't allow OPTIONS for security reasons
why sending post becomes an option request

how can a hacker take advantage  of http communication



why php lang was created 


understand the pattern of this request


POST /users/sign_in HTTP/1.1
Host: courses.pikuma.com
authority: courses.pikuma.com
accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
accept-language: fr-FR,fr;q=0.9
cache-control: max-age=0
content-type: application/x-www-form-urlencoded
cookie: visitor_id=1840790975; split=%7B%22beta_checkout%22%3A%22test%22%7D; _ga=GA1.1.740607860.1681142369; _ga=GA1.3.740607860.1681142369; _gid=GA1.3.968319808.1681142831; _gat_tenantTracker=1; _ga_T7VSHHFQGL=GS1.1.1681145367.2.1.1681145367.0.0.0; mp_e9f85a260e22673665c335ea07907e45_mixpanel=%7B%22distinct_id%22%3A%20%2216924c01c298d-09524324974757-36657105-13c680-16924c01c2ab2e%22%2C%22%24initial_referrer%22%3A%20%22https%3A%2F%2Fcourses.pikuma.com%2Fusers%22%2C%22%24initial_referring_domain%22%3A%20%22courses.pikuma.com%22%7D; _thinkific_session=TVU1eHFGMFlCOHRLT1J1NEpwTFpvVzVKcmVjRGwxT3lsVDQ4bnZ4NVNpMjZadStjZ1hoMXJUTVpyaWwzZlFtSitQY1MxMENhcnFCRXFkeHNPSVRndTRsTzJvdmhPeG5HWHQwUkF6SnpDS1BGbitqVFMzZGxYeHRSSUkzRFVkeUtlZ3BDcW5LdFUwcnFna3dzU0Ezc0hqc2JmUFJYUGg1TkdXbHBiQysxd0lwRklNTFlrNmRERDg5RUhhT1JsL0czQlJocW9EbEhYaktBcFRHWDloekU1dVg5Z21HSUxUc0paTkJBdldQRTJIKzRrT29nV1Vzd05RQmVwdHhkTENRSjRGT3A1UGVLamVqRENsZ24yYTlGTHNzOCtsbjRoazhURmZWS1FxM0hiZ0pVcmUyeno4M0U0ZElpNlFPcTYxVWd1cDJaaGszN1B5UjhkQW4yKzRiL2k5MkFqZXgrMVA4SDI4NXRXUHBOeUZzdFNLY0I0UVJxdWVDdkpFNjNiUHB5dG5udFlvQTJnZFBpeTRRU3hjRHNZaGU2SmEwajlPaG9QcUFnSzIxZDd2TGRFdjFMZjVaTGxSRVFkWng5dFRaTVl6SUtDTUpIMUVvU2R1bGgvcnA2UlJEVXozeC9KZ0cwTW5kdWxHcFByUFE9LS1DZWtPL2JFVHRSVEFrYkVnQnlrWTVnPT0%3D--f4ebb29e769438cfb963b86a51b4158610dde936; _thinkific_session=Ulhhd3Jia1FWbCt5VkhQWFlEK0R6cDBzT1VSMTBZQnpWZ1ZlZ3k0dXZoRzIxdjZqSXdaVDFaeHJRMWtEWlp5dmQ2MWMwWXJ0MDNOSndLaEIzUlJINTNoT1FYeTZCSFBremd6K21POTRBeGo1UmxaeXlpRkhDT3luOFI0SFUwajVVb3VtN0RYalpyT3lGVDRmZGo4NTFMU2ZmZFgzb2lrRGFZaDdkRWhqMnFRRG5oVWRWQTU3RkZRRHZNTlU0NFVnKzVneGNrblBGK1JZUGhLMTlaU2J5TkhlZDNlbGRmVDdTSTAyNGZoRGI1UjdBRnN6Wm15ZjRsRWVXU0NuS0h0WkFjbThURTB6aDNwYnZiWTM4Z1Rzak1yNll1M2FqVDlqakFtVHN4R2NrTWhRVFNOTldPMVFzOWpkZFFrYlV3WmxrVDc0dk5CelI4ajJsVVpIcVVrR3JuNi9NdVoyMGNHZXV0UE5KYjdEZkJzVzcwenVoRnN2RnNseWkvMjdORzFzdytRRFAzQ2pSWDlDZjlucGd4NlNIWjRTSTdWTEtUV2Z5MXhJNkhPM1pKSHlEbmF0VWZVa3ZBQUpGM0NKYkpId0JQU2psS0ZsL3ZEWjZVdnBiOG5iZUFvY2NUU3BmL3pvS0owNDg2MXUrK1k9LS05a1pwNVpjSXBUcGEyK2gwUTExbmdBPT0%3D--616128908a75d63c427fcc1f24694a040fc1df25; split=%7B%22beta_checkout%22%3A%22test%22%7D; visitor_id=1840798130
origin: https://courses.pikuma.com
referer: https://courses.pikuma.com/users/sign_in
sec-ch-ua: "Chromium";v="112", "Google Chrome";v="112", "Not:A-Brand";v="99"
sec-ch-ua-mobile: ?0
sec-ch-ua-platform: "macOS"
sec-fetch-dest: document
sec-fetch-mode: navigate
sec-fetch-site: same-origin
sec-fetch-user: ?1
upgrade-insecure-requests: 1
user-agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/112.0.0.0 Safari/537.36
Content-Length: 248

utf8=%E2%9C%93&authenticity_token=JNILdOpPMyaWiAOglWOawroANt9Xe75rjcRAavpnFFF%2FSp%2FamFt6eZJ9%2F%2BtmxJKKAagMcxKl%2Bd9XWq2SnUAqtQ%3D%3D&user%5Bemail%5D=soufianeamt11%40gmail.com&user%5Bpassword%5D=soufianeamt11%40gmail.comm&user%5Bremember_me%5D=


The Common Gateway Interface (CGI) provides the middleware between WWW servers and external databases and information sources. The World Wide Web Consortium (W3C) defined the Common Gateway Interface (CGI) and also defined how a program interacts with a Hyper Text Transfer Protocol (HTTP) server. The Web server typically passes the form information to a small application program that processes the data and may send back a confirmation message. This process or convention for passing data back and forth between the server and the application is called the common gateway interface (CGI). 




Connection: close
The close option signifies that either the client or server wishes to end
the connection (i.e., this is the last transaction). The keep-alive option
signifies that the client wishes to keep the connection open. The default
behavior of web applications differs between HTTP 1.0 and 1.1.
By default, HTTP 1.1 uses persistent connections, where the connection
does not automatically close after a transaction. When an HTTP 1.1 web
client no longer has any requests, or the server has reached some
preprogrammed limit in spending resources on the client, a
Connection: close header indicates that no more transactions will
proceed, and the connection closes after the current one. An HTTP 1.1
client or server that doesn't support persistent connections should always
use the Connection: close header.
HTTP 1.0, on the other hand, does not have persistent connections by
default. If a 1.0 client wishes to use persistent connections, it uses the
keep-alive parameter. A Connection: keep-alive header is
issued by both HTTP 1.0 clients and servers for each transaction under
persistent connections. The last transaction does not have a
Connection: keep-alive header, and behaves like a
Connection: close header under HTTP 1.1. HTTP 1.0 servers that
do not support persistent connections will not have a Connection:
keep-alive header in their response, and the client should disconnect
after the first transaction completes.
Use of the keep-alive parameter is known to cause problems with
proxy servers that do not understand persistent connections for HTTP
1.0. If a proxy server blindly forwards the Connection: keep-alive
header, the origin-server and initial client are using persistent
connections while the proxy server is not. The origin server maintains the
network connection when the proxy server expects a disconnect; timing
problems follow.
To get around that, when HTTP 1.1 proxies encounter an HTTP 1.0
request, it must remove the Connection header and any headers
specified by the Connection header before forwarding the message.