/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:49:34 by samajat           #+#    #+#             */
/*   Updated: 2023/06/20 18:01:55 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorManager.hpp"
#include <string>

// Config parser;

const std::string errorManager::_validProtocol = "HTTP/1.1";
const std::string errorManager::_Methods[8] = {"GET", "POST", "DELETE", "OPTIONS","HEAD","PUT","TRACE","CONNECT"};



void     errorManager::request_has_valid_headers(header_t& header, bool requestHasBody)
{
    std::string Method = header["Method"];

    if ((Method == "GET" || Method == "DELETE") && (requestHasBody || _request_has_meta_data(header)))
        throw StatusCode(BAD_REQUEST);
    if (Method == "POST" && !_request_has_meta_data(header))
        throw StatusCode(BAD_REQUEST);
    if (__request_transfer_encoded(header) && !(_request_is_chunked(header)))
        throw StatusCode(BAD_REQUEST);
    if (!_request_is_chunked(header) && Method == "POST" && !requestHasBody)
        throw StatusCode(BAD_REQUEST);
    if (Method == "POST" && (!__request_has_content_length(header) || !__request_has_content_type(header) ))
        throw StatusCode(BAD_REQUEST);
    if (Method == "POST" && __request_has_content_length(header) && _request_is_chunked(header) )
        throw StatusCode(BAD_REQUEST);
}


void     errorManager::isMethodValid(Method_t Method, directive_t& location_dirts)
{
    std::string allow_value = utility::search_directive ("allow", location_dirts);
    if (allow_value == "")
        return ;
    std::vector <std::string> allowedMethods = utility::split(allow_value, " ");
    for (size_t i = 0; i < allowedMethods.size(); i++)
        if (Method == allowedMethods[i])//valid method must be in the list of valid methods in the config file
            return ;
    
    for (size_t i = 0; i < _Methods->size(); i++)
        if (Method == _Methods[i])
            throw StatusCode(METHOD_NOT_ALLOWED) ;
    throw StatusCode(BAD_REQUEST);
}



void     errorManager::isProtocolValid(protocol_t protocol)
{
    // std::cout << "protocol:" << protocol << std::endl;
    if (protocol == _validProtocol)
        return ;
    if (protocol.substr( 0, 5) == "HTTP/" && (protocol[5] != '0' && protocol[5] != '\0') )
        throw StatusCode(HTTP_VERSION_NOT_SUPPORTED);
    throw StatusCode(BAD_REQUEST);
}



void     errorManager::isLocationRedirected(const std::string& targetLocat,location_t& server_location)
{
    location_t::iterator it = server_location.find(targetLocat);
    if (it != server_location.end())
    {
        std::string red = utility::search_directive ("return", server_location[targetLocat]);
        if (red != "")
        {
            StatusCode redirection = utility::redirector_proccessor(red);
            throw redirection;
        }
    }
}

std::string errorManager::isURIValid(const std::string& URI, location_t server_location) {
    
    std::cout << URI[0] <<"--------\n";
    if (URI[0] != '/')
        throw StatusCode(BAD_REQUEST);
    if (URI.size() > MAX_URI_SIZE)
        throw StatusCode(URI_TOO_LONG);
    location_t::iterator it = server_location.find(URI);

    if (it != server_location.end())
        return URI.substr(0, URI.size());
    size_t pos = URI.find_last_of('/');
    if (pos == 0)
        return "/";
    else if (pos != std::string::npos)
        return isURIValid(URI.substr(0, pos), server_location);
    throw StatusCode(NOT_FOUND);
    return "";
}



void     errorManager::defineFinalUri (header_t& header, const std::string& targetLocat, location_t server_location)
{
    isLocationRedirected(targetLocat, server_location);
    std::string root =  utility::search_directive("root", server_location[targetLocat]);
    if (targetLocat.size() == 1 && header.at("URI").size() > 1)//to fix
        root += "/";
    if (header.at("URI").substr(0, targetLocat.size()) != targetLocat && !utility::check_file_or_directory((root + header.at("URI"))) )
        throw StatusCode(NOT_FOUND);
    
    header["URI"] = root + header.at("URI").substr(targetLocat.size());
    if (!utility::check_file_or_directory(header.at("URI")) )
        throw StatusCode(NOT_FOUND);
    if (utility::check_file_or_directory(header.at("URI")) == S_DIRECTORY)
    {
        std::string it_ind = utility::search_directive("index", server_location[targetLocat]);
        std::string it_auto = utility::search_directive("autoindex", server_location[targetLocat]);
        //------->/at the begining of the URI or at the end of the index may cause a problem//this is only a temporary solution
        if (it_ind != "")
        {
            if (header.at("URI").back() != '/' && it_ind.front() != '/')
                header.at("URI") += "/";
            else if (header.at("URI").back() == '/' && it_ind.front() == '/')
                header.at("URI").pop_back();
            header.at("URI") +=  it_ind;
            if (utility::check_file_or_directory(header["URI"]) == S_DIRECTORY)
                throw StatusCode(NOT_FOUND);
        }
        else if (it_auto == "" ||  it_auto == "off")
            throw StatusCode(NOT_FOUND);
    }
}


void   errorManager::isHostValid(const header_t& header)
{
    header_t::const_iterator it = header.find("host");
    if (it ==  header.end() || it->second.empty())
        throw StatusCode(BAD_REQUEST);
    //here I check if the host has a space in its value
    for (std::string::const_iterator iter = it->second.begin(); iter != it->second.end(); iter++)
        if (isspace(*iter))
            throw StatusCode(BAD_REQUEST);
}

void    errorManager::isBodySizeValid(const std::string& body,  directive_t& header)
{
    std::string max_body_size = utility::search_directive ("max_body_size", header);
    if (max_body_size != "" && static_cast<int>(body.size()) > atoi(max_body_size.c_str()))
        throw StatusCode(REQUEST_ENTITY_TOO_LARGE);    
}

bool     errorManager::isRequestValid(http_message_t &request, int targeted_serv)
{
    location_t     server_location = parser.get_server_locations(targeted_serv);
    header_t              &header         = request.header;

    std::cout << "|" << (header.find("URI")->second)[0] << "|" << std::endl;
    request.targeted_Location = isURIValid(header.find("URI")->second, server_location);

    request_has_valid_headers(header, !request.body.empty());
    isMethodValid(header.find("Method")->second, server_location[request.targeted_Location]);
    isProtocolValid(header.find("Protocol")->second);

    isHostValid(header);
    defineFinalUri(header, request.targeted_Location, server_location);
    
    isBodySizeValid(request.body, server_location[request.targeted_Location]);
    // std::string max_body_size = utility::search_directive ("max_body_size", server_location[request.targeted_Location]);
    // if (max_body_size != "" && static_cast<int>(request.body.size()) > atoi(max_body_size.c_str()))
    //     throw StatusCode(REQUEST_ENTITY_TOO_LARGE);    

    return true;
}