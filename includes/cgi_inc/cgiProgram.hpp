/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgiProgram.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:09:17 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/15 17:30:16 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIPROGRAM_HPP
# define CGIPROGRAM_HPP

#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

class CGI
{
    private:
        std::vector<std::string> _cgi;
    public:
        CGI();
        ~CGI();
        void    handleCGI(std::string &body, std::string &resp);
        void    setCGIpath(std::string filename);
};

char**  convert_vector_to_char_array(std::vector<std::string>& vec) ;
void    freeConvertedArray(char** array, size_t size);

#endif
