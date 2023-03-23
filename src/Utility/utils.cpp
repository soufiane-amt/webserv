/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:52 by samajat           #+#    #+#             */
/*   Updated: 2023/03/23 17:19:08 by samajat          ###   ########.fr       */
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
            tokens.push_back(token);
            str.erase(0, pos + delimiter.length());
            while (str.length() >=delimiter.length() && ( str.substr(0, delimiter.length())) == delimiter)
                str.erase(0, delimiter.length());      
        }
        tokens.push_back(str);
        return tokens;
}


/* ************************************************************************** */
                            // utility::trim :
/* ************************************************************************** */


std::string utility::left_trim(const std::string &s, const std::string &delimiter)
{
    size_t start = s.find_first_not_of(delimiter);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string utility::right_trim(const std::string &s, const std::string &delimiter)
{
    size_t end = s.find_last_not_of(delimiter);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}


/* ************************************************************************** */
                            // utility::case insensitive search :
/* ************************************************************************** */

std::string utility::trim(const std::string &s, const std::string &delimiter) {
    return right_trim(left_trim(s, delimiter), delimiter);
}

/* ************************************************************************** */
                            // utility::case insensitive search :
/* ************************************************************************** */


bool utility::caseInsensitiveStringCompare(char a, char b)
{
    return std::toupper(a) == std::toupper(b);
}

std::string::iterator utility::caseInsensitiveSearch(std::string & str1, const std::string & str2)
{
    return std::search(str1.begin(), str1.end(), str2.begin(), str2.end(), caseInsensitiveStringCompare);
}


/* ************************************************************************** */
                            // utility::get_date :
/* ************************************************************************** */

std::string utility::get_date()
{
    std::time_t t = std::time(nullptr);
    return (std::asctime(std::localtime(&t)));
}