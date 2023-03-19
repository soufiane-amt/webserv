/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:49:34 by samajat           #+#    #+#             */
/*   Updated: 2023/03/19 15:02:47 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorManager.hpp"

const std::string errorManager::_validMethods[3] = {"GET", "POST", "DELETE"};
const std::string errorManager::_validProtocol = "HTTP/1.1";


bool     errorManager::isMethodValid(Method_t Method)
{
    std::cout << "Method: " << Method << std::endl;
    for (int i = 0; i < 3; i++)
        if (Method == _validMethods[i])
            return true;
    return false;
}

bool     errorManager::isProtocolValid(protocol_t protocol)
{
    if (protocol == _validProtocol)
        return true;
    if (protocol.substr( 0, 4) == "HTTP")
        return true;
    return false;
}

//This function is used to check if the request is valid or not and r
//eturns the URI if it is valid if not returns an empty string


std::string errorManager::isURIValid(const std::string& URI) {
    static simpleConfPars parser;
    static location_t server_location = parser.get_server_location(0);

    location_t::iterator it = server_location.find(URI);
    if (it != server_location.end())
        return (URI);
    size_t pos = URI.find_last_of('/');
    if (URI[0] == '/')
        return isURIValid(URI.substr(1));
    else if (pos != std::string::npos)
        return isURIValid(URI.substr(0, pos));
    return ("");
}

// bool     errorManager::isRestOfRequestValid(request_t request)
// {
//     if (request["Host"].empty())
//         return false;
    
//     return true;
// }

bool     errorManager::isRequestValid(const request_t &request)
{
    if (!isMethodValid(request.at("Method")))
        return false;
    if (!isProtocolValid(request.at("Protocol")))
        return false;
    if (isURIValid(request.at("URI")).empty())
        return false;
    // if (!isRestOfRequestValid(request))
    //     return false;
    return true;
}