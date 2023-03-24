/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:04:50 by samajat           #+#    #+#             */
/*   Updated: 2023/03/24 17:01:40 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_HPP
# define MACROS_HPP



/* ************************************************************************** */
                            // Special Macros :
/* ************************************************************************** */

#define CRLF "\r\n"
#define SP " "



/* ************************************************************************** */
                            // MAXIMUM SIZE OF EACH FIELD :
/* ************************************************************************** */


# define MAX_URI_SIZE 2048


/* ************************************************************************** */
                            // Status codes :
/* ************************************************************************** */

#define OK "200 OK"
#define CREATED "201 Created"
#define ACCEPTED "202 Accepted"
#define NO_CONTENT "204 No Content"
#define PARTIAL_CONTENT "206 Partial Content"

#define MULTIPLE_CHOICES "300 Multiple Choices"
#define MOVED_PERMANENTLY "301 Moved Permanently"
#define FOUND "302 Found"
#define SEE_OTHER "303 See Other"
#define NOT_MODIFIED "304 Not Modified"
#define TEMPORARY_REDIRECT "307 Temporary Redirect"

#define BAD_REQUEST "400 Bad Request"
#define UNAUTHORIZED "401 Unauthorized"
#define FORBIDDEN "403 Forbidden"
#define NOT_FOUND "404 Not Found"
#define METHOD_NOT_ALLOWED "405 Method Not Allowed"
#define REQUEST_TIMEOUT "408 Request Timeout"
#define REQUEST_ENTITY_TOO_LARGE "413 Request Entity Too Large"
#define URI_TOO_LONG "414 Request-URI Too Long"
#define INTERNAL_SERVER_ERROR "500 Internal Server Error"
#define NOT_IMPLEMENTED "501 Not Implemented"
#define BAD_GATEWAY "502 Bad Gateway"
#define SERVICE_UNAVAILABLE "503 Service Unavailable"
#define GATEWAY_TIMEOUT "504 Gateway Timeout"
#define HTTP_VERSION_NOT_SUPPORTED "505 HTTP Version Not Supported"

// #define OK 200
// #define CREATED 201
// #define ACCEPTED 202
// #define NO_CONTENT 204
// #define PARTIAL_CONTENT 206

// #define MULTIPLE_CHOICES 300
// #define MOVED_PERMANENTLY 301
// #define FOUND 302
// #define SEE_OTHER 303
// #define NOT_MODIFIED 304
// #define TEMPORARY_REDIRECT 307

// #define BAD_REQUEST 400
// #define UNAUTHORIZED 401
// #define FORBIDDEN 403
// #define NOT_FOUND 404
// #define METHOD_NOT_ALLOWED 405
// #define REQUEST_TIMEOUT 408

// #define INTERNAL_SERVER_ERROR 500
// #define NOT_IMPLEMENTED 501
// #define BAD_GATEWAY 502
// #define SERVICE_UNAVAILABLE 503
// #define GATEWAY_TIMEOUT 504
// #define HTTP_VERSION_NOT_SUPPORTED 505





#endif