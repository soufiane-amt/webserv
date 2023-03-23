/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:09:01 by samajat           #+#    #+#             */
/*   Updated: 2023/03/23 11:46:02 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exception.hpp"


ParsingErrorDetected::ParsingErrorDetected(std::string msg) : _codeStatus(msg)
{
}

const char* ParsingErrorDetected::what() const throw()
{
    return (_codeStatus.c_str());
}

bool ParsingErrorDetected::operator==(const std::string& codeStatus)
{
    if (_codeStatus == codeStatus)
        return (true);
    return (false);
}

ParsingErrorDetected::~ParsingErrorDetected()throw()
{
    
}






StatusCode::StatusCode(std::string msg) : _status_code(msg)
{
}

const char* StatusCode::what() const throw()
{
    return (_status_code.c_str());
}

bool StatusCode::operator==(const std::string& status_code)
{
    if (_status_code == status_code)
        return (true);
    return (false);
}

StatusCode::~StatusCode()throw()
{
    
}
