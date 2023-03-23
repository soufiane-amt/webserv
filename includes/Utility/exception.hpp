/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:09:03 by samajat           #+#    #+#             */
/*   Updated: 2023/03/23 11:44:59 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

# include <exception>
# include <iostream>
# include <string>


class ParsingErrorDetected : public std::exception
{
    private:
        std::string _codeStatus;
    public:
        ParsingErrorDetected(std::string msg);
        virtual const char* what() const throw();
        bool operator==(const std::string& rhs);
        virtual ~ParsingErrorDetected()throw();
};

class StatusCode : public std::exception
{
    private:
        std::string _status_code;
    public:
        StatusCode(std::string msg);
        virtual const char* what() const throw();
        bool operator==(const std::string& rhs);
        virtual ~StatusCode()throw();
};


#endif