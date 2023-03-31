/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:49:48 by samajat           #+#    #+#             */
/*   Updated: 2023/03/31 20:59:14 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORMANAGER_HPP
# define ERRORMANAGER_HPP

#include "utils.hpp"
#include "exception.hpp"
#include <sys/stat.h>

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
    static bool  isRequestValid(http_message_t& request);
    

    
    private:
    static  void        isMethodValid(Method_t Method, bool requestHasBody);
    static  void        isProtocolValid(protocol_t protocol);
    static  int         isURIValid(const std::string& URI,location_t server_location);
    // static  int         isHostValid(const std::string& URI,location_t server_location);
    static  bool        isLocationRedirected(const std::string& URI,location_t server_location);

    static void         defineFinalUri (header_t& header, int targetPathSize, location_t server_location);
};


#endif