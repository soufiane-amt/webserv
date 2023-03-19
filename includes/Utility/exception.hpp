/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:09:03 by samajat           #+#    #+#             */
/*   Updated: 2023/03/19 15:10:59 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

# include <exception>
# include <string>


class ParsingErrorDetected : public std::exception
{
    private:
        std::string _msg;
    public:
        ParsingErrorDetected(std::string msg);
        virtual const char* what() const throw();
};

#endif