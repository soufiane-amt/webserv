/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:47:23 by samajat           #+#    #+#             */
/*   Updated: 2023/05/23 15:59:38 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> split( std::string& str, const std::string& delimiter)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    tokens.reserve(str.size() / delimiter.size() + 1);  // Preallocate memory for tokens
    
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        tokens.push_back(std::move(token));  // Move ownership of the string
        str.erase(0, pos + delimiter.length());
    }
    
    tokens.push_back(std::move(str));  // Move ownership of the remaining string
    return tokens;
}

int main()
{
    std::string str = "hello world    f  f  df      fd";
    std::vector <std::string> vec = split(str, " ");
    for (std::vector <std::string>::iterator it = vec.begin(); it != vec.end(); )
    {
        
    }
    return 0;
}
