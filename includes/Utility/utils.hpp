/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:52 by samajat           #+#    #+#             */
/*   Updated: 2023/03/20 14:30:50 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_HPP
# define UTILS_HPP



#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <fstream>


/* ************************************************************************** */
                            // Special Macros :
/* ************************************************************************** */

#define CRLF "\r\n"
#define SP " "



/* ************************************************************************** */
                            // Typedefs :
/* ************************************************************************** */

typedef std::map<std::string, std::string> directive_t;
typedef std::map<std::string, directive_t> location_t;
typedef std::vector<std::pair<directive_t, location_t> > server_t;


/* ************************************************************************** */
                            // utility :
/* ************************************************************************** */

struct utility
{
    static std::vector<std::string> split(std::string str, std::string delimiter);
};

#endif