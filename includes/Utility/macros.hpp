/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:04:50 by samajat           #+#    #+#             */
/*   Updated: 2023/05/26 13:26:28 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_HPP
# define MACROS_HPP



/* ************************************************************************** */
                            // Special Macros :
/* ************************************************************************** */

#define CRLF "\r\n"
#define SP " "

#define URI_ERROR "www/error_pages/"

#define S_DIRECTORY 100
#define S_FILE      200

/* ************************************************************************** */
                            // MAXIMUM SIZE OF EACH FIELD :
/* ************************************************************************** */


# define MAX_URI_SIZE 2048


/* ************************************************************************** */
                            // Status codes :
/* ************************************************************************** */

#define CONTINUE "100 Continue"
#define SWITCHING_PROTOCOLS "101 Switching Protocols"

#define OK "200 OK"
#define CREATED "201 Created"
#define ACCEPTED "202 Accepted"
#define NON_AUTHORITATIVE_INFORMATION "203 Non-Authoritative Information"
#define NO_CONTENT "204 No Content"
#define RESET_CONTENT "205 Reset Content"
#define PARTIAL_CONTENT "206 Partial Content"

#define MULTIPLE_CHOICES "300 Multiple Choices"
#define MOVED_PERMANENTLY "301 Moved Permanently"
#define FOUND "302 Found"
#define SEE_OTHER "303 See Other"
#define NOT_MODIFIED "304 Not Modified"
#define USE_PROXY "305 Use Proxy"
#define TEMPORARY_REDIRECT "307 Temporary Redirect"

#define BAD_REQUEST "400 Bad Request"
#define UNAUTHORIZED "401 Unauthorized"
#define PAYMENT_REQUIRED "402 Payment Required"
#define FORBIDDEN "403 Forbidden"
#define NOT_FOUND "404 Not Found"
#define METHOD_NOT_ALLOWED "405 Method Not Allowed"
#define NOT_ACCEPTABLE "406 Not Acceptable"
#define PROXY_AUTHENTICATION_REQUIRED "407 Proxy Authentication Required"
#define REQUEST_TIMEOUT "408 Request Timeout"
#define CONFLICT "409 Conflict"
#define GONE "410 Gone"
#define LENGTH_REQUIRED "411 Length Required"
#define PRECONDITION_FAILED "412 Precondition Failed"
#define REQUEST_ENTITY_TOO_LARGE "413 Request Entity Too Large"
#define URI_TOO_LONG "414 URI Too Long"
#define UNSUPPORTED_MEDIA_TYPE "415 Unsupported Media Type"
#define RANGE_NOT_SATISFIABLE "416 Range Not Satisfiable"
#define EXPECTATION_FAILED "417 Expectation Failed"

#define INTERNAL_SERVER_ERROR "500 Internal Server Error"
#define NOT_IMPLEMENTED "501 Not Implemented"
#define BAD_GATEWAY "502 Bad Gateway"
#define SERVICE_UNAVAILABLE "503 Service Unavailable"
#define GATEWAY_TIMEOUT "504 Gateway Timeout"
#define HTTP_VERSION_NOT_SUPPORTED "505 HTTP Version Not Supported"


/* ************************************************************************** */
                            // CGI FILES :
/* ************************************************************************** */


#define CGI_FILES "./www/cgi_files/cgi1.php"
#define CGI_FILES2 "./www/cgi_files/cgi2.php"

#endif