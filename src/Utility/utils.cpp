/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:52 by samajat           #+#    #+#             */
/*   Updated: 2023/04/05 18:25:02 by samajat          ###   ########.fr       */
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
                            // utility::get_StatusCode :
/* ************************************************************************** */

StatusCode utility::redirector_proccessor(const std::string& redirector)
{
    std::vector<std::string> tokens = utility::split(redirector, " ");
    
    
    if (tokens[0] == "100")
        return (StatusCode(CONTINUE, tokens[1]));   
    if (tokens[0] == "101")
        return (StatusCode(SWITCHING_PROTOCOLS, tokens[1]));
    if (tokens[0] == "200")
        return (StatusCode(OK, tokens[1]));
    if (tokens[0] == "201")
        return (StatusCode(CREATED, tokens[1]));
    if (tokens[0] == "202")
        return (StatusCode(ACCEPTED, tokens[1]));
    if (tokens[0] == "203")
        return (StatusCode(NON_AUTHORITATIVE_INFORMATION, tokens[1]));
    if (tokens[0] == "204")
        return (StatusCode(NO_CONTENT, tokens[1]));
    if (tokens[0] == "205")
        return (StatusCode(RESET_CONTENT, tokens[1]));
    if (tokens[0] == "206")
        return (StatusCode(PARTIAL_CONTENT, tokens[1]));
    if (tokens[0] == "300")
        return (StatusCode(MULTIPLE_CHOICES, tokens[1]));
    if (tokens[0] == "301")
        return (StatusCode(MOVED_PERMANENTLY, tokens[1]));
    if (tokens[0] == "302")
        return (StatusCode(FOUND, tokens[1]));
    if (tokens[0] == "303")
        return (StatusCode(SEE_OTHER, tokens[1]));
    if (tokens[0] == "304")
        return (StatusCode(NOT_MODIFIED, tokens[1]));
    if (tokens[0] == "305")
        return (StatusCode(USE_PROXY, tokens[1]));
    if (tokens[0] == "307")
        return (StatusCode(TEMPORARY_REDIRECT, tokens[1]));
    if (tokens[0] == "400")
        return (StatusCode(BAD_REQUEST, tokens[1]));
    if (tokens[0] == "401")
        return (StatusCode(UNAUTHORIZED, tokens[1]));
    if (tokens[0] == "402")
        return (StatusCode(PAYMENT_REQUIRED, tokens[1]));
    if (tokens[0] == "403")
        return (StatusCode(FORBIDDEN, tokens[1]));
    if (tokens[0] == "404")
        return (StatusCode(NOT_FOUND, tokens[1]));
    if (tokens[0] == "405")
        return (StatusCode(METHOD_NOT_ALLOWED, tokens[1]));
    if (tokens[0] == "406")
        return (StatusCode(NOT_ACCEPTABLE, tokens[1]));
    if (tokens[0] == "407")
        return (StatusCode(PROXY_AUTHENTICATION_REQUIRED, tokens[1]));
    if (tokens[0] == "408")
        return (StatusCode(REQUEST_TIMEOUT, tokens[1]));
    if (tokens[0] == "409")
        return (StatusCode(CONFLICT, tokens[1]));
    if (tokens[0] == "410")
        return (StatusCode(GONE, tokens[1]));
    if (tokens[0] == "411")
        return (StatusCode(LENGTH_REQUIRED, tokens[1]));
    if (tokens[0] == "412")
        return (StatusCode(PRECONDITION_FAILED, tokens[1]));
    if (tokens[0] == "413")
        return (StatusCode(PAYLOAD_TOO_LARGE, tokens[1]));
    if (tokens[0] == "414")
        return (StatusCode(URI_TOO_LONG, tokens[1]));
    if (tokens[0] == "415")
        return (StatusCode(UNSUPPORTED_MEDIA_TYPE, tokens[1]));
    if (tokens[0] == "416")
        return (StatusCode(RANGE_NOT_SATISFIABLE, tokens[1]));
    if (tokens[0] == "417")
        return (StatusCode(EXPECTATION_FAILED, tokens[1]));
    if (tokens[0] == "500")
        return (StatusCode(INTERNAL_SERVER_ERROR, tokens[1]));
    if (tokens[0] == "501")
        return (StatusCode(NOT_IMPLEMENTED, tokens[1]));
    if (tokens[0] == "502")
        return (StatusCode(BAD_GATEWAY, tokens[1]));
    if (tokens[0] == "503")
        return (StatusCode(SERVICE_UNAVAILABLE, tokens[1]));
    if (tokens[0] == "504")
        return (StatusCode(GATEWAY_TIMEOUT, tokens[1]));
    if (tokens[0] == "505")
        return (StatusCode(HTTP_VERSION_NOT_SUPPORTED, tokens[1]));
    return (StatusCode(HTTP_VERSION_NOT_SUPPORTED, tokens[1]));
}


/* ************************************************************************** */
                            // utility::directory_listing :
/* ************************************************************************** */

std::string     utility::list_directory(const std::string& directory)
{
    DIR *dir;
    struct dirent *ent;
    std::string listing_file;
    
    // Open the current directory
    std::cout <<  "vvvvvvvv" << directory.c_str() << std::endl;
    dir = opendir(directory.c_str());
    if (dir == NULL)
        return "";
    // Output the HTML header
    listing_file += "<html><head><title>Directory Listing</title></head><body>\n";
    listing_file += "<h1>Directory Listing</h1><hr>\n";
    
    // Output the list of files and directories in the directory as links
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_DIR) {
            // Output a link for a directory
            listing_file += "<a href=\"" + std::string(ent->d_name) + "/\">" + std::string(ent->d_name) + "/</a><br>\n";
        } else {
            // Output a link for a file
            listing_file += "<a href=\"" + std::string(ent->d_name) + "\">" + std::string(ent->d_name) + "</a><br>\n";
        }
    }
    
    // Output the HTML footer
    listing_file += "<hr></body></html>\n";
    
    // Close the directory
    closedir(dir);
    return listing_file;
}

/* ************************************************************************** */
                            // utility::check_file_or_directory :
/* ************************************************************************** */

int        utility::check_file_or_directory(const std::string& path)
{
    struct stat info;
    
    if (stat(path.c_str(), &info) == -1)
        return 0;
    if (S_ISDIR(info.st_mode))
        return S_DIRECTORY;
    else if (!S_ISDIR(info.st_mode))
        return S_FILE;
    return 0;
}
