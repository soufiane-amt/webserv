/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:09:03 by samajat           #+#    #+#             */
/*   Updated: 2023/04/08 20:08:35 by samajat          ###   ########.fr       */
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
        std::string _redir_location;

    public:
        StatusCode(std::string msg);
        StatusCode(std::string msg, std::string redir_location);
        virtual const char* what() const throw();
        bool operator==(const std::string& rhs);
        bool is_error_status() const;
        std::string get_status_code() const;
        std::string get_associated_page() const;
        std::string get_redir_location() const;
        virtual ~StatusCode()throw();
};


#endif