/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:52 by samajat           #+#    #+#             */
/*   Updated: 2023/03/31 16:27:29 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "utils.hpp"
#include <fstream>



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
    std::string date = std::asctime(std::localtime(&t));
    date.resize(date.size() - 1);
    return (date);
}

/* ************************************************************************** */
                            // utility::get_file_content :
/* ************************************************************************** */

std::string utility::get_file_content(const std::string& uri)
{
    std::ifstream file(uri);
    std::string content;
    std::string line;

    if (file.is_open())
    {
        while (getline(file, line))
            content += line + "\n";
        file.close();
    }
    return content;
}


/* ************************************************************************** */
                            // utility::get_status_code :
/* ************************************************************************** */

std::pair <status_code, std::string> get_status_code(const std::string& redirector)
{
    std::vector<std::string> tokens = utility::split(redirector, " ");
    
    
    if (token[0] == "100")
        return (std::make_pair(status_code(CONTINUE), tokens[1]));   
    if (token[0] == "101")
        return (std::make_pair(status_code(SWITCHING_PROTOCOLS), tokens[1]));
    if (token[0] == "200")
        return (std::make_pair(status_code(OK), tokens[1]));
    if (token[0] == "201")
        return (std::make_pair(status_code(CREATED), tokens[1]));
    if (token[0] == "202")
        return (std::make_pair(status_code(ACCEPTED), tokens[1]));
    if (token[0] == "203")
        return (std::make_pair(status_code(NON_AUTHORITATIVE_INFORMATION), tokens[1]));
    if (token[0] == "204")
        return (std::make_pair(status_code(NO_CONTENT), tokens[1]));
    if (token[0] == "205")
        return (std::make_pair(status_code(RESET_CONTENT), tokens[1]));
    if (token[0] == "206")
        return (std::make_pair(status_code(PARTIAL_CONTENT), tokens[1]));
    if (token[0] == "300")
        return (std::make_pair(status_code(MULTIPLE_CHOICES), tokens[1]));
    if (token[0] == "301")
        return (std::make_pair(status_code(MOVED_PERMANENTLY), tokens[1]));
    if (token[0] == "302")
        return (std::make_pair(status_code(FOUND), tokens[1]));
    if (token[0] == "303")
        return (std::make_pair(status_code(SEE_OTHER), tokens[1]));
    if (token[0] == "304")
        return (std::make_pair(status_code(NOT_MODIFIED), tokens[1]));
    if (token[0] == "305")
        return (std::make_pair(status_code(USE_PROXY), tokens[1]));
    if (token[0] == "307")
        return (std::make_pair(status_code(TEMPORARY_REDIRECT), tokens[1]));
    if (token[0] == "400")
        return (std::make_pair(status_code(BAD_REQUEST), tokens[1]));
    if (token[0] == "401")
        return (std::make_pair(status_code(UNAUTHORIZED), tokens[1]));
    if (token[0] == "402")
        return (std::make_pair(status_code(PAYMENT_REQUIRED), tokens[1]));
    if (token[0] == "403")
        return (std::make_pair(status_code(FORBIDDEN), tokens[1]));
    if (token[0] == "404")
        return (std::make_pair(status_code(NOT_FOUND), tokens[1]));
    if (token[0] == "405")
        return (std::make_pair(status_code(METHOD_NOT_ALLOWED), tokens[1]));
    if (token[0] == "406")
        return (std::make_pair(status_code(NOT_ACCEPTABLE), tokens[1]));
    if (token[0] == "407")
        return (std::make_pair(status_code(PROXY_AUTHENTICATION_REQUIRED), tokens[1]));
    if (token[0] == "408")
        return (std::make_pair(status_code(REQUEST_TIMEOUT), tokens[1]));
    if (token[0] == "409")
        return (std::make_pair(status_code(CONFLICT), tokens[1]));
    if (token[0] == "410")
        return (std::make_pair(status_code(GONE), tokens[1]));
    if (token[0] == "411")
        return (std::make_pair(status_code(LENGTH_REQUIRED), tokens[1]));
    if (token[0] == "412")
        return (std::make_pair(status_code(PRECONDITION_FAILED), tokens[1]));
    if (token[0] == "413")
        return (std::make_pair(status_code(PAYLOAD_TOO_LARGE), tokens[1]));
    if (token[0] == "414")
        return (std::make_pair(status_code(URI_TOO_LONG), tokens[1]));
    if (token[0] == "415")
        return (std::make_pair(status_code(UNSUPPORTED_MEDIA_TYPE), tokens[1]));
    if (token[0] == "416")
        return (std::make_pair(status_code(RANGE_NOT_SATISFIABLE), tokens[1]));
    if (token[0] == "417")
        return (std::make_pair(status_code(EXPECTATION_FAILED), tokens[1]));
    if (token[0] == "500")
        return (std::make_pair(status_code(INTERNAL_SERVER_ERROR), tokens[1]));
    if (token[0] == "501")
        return (std::make_pair(status_code(NOT_IMPLEMENTED), tokens[1]));
    if (token[0] == "502")
        return (std::make_pair(status_code(BAD_GATEWAY), tokens[1]));
    if (token[0] == "503")
        return (std::make_pair(status_code(SERVICE_UNAVAILABLE), tokens[1]));
    if (token[0] == "504")
        return (std::make_pair(status_code(GATEWAY_TIMEOUT), tokens[1]));
    if (token[0] == "505")
        return (std::make_pair(status_code(HTTP_VERSION_NOT_SUPPORTED), tokens[1]));
    return (std::make_pair(status_code(HTTP_VERSION_NOT_SUPPORTED), tokens[1]));
         

}
