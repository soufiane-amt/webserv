/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:49:34 by samajat           #+#    #+#             */
/*   Updated: 2023/04/05 16:43:37 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorManager.hpp"
#include <string>

simpleConfPars parser;

const std::string errorManager::_validMethods[3] = {"GET", "POST", "DELETE"};
const std::string errorManager::_validProtocol = "HTTP/1.1";
const std::string errorManager::_notAllowedMethods[5] = {"OPTIONS","HEAD","PUT","TRACE","CONNECT"};


void     errorManager::isMethodValid(Method_t Method, bool requestHasBody)
{
    if ((!requestHasBody && Method == "POST") || 
           (requestHasBody && (Method == "GET" || Method == "DELETE")))//Check if method is valid for the request body
        throw StatusCode(BAD_REQUEST);

    for (size_t i = 0; i < _validMethods->size(); i++)
        if (Method == _validMethods[i])//valid method must be in the list of valid methods in the config file
            return ;
    
    for (size_t i = 0; i < _notAllowedMethods->size(); i++)
        if (Method == _notAllowedMethods[i])
            throw StatusCode(METHOD_NOT_ALLOWED) ;
    throw StatusCode(BAD_REQUEST);
}



void     errorManager::isProtocolValid(protocol_t protocol)
{
    if (protocol == _validProtocol)
        return ;
    if (protocol.substr( 0, 5) == "HTTP/" && (protocol[5] != '0' && protocol[5] != '\0') )
        throw StatusCode(HTTP_VERSION_NOT_SUPPORTED);
    throw StatusCode(BAD_REQUEST);
}


void     errorManager::isLocationRedirected(const std::string& URI,location_t server_location)
{
    location_t::iterator it = server_location.find(URI);
    if (it != server_location.end())
    {
        directive_t::iterator it_red = it->second.find("return");
        if (it_red != it->second.end())
        {
            StatusCode redirection = utility::redirector_proccessor(it_red->second);
            throw redirection;
        }
    }
}

std::string errorManager::isURIValid(const std::string& URI, location_t server_location) {
    
    if (URI[0] != '/')
        throw StatusCode(BAD_REQUEST);
    if (URI.size() > MAX_URI_SIZE)
        throw StatusCode(URI_TOO_LONG);
    location_t::iterator it = server_location.find(URI);

    if (it != server_location.end())
        return URI.substr(0, URI.size());
    size_t pos = URI.find_last_of('/');
    if (!pos )
        return "/";
    else if (pos != std::string::npos)
        return isURIValid(URI.substr(0, pos), server_location);
    throw StatusCode(NOT_FOUND);
    return "";
}

//This function is performed when we check if the URI is valid and we need to define the final 
//directory or a file from where the file should be searched


std::string     search_root (const std::string &targetLocat, location_t server_location)
{
    directive_t           location_dirts = server_location[targetLocat];
    directive_t::iterator root_it ;
    std::string           root = "";
    
    root_it =  location_dirts.find("root");
    if (root_it == location_dirts.end())
    {
        directive_t::iterator serv_it = parser.get_server_directives(0, "root");
        if (serv_it == location_dirts.end())
            throw StatusCode(NOT_FOUND);
        root = serv_it->second;
    }
    else
        root = root_it->second;
    return (root);
}


// bool is_tageted_uri_defined_location(const std::string& targetLocat, location_t server_location)
// {
//     location_t::iterator it = server_location.find(targetLocat);
//     if (it != server_location.end())
//         return true;
//     return false;
// }

void     errorManager::defineFinalUri (header_t& header, const std::string& targetLocat, location_t server_location)
{
    struct stat sb;
    

    //check redirections
    isLocationRedirected(targetLocat, server_location);
    std::string root =  search_root(targetLocat, server_location);
    if (targetLocat.size() == 1 && header.at("URI").size() > 1)//to fix
        root += "/";
    // if (header.at("URI").back() == '/')
    //     header["URI"];
    if (header.at("URI").substr(0, targetLocat.size()) != targetLocat && !utility::directory_file_exist((root + header.at("URI"))) )
        throw StatusCode(NOT_FOUND);
    header["URI"] = root + header.at("URI").substr(targetLocat.size());
    if (!utility::directory_file_exist(header.at("URI")) )
        throw StatusCode(NOT_FOUND);
    if (stat(header.at("URI").c_str(), &sb) != -1 && S_ISDIR(sb.st_mode))
    {
        location_t::iterator it_loc = server_location.find(targetLocat);
        directive_t::iterator it_ind = it_loc->second.find("index");
        directive_t::iterator it_auto = it_loc->second.find("autoindex");
        //------->/at the begining of the URI or at the end of the index may cause a problem//this is only a temporary solution
        if (it_loc->second.end() != it_ind)
        { 
            std::cout << "before" << header.at("URI")   << std::endl;
            if (header.at("URI").back() != '/' && it_ind->second.front() != '/')
                header.at("URI") += "/";
            else if (header.at("URI").back() == '/' && it_ind->second.front() == '/')
                header.at("URI").pop_back();
            header.at("URI") +=  it_ind->second;
            std::cout << "after" << header.at("URI")   << std::endl;
            if (stat(header.at("URI").c_str(), &sb) == -1 ||  S_ISDIR(sb.st_mode))
                throw StatusCode(NOT_FOUND);
        }
        else if (it_loc->second.end() == it_auto || (it_loc->second.end() != it_auto && it_auto->second == "off"))
            throw StatusCode(NOT_FOUND);
    }
}


void   errorManager::isHostValid(const header_t& header)
{
    header_t::const_iterator it = header.find("host");
    if (it ==  header.end() || it->second.empty())
        throw StatusCode(BAD_REQUEST);
    for (std::string::const_iterator iter = it->second.begin(); iter != it->second.end(); iter++)
        if (isspace(*iter))
            throw StatusCode(BAD_REQUEST);
}

bool     errorManager::isRequestValid(http_message_t &request)
{
    location_t     server_location = parser.get_server_locations(0);
    header_t              &header         = request.header;

    isMethodValid(header.find("Method")->second, !request.body.empty());
    isProtocolValid(header.find("Protocol")->second);
    isHostValid(header);
    std::string   targetLocation = isURIValid(header.find("URI")->second, server_location);
    std::cout << "targetLocation " << targetLocation << std::endl;
    request.targeted_Location = targetLocation;
    defineFinalUri(header, targetLocation, server_location);
    

    //THis the max+body+size shit of which I'll take care later
    // std::pair <bool, directive_t::iterator> it2 = parser.get_directive(0, header["URI"], "max_body_size");
    // std::cout << "header[\"URI\"] "  << it2.first <<  header["URI"] << (static_cast<int>(request.body.size()) > atoi((it2.second->second).c_str())) << std::endl;
    // if (it2.first && static_cast<int>(request.body.size()) > atoi((it2.second->second).c_str()))
    //     throw StatusCode(REQUEST_ENTITY_TOO_LARGE);
    


    return true;
}