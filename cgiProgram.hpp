/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgiProgram.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:09:17 by fech-cha          #+#    #+#             */
/*   Updated: 2023/05/22 20:29:24 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIPROGRAM_HPP
# define CGIPROGRAM_HPP

#include <string>
#include <iostream>
#include <unistd.h>

//prototype for executing CGI

class CGI
{
    private:
        std::string _name;
        std::string _output;
    public:
        CGI();
        ~CGI();
        void    checkCGI();
        void    handleCGI();
        //set env vars
        //cgi directive in config file
};

#endif