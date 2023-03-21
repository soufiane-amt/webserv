/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:49:48 by samajat           #+#    #+#             */
/*   Updated: 2023/03/21 15:27:36 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORMANAGER_HPP
# define ERRORMANAGER_HPP

#include "utils.hpp"
#include "exception.hpp"

//All the functions in this class are static as We don't need to create an object of this class

class errorManager
{
    private:
    typedef   std::string    Method_t;
    typedef   std::string    protocol_t;
    
    static const std::string              _notAllowedMethods[5];//I could have used a set but it is hard to initialize a static set in c++98 witout using function
    static const std::string              _validMethods[3];
    static const std::string              _validProtocol;
    public:
    static bool  isRequestValid(const http_message_t& request, std::string &targetPath);
    

    
    private:
    static  void        isMethodValid(Method_t Method, bool requestHasBody);
    static  void        isProtocolValid(protocol_t protocol);
    static  bool        isURIValid(const std::string& URI,location_t server_location, std::string &targetPath);
};


#endif