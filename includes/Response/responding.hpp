/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responding.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:21:12 by samajat           #+#    #+#             */
/*   Updated: 2023/03/23 11:46:31 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONDING_HPP
#define RESPONDING_HPP

#include "utils.hpp"
#include "exception.hpp"



//Status-Line

class responsePreparation
{
    private:
        typedef std::string     ultimateResponse_t;
        typedef std::string     statusCode_t;
    
        ultimateResponse_t      _response;
        statusCode_t            _statusCode;

    public:
        responsePreparation(const  StatusCode& e = StatusCode(OK));
};

#endif