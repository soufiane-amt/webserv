/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:52 by samajat           #+#    #+#             */
/*   Updated: 2023/04/09 14:52:04 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_HPP
# define UTILS_HPP


#include <iostream>

#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

#include <exception>
#include <cctype>
#include <ctime>
#include "macros.hpp"
#include "exception.hpp"
#include <sys/stat.h>
#include <dirent.h>

/* ************************************************************************** */
                            // Typedefs :
/* ************************************************************************** */

typedef std::map<std::string, std::string>                          directive_t;
typedef std::map<std::string, directive_t>                          location_t;
typedef std::vector< std::pair<directive_t, location_t> > server_t;


//Http Request typedefs : 
typedef    std::map <std::string, std::string>  header_t;
typedef    std::string                          body_t;



struct http_message_t
{
    header_t        header;
    body_t          body;
    std::string     targeted_Location;
};




//For tests :
struct simpleConfPars
{
    simpleConfPars ()
    {

    directive_t directives;
    location_t locations;//autoindex on
    
    directives["listen"] = "80";
    directives["server_name"] = "example.com";
    // directives["max_body_size"] = "-1";
    
    // directives["return"] = "302 https://www.youtube.com/";
    // directives["root"] = "./www";
    directives["root"] = "index.html";
    // directives["allow"] = "POST";
    
    // locations["/"]["index"] = "index.html";
    // locations["/"]["index"] = "index.html";
    // locations["/"]["max_body_size"] = "-1";

    locations["/"]["root"] = "./www";
        // locations["/"]["index"] = "index.html";
    // locations["/"]["allow"] = "POST";
    locations["/"]["autoindex"] = "on";
    // locations["/"]["return"] = "302 https://www.youtube.com/";

    locations["/random"]["root"] = "./www/random/";
    // locations["/random"]["index"] = "page.html";
    locations["/random"]["autoindex"] = "on";
    
    locations["/youtube"]["return"] = "302 https://www.youtube.com/";
    // locations["/images"]["autoindex"] = "on";

    
    locations["/upl"]["root"] = "./www/upload";
    locations["/upl"]["upload"] = "upload_store";
    
    // directives["error_page"] = "404 /404.html";
    // locations["/404.html"]["root"] = "./www/error_pages";
    server.push_back(make_pair(directives, locations));
    }

    location_t get_server_locations (int server_id)
    {
        return (server[server_id].second);
    }
    
    std::string get_server_directives (int server_id, std::string directive)
    {
        return (server[server_id].first.at(directive));
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

extern simpleConfPars parser;



/* ************************************************************************** */
                            // utility::Methods :
/* ************************************************************************** */

struct utility
{
    static std::vector<std::string>             split(std::string str, std::string delimiter);

    static std::string                          trim(const std::string &str, const std::string &delimiter);

    static std::string::iterator                caseInsensitiveSearch(std::string & str1, const std::string & str2);

    static std::string                          get_date();

    static std::vector<char>                          get_file_content(const std::string& uri);
    
    static StatusCode                           redirector_proccessor(const std::string& redirector);

    static std::string                          list_directory(const std::string& directory);

    static int                                  check_file_or_directory(const std::string& path);
    private:
    //trim methods :
    static std::string              left_trim(const std::string &str, const std::string &delimiter);
    static std::string              right_trim(const std::string &str, const std::string &delimiter);
    
    //case insensitive search :
    static bool                     caseInsensitiveStringCompare(char a, char b);

};




#endif