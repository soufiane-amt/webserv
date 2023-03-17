/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:49:34 by samajat           #+#    #+#             */
/*   Updated: 2023/03/17 19:58:18 by samajat          ###   ########.fr       */
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

bool     errorManager::isURIValid(std::string uri)
{
    if (uri[0] == '/')
        return true;
    return false;
}

bool     errorManager::isRestOfRequestValid(request_t request)
{
    if (request["Host"].empty())
        return false;
    
    return true;
}

