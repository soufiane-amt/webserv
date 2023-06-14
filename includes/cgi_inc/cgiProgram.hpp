/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgiProgram.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:09:17 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/14 16:11:15 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIPROGRAM_HPP
# define CGIPROGRAM_HPP

#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

//prototype for executing CGI

class CGI
{
    private:
        std::string _name;
        std::string _output;
        std::vector<std::string> _env;
        std::vector<std::string> _cgi;
    public:
        CGI();
        ~CGI();
        void    checkCGI();
        void    handleCGI();
        //cgi directive in config file
        void    setCGIpath(std::string filename);
};

char**  convert_vector_to_char_array(std::vector<std::string>& vec) ;
void    freeConvertedArray(char** array, size_t size);

#endif
