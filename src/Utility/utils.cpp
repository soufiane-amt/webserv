/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:52 by samajat           #+#    #+#             */
/*   Updated: 2023/05/19 17:37:14 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "utils.hpp"



/* ************************************************************************** */
                            // utility::split :
/* ************************************************************************** */

std::vector<std::string> utility::split(std::string str, std::string delimiter)
{
        std::vector<std::string> tokens;
        size_t pos = 0;
        std::string token;
        while ((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, pos);
			if (token.length() == 0)
			{
            	str.erase(0, pos + delimiter.length());
				continue;
			}
            tokens.push_back(token);
            str.erase(0, pos + delimiter.length());
        }
        tokens.push_back(str);
        return tokens;
}
