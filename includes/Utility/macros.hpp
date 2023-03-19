/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:04:50 by samajat           #+#    #+#             */
/*   Updated: 2023/03/19 15:08:25 by samajat          ###   ########.fr       */
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


# define MAX_REQUEST_SIZE 1000000
# define MAX_HEADER_SIZE 1000000
# define MAX_BODY_SIZE 1000000
# define MAX_URI_SIZE 1000000
# define MAX_METHOD_SIZE 1000000
# define MAX_PROTOCOL_SIZE 1000000
# define MAX_KEY_SIZE 1000000
# define MAX_VALUE_SIZE 1000000
# define MAX_STATUS_CODE_SIZE 1000000
# define MAX_STATUS_MESSAGE_SIZE 1000000
# define MAX_VERSION_SIZE 1000000


/* ************************************************************************** */
                            // Status codes :
/* ************************************************************************** */


#define OK 200
#define CREATED 201
#define ACCEPTED 202
#define NO_CONTENT 204
#define PARTIAL_CONTENT 206

#define MULTIPLE_CHOICES 300
#define MOVED_PERMANENTLY 301
#define FOUND 302
#define SEE_OTHER 303
#define NOT_MODIFIED 304
#define TEMPORARY_REDIRECT 307

#define BAD_REQUEST 400
#define UNAUTHORIZED 401
#define FORBIDDEN 403
#define NOT_FOUND 404
#define METHOD_NOT_ALLOWED 405
#define REQUEST_TIMEOUT 408

#define INTERNAL_SERVER_ERROR 500
#define NOT_IMPLEMENTED 501
#define BAD_GATEWAY 502
#define SERVICE_UNAVAILABLE 503
#define GATEWAY_TIMEOUT 504
#define HTTP_VERSION_NOT_SUPPORTED 505





#endif