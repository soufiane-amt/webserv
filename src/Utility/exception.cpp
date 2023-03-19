/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:09:01 by samajat           #+#    #+#             */
/*   Updated: 2023/03/19 15:31:18 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exception.hpp"


ParsingErrorDetected::ParsingErrorDetected(std::string msg) : _msg(msg)
{
}

const char* ParsingErrorDetected::what() const throw()
{
    return (_msg.c_str());
}

bool ParsingErrorDetected::operator==(const std::string& codeStatus)
{
    if (_msg == codeStatus)
        return (true);
    return (false);
}