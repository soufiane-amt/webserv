/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:09:01 by samajat           #+#    #+#             */
/*   Updated: 2023/04/09 16:28:21 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exception.hpp"
#include "utils.hpp"
#include <fstream>

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






StatusCode::StatusCode(std::string msg) : _status_code(msg), _redir_location("")
{
}

StatusCode::StatusCode(std::string msg, std::string redir_location) : _status_code(msg), _redir_location(redir_location)
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

bool StatusCode::is_error_status() const
{
    if (_status_code[0] == '4' || _status_code[0] == '5')
        return (true);
    return (false);
}


std::string StatusCode::get_status_code() const
{
    return (_status_code);
}

std::string StatusCode::get_associated_page() const
{
    std::vector<char> _err = utility::get_file_content(URI_ERROR + _status_code.substr(0,3) + "_sc" + ".html");
    return (std::string(_err.begin(), _err.end()));
}

std::string StatusCode::get_redir_location() const
{
    return (_redir_location);
}

StatusCode::~StatusCode()throw()
{
    
}
