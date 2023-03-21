/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:49:34 by samajat           #+#    #+#             */
/*   Updated: 2023/03/21 15:28:24 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorManager.hpp"
#include <string>

const std::string errorManager::_validMethods[3] = {"GET", "POST", "DELETE"};
const std::string errorManager::_validProtocol = "HTTP/1.1";
const std::string errorManager::_notAllowedMethods[5] = {"OPTIONS","HEAD","PUT","TRACE","CONNECT"};


void     errorManager::isMethodValid(Method_t Method, bool requestHasBody)
{
    if (requestHasBody && (Method == "GET" || Method == "DELETE"))
        throw ParsingErrorDetected(BAD_REQUEST);
    for (size_t i = 0; i < _validMethods->size(); i++)
        if (Method == _validMethods[i])//valid method must be in the list of valid methods in the config file
            return ;
    
    for (size_t i = 0; i < _notAllowedMethods->size(); i++)
        if (Method == _notAllowedMethods[i])
            throw ParsingErrorDetected(METHOD_NOT_ALLOWED) ;
    throw ParsingErrorDetected(BAD_REQUEST);
}

void     errorManager::isProtocolValid(protocol_t protocol)
{
    if (protocol == _validProtocol)
        return ;
    if (protocol.substr( 0, 5) == "HTTP/" && (protocol[5] != '0' && protocol[5] != '\0') )
        throw ParsingErrorDetected(HTTP_VERSION_NOT_SUPPORTED);
    throw ParsingErrorDetected(BAD_REQUEST);

}

//This function is used to check if the request is valid or not and r
//eturns the URI if it is valid if not returns an empty string


// std::string errorManager::isURIValid(const std::string& URI) {
//     static simpleConfPars parser;
//     static location_t server_location = parser.get_server_location(0);

//     location_t::iterator it = server_location.find(URI);
//     if (it != server_location.end())
//         return (URI);
//     size_t pos = URI.find_last_of('/');
//     if (URI[0] == '/')
//         return isURIValid(URI.substr(1));
//     else if (pos != std::string::npos)
//         return isURIValid(URI.substr(0, pos));
//     return ("");
// }



bool errorManager::isURIValid(const std::string& URI,location_t server_location, std::string &targetPath) {
    
    if (URI[0] != '/')
        throw ParsingErrorDetected(BAD_REQUEST);
    location_t::iterator it = server_location.find(URI);

    if (it != server_location.end())
    {
        targetPath = URI;
        return true;
    }
    //for http://
    // if (URI.substr(0, 7) == "http://")
    //     isURIValid(URI.substr(7), server_location, targetPath);
    size_t pos = URI.find_last_of('/');
    if (URI.length() == 1 && URI[0] == '/')
        isURIValid(URI.substr(1), server_location, targetPath);
    else if (pos != std::string::npos)
        return isURIValid(URI.substr(0, pos), server_location, targetPath);
    throw ParsingErrorDetected(NOT_FOUND);
    return false;
}

bool     errorManager::isRequestValid(const http_message_t &request, std::string &targetPath)
{
    static simpleConfPars parser;
    static location_t server_location = parser.get_server_location(0);
    const header_t &header = request.first;

    isMethodValid(header.find("Method")->second, !request.second.empty());
    isProtocolValid(header.find("Protocol")->second);
    isURIValid(header.find("URI")->second, server_location, targetPath);
    header_t::const_iterator it = header.find("host");
    
    if (it ==  header.end() || it->second.empty())
        throw ParsingErrorDetected(BAD_REQUEST);
    
    for (std::string::const_iterator iter = it->second.begin(); iter != it->second.end(); iter++)
        if (isspace(*iter))
            throw ParsingErrorDetected(BAD_REQUEST);
    //if the header doesn't end with a CRLF to seperate the body from the header
    // if (request.find("") == request.end())
    //     throw ParsingErrorDetected(BAD_REQUEST);
    return true;
}