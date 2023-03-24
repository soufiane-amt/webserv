/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:52 by samajat           #+#    #+#             */
/*   Updated: 2023/03/24 22:01:12 by samajat          ###   ########.fr       */
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
#include <ctime>
#include "macros.hpp"


/* ************************************************************************** */
                            // Typedefs :
/* ************************************************************************** */

typedef std::map<std::string, std::string>                          directive_t;
typedef std::map<std::string, directive_t>                          location_t;
typedef std::vector< std::pair<directive_t, location_t> > server_t;


//Http Request typedefs : 
typedef    std::map <std::string, std::string>  header_t;
typedef    std::string                          body_t;

typedef    std::pair <header_t, body_t>         http_message_t;







//For tests :
struct simpleConfPars
{
    simpleConfPars ()
    {

    directive_t directives;
    location_t locations;
    
    directives["listen"] = "80";
    directives["server_name"] = "example.com";
    directives["max_body_size"] = "-1";
    locations["/"]["root"] = "/Users/samajat/Desktop/webserv/files";
    locations["/"]["Methods"] = "GET HEAD";
    locations["/"]["index"] = "index.html";
    locations["/images"]["root"] = "/Users/samajat/Desktop/webserv/files";
    locations["/images"]["index"] = "index.html";
    directives["error_page"] = "404 /404.html";
    locations["/404.html"]["root"] = "/Users/samajat/Desktop/webserv/files";
    server.push_back(make_pair(directives, locations));
    }

    location_t get_server_locations (int server_id)
    {
        return (server[server_id].second);
    }
    
    directive_t::iterator get_server_directives (int server_id, std::string directive)
    {
        return (server[server_id].first.find(directive));
    }

    std::pair <bool,  directive_t::iterator> get_directive (int server_id, std::string uri, std::string directive_key)
    {
        location_t::iterator it = server[server_id].second.find(uri);
        if (it != server[server_id].second.end())
        {
            directive_t::iterator it2 = it->second.find(directive_key);
            if (it2 == it->second.end())
            {
                directive_t::iterator d_itr =  server[server_id].first.find(directive_key);
                if (d_itr == server[server_id].first.end())
                    return (std::pair<bool, directive_t::iterator>(false, server[server_id].first.end()));
                else
                    return (std::pair<bool, directive_t::iterator>(true, d_itr));
            }
            else
                return (std::pair<bool, directive_t::iterator>(true, it2));
        }
        return (std::pair<bool, directive_t::iterator>(false, server[server_id].first.end()));
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
    
    static std::string::iterator    caseInsensitiveSearch(std::string & str1, const std::string & str2);

    static std::string              get_date();


    private:
    //trim methods :
    static std::string              left_trim(const std::string &str, const std::string &delimiter);
    static std::string              right_trim(const std::string &str, const std::string &delimiter);
    
    //case insensitive search :
    static bool                     caseInsensitiveStringCompare(char a, char b);

};




#endif