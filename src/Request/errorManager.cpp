/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:49:34 by samajat           #+#    #+#             */
/*   Updated: 2023/03/18 14:49:58 by samajat          ###   ########.fr       */
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

std::pair<bool, std::string> errorManager::isURIValid(const std::string& uri) {
    static simpleConfPars parser;
    static location_t server_location = parser.get_server_location(0);

    location_t::iterator it = server_location.find(uri);
    if (it != server_location.end())
        return std::make_pair (true, it->second["root"]);
    size_t pos = uri.find_last_of('/');
    if (pos != std::string::npos)
        return isURIValid(uri.substr(0, pos));
    return std::make_pair (false, "");
}

bool     errorManager::isRestOfRequestValid(request_t request)
{
    if (request["Host"].empty())
        return false;
    
    return true;
}

