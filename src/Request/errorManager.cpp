/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:49:34 by samajat           #+#    #+#             */
/*   Updated: 2023/03/19 20:09:38 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorManager.hpp"
#include <string>

const std::string errorManager::_validMethods[3] = {"GET", "POST", "DELETE"};
const std::string errorManager::_validProtocol = "HTTP/1.1";
const std::string errorManager::_notAllowedMethods[5] = {"OPTIONS","HEAD","PUT","TRACE","CONNECT"};


void     errorManager::isMethodValid(Method_t Method)
{
    for (int i = 0; i < 3; i++)
        if (Method == _validMethods[i])
            return ;
    for (int i = 0; i < 5; i++)
        if (Method == _notAllowedMethods[i])
            throw ParsingErrorDetected(METHOD_NOT_ALLOWED) ;
    throw ParsingErrorDetected(BAD_REQUEST);
}

void     errorManager::isProtocolValid(protocol_t protocol)
{
    if (protocol == _validProtocol)
        return ;
    if (protocol.substr( 0, 4) == "HTTP")
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



void errorManager::isURIValid(const std::string& URI,location_t server_location) {
    
    if (URI[0] != '/')
        throw ParsingErrorDetected(BAD_REQUEST);
    location_t::iterator it = server_location.find(URI);

    if (it != server_location.end())
        return;
    if (URI.substr(0, 7) == "http://")
        isURIValid(URI.substr(7), server_location);
    size_t pos = URI.find_last_of('/');
    if (URI.length() == 1 && URI[0] == '/')
        isURIValid(URI.substr(1), server_location);
    else if (pos != std::string::npos)
        isURIValid(URI.substr(0, pos), server_location);
    throw ParsingErrorDetected(NOT_FOUND);
}

// bool     errorManager::isRestOfRequestValid(request_t request)
// {
//     if (request["Host"].empty())
//         return false;
    
//     return true;
// }

bool     errorManager::isRequestValid(request_t &request)
{
    static simpleConfPars parser;
    static location_t server_location = parser.get_server_location(0);

    isMethodValid(request.at("Method"));
    isProtocolValid(request.at("Protocol"));
    isURIValid(request.at("URI"), server_location);
    
    // if (!isRestOfRequestValid(request))
    //     return false;
    return true;
}