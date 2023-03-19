/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:52 by samajat           #+#    #+#             */
/*   Updated: 2023/03/19 14:30:07 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_HPP
# define UTILS_HPP



#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <exception>



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


/* ************************************************************************** */
                            // Special Macros :
/* ************************************************************************** */

#define CRLF "\r\n"
#define SP " "



/* ************************************************************************** */
                            // Typedefs :
/* ************************************************************************** */

typedef std::map<std::string, std::string>                          directive_t;
typedef std::map<std::string, directive_t>                          location_t;
typedef std::vector< std::pair<directive_t, location_t> > server_t;


//Http Request typedefs : 
typedef    std::map <std::string, std::string>  request_t;







//For tests :
struct simpleConfPars
{
    simpleConfPars ()
    {

        directive_t directives;
        location_t locations;
        
        directives["listen"] = "80";
        directives["server_name"] = "example.com";
        locations["/"]["root"] = "/var/www/html";
        locations["/"]["Methods"] = "GET HEAD";
        locations["/"]["index"] = "index.html";
        locations["/images"]["root"] = "/var/www";
        locations["/images"]["index"] = "index.html";
        directives["error_page"] = "404 /404.html";
        locations["/404.html"]["root"] = "/var/www/html";
        server.push_back(make_pair(directives, locations));
    }

    location_t get_server_location (int server_id)
    {
        return (server[server_id].second);
    }
    
    directive_t::iterator get_server_directive (int server_id, std::string directive)
    {
        return (server[server_id].first.find(directive));
    }

    private:
    server_t server;
    
};


/* ************************************************************************** */
                            // utility :
/* ************************************************************************** */

struct utility
{
    static std::vector<std::string> split(std::string str, std::string delimiter);
};

#endif