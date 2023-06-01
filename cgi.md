# CGI README (RFC)

## I-intro and conventions

-allows webserver and cgi script to share resonsability of responding to client requests.
-CGI defines the abstract parameters, known as meta-variables,which describe a client's request.
-CGI script handles the application issues, such as data access and document processing.

-From RFC: Terminology: Meta-variable, script, server.

## II-Invoking the script:(from RFC)

### 1-server responsability:
-get request from client => select CGI to handle => convert client req to CGI req => execute script and convert CGI resp to client resp 

### 2- script selection:
-server determines which CGI is script to be executed based on a generic-form URI supplied by the client

### 3-script-URI

### 4-execution:
-set envirenment vars and create new process for executing the script

### example of cgi URL:

=> http://example.com/cgi-bin/script.cgi
=> file:///home/user/scripts/script.cgi

cookie:

-generate a token for each session
-store data in DB
-compare data to serve client



