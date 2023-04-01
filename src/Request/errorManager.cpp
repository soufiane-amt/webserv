/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:49:34 by samajat           #+#    #+#             */
/*   Updated: 2023/04/01 15:50:17 by samajat          ###   ########.fr       */
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

int errorManager::isURIValid(const std::string& URI, location_t server_location) {
    
    if (URI[0] != '/')
        throw StatusCode(BAD_REQUEST);
    if (URI.size() > MAX_URI_SIZE)
        throw StatusCode(URI_TOO_LONG);
    location_t::iterator it = server_location.find(URI);

    if (it != server_location.end())
        return URI.size();
    size_t pos = URI.find_last_of('/');
    if (!pos )
        return 1;
    else if (pos != std::string::npos)
        return isURIValid(URI.substr(0, pos), server_location);
    throw StatusCode(NOT_FOUND);
    return -1;
}

//This function is performed when we check if the URI is valid and we need to define the final 
//directory or a file from where the file should be searched


std::string     search_root (header_t& header, int targetPathSize, location_t server_location)
{
    directive_t           location_dirts = server_location[header.at("URI").substr(0, targetPathSize)];
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

void     errorManager::defineFinalUri (header_t& header, int targetPathSize, location_t server_location)
{
    struct stat sb;
    
    //check redirections
    isLocationRedirected(header["URI"], server_location);
    
    std::string location_uri  = header.at("URI");
    std::string root =  search_root(header, targetPathSize, server_location);
    if (targetPathSize == 1 && header.at("URI").size() > 1)
        root += "/";
    header["URI"] = root + header["URI"].substr(targetPathSize);
    if (stat(header.at("URI").c_str(), &sb) == -1)
        throw StatusCode(NOT_FOUND);
    if (S_ISDIR(sb.st_mode))
    {
        location_t::iterator it_loc = server_location.find(location_uri);
        directive_t::iterator it_ind = it_loc->second.find("index");
        directive_t::iterator it_auto = it_loc->second.find("autoindex");
            //------->/at the begining of the URI or at the end of the index may cause a problem//this is only a temporary solution
        if (it_loc->second.end() != it_ind)
        { 
            header.at("URI") += "/" + it_ind->second;
            std::cout << header.at("URI") <<std::endl;
        }
        else if (it_loc->second.end() != it_auto)
            header.at("URI") += "/" + it_auto->second;
        else
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
    header_t              &header         = request.first;

    isMethodValid(header.find("Method")->second, !request.second.empty());
    isProtocolValid(header.find("Protocol")->second);
    isHostValid(header);
    int   targetPathSize = isURIValid(header.find("URI")->second, server_location);
    defineFinalUri(header, targetPathSize, server_location);
    

    //THis the max+body+size shit of which I'll take care later
    // std::pair <bool, directive_t::iterator> it2 = parser.get_directive(0, header["URI"], "max_body_size");
    // std::cout << "header[\"URI\"] "  << it2.first <<  header["URI"] << (static_cast<int>(request.second.size()) > atoi((it2.second->second).c_str())) << std::endl;
    // if (it2.first && static_cast<int>(request.second.size()) > atoi((it2.second->second).c_str()))
    //     throw StatusCode(REQUEST_ENTITY_TOO_LARGE);
    


    return true;
}