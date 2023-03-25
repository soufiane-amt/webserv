/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:09:01 by samajat           #+#    #+#             */
/*   Updated: 2023/03/25 15:23:33 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exception.hpp"
#include "utils.hpp"

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

bool StatusCode::is_error_status()
{
    if (_status_code[0] == '4' || _status_code[0] == '5')
        return (true);
    return (false);
}


std::string StatusCode::get_status_code()
{
    return (_status_code);
}

std::string StatusCode::get_associated_page() const
{
    return (utility::get_file_content("../error_pages/" + _status_code.substr(3) + "_sc" + ".html"));
}

StatusCode::~StatusCode()throw()
{
    
}
