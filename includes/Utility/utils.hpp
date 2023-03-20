/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:52 by samajat           #+#    #+#             */
/*   Updated: 2023/03/20 17:36:01 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_HPP
# define UTILS_HPP


#include <iostream>

#include <vector>
#include <map>
#include <set>
#include <string>
#include <iterator>
#include <algorithm>

#include <exception>
#include <cctype>
#include "macros.hpp"


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
                            // utility::Methods :
/* ************************************************************************** */

struct utility
{
    static std::vector<std::string> split(std::string str, std::string delimiter);
    static std::string              trim(const std::string &str, const std::string &delimiter);

    private:
    //trim methods :
    static std::string              left_trim(const std::string &str, const std::string &delimiter);
    static std::string              right_trim(const std::string &str, const std::string &delimiter);
    
};


#endif