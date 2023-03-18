/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:52 by samajat           #+#    #+#             */
/*   Updated: 2023/03/18 14:30:41 by samajat          ###   ########.fr       */
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
        locations["/"]["methods"] = "GET HEAD";
        locations["/"]["index"] = "index.html";
        locations["/images/"]["root"] = "/var/www";
        locations["/images/"]["index"] = "index.html";
        directives["error_page"] = "404 /404.html";
        locations["/404.html"]["root"] = "/var/www/html";
        server[0] = std::make_pair(directives, locations);
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