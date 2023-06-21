/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgiProgram.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:09:17 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/21 12:10:25 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIPROGRAM_HPP
# define CGIPROGRAM_HPP

#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>
#include <cctype>

class CGI
{
    private:
        std::vector<std::string> _cgi;
    public:
        CGI();
        ~CGI();
        void    handleCGI(std::string &body, std::string &resp);
        int     hasPythonOrPhpExtension(const std::string& filename);
        void    setCGIpath(std::string filename);
};

char**  convert_vector_to_char_array(std::vector<std::string>& vec) ;
void    freeConvertedArray(char** array, size_t size);

#endif
