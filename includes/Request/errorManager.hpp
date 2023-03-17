/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:49:48 by samajat           #+#    #+#             */
/*   Updated: 2023/03/17 19:36:37 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORMANAGER_HPP
# define ERRORMANAGER_HPP

#include "utils.hpp"

class errorManager
{
    private:
    typedef   std::string    method_t;
    typedef   std::string    protocol_t;
    
    static const std::string    _validMethods[3];
    static const std::string    _validProtocol;

    public:
    static bool     isRequestValid(request_t request);
    

    
    private:
    bool     isMethodValid(method_t method);
    bool     isProtocolValid(protocol_t protocol);
    bool     isURIValid(std::string uri);
    bool     isRestOfRequestValid(request_t request);
};

#endif