/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:49:34 by samajat           #+#    #+#             */
/*   Updated: 2023/03/19 11:09:39 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorManager.hpp"


const std::string errorManager::_validMethods[3] = {"GET", "POST", "DELETE"};
const std::string errorManager::_validProtocol = "HTTP/1.1";


bool     errorManager::isMethodValid(method_t method)
{
    for (int i = 0; i < 3; i++)
        if (method == _validMethods[i])
            return true;
    return false;
}

bool     errorManager::isProtocolValid(protocol_t protocol)
{
    if (protocol == _validProtocol)
        return true;
    return false;
}

//This function is used to check if the request is valid or not and r
//eturns the uri if it is valid if not returns an empty string


std::string errorManager::isURIValid(const std::string& uri) {
    static simpleConfPars parser;
    static location_t server_location = parser.get_server_location(0);

    std::cout << "URI: " << uri << std::endl;
    location_t::iterator it = server_location.find(uri);
    if (it != server_location.end())
        return (uri);
    size_t pos = uri.find_last_of('/');
    if (uri[0] == '/')
        return isURIValid(uri.substr(1));
    else if (pos != std::string::npos)
        return isURIValid(uri.substr(0, pos));
    return ("");
}

// bool     errorManager::isRestOfRequestValid(request_t request)
// {
//     if (request["Host"].empty())
//         return false;
    
//     return true;
// }

bool     errorManager::isRequestValid(request_t request)
{
    if (!isMethodValid(request["Method"]))
        return false;
    if (!isProtocolValid(request["Protocol"]))
        return false;
    if (isURIValid(request["URI"]).empty())
        return false;
    // if (!isRestOfRequestValid(request))
    //     return false;
    return true;
}