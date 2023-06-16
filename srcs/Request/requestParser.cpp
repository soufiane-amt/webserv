/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requestParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:09 by samajat           #+#    #+#             */
/*   Updated: 2023/06/16 21:13:27 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "requestParser.hpp"

clientRequestParser::clientRequestParser(std::string clientRequestMsg) //if one of the _tokens lines has a height of two please declare it as an error
{
    std::vector<std::string>spl_request;
    if (clientRequestMsg.find(CRLF CRLF) != std::string::npos)
        spl_request = utility::split(clientRequestMsg, CRLF CRLF);
    else
        throw StatusCode(BAD_REQUEST); 

    _tokens = utility::split(spl_request[0], CRLF);
    for (size_t i = 1; i < spl_request.size(); i++)
        for (size_t j = 0; j < spl_request[i].size(); j++)
            _request.body.push_back(spl_request[i][j]);
    parseHeader();
}


http_message_t& clientRequestParser::getRequest ()
{
    return (_request);
}

void    clientRequestParser::check_the_absoluteURI ()
{
    std::string &URI = _request.header["URI"];
    if (URI.substr(0, 7) == "http://")
        URI.erase (0, 7);
    else
        return;
    size_t  pos = URI.find_first_of('/');
    if (pos != std::string::npos)
    {
        _request.header["host"] = URI.substr(0, pos);
        URI.erase(0, pos);
        return;
    }
    throw StatusCode(BAD_REQUEST);
}

void    clientRequestParser::parseFirstLine ()
{
    std::vector<std::string> firstLineParts = utility::split(_tokens[0], SP);
    if (firstLineParts.size() != 3)
        throw StatusCode(BAD_REQUEST);
    _request.header["Method"] = firstLineParts[0];
    
    _request.header["QUERY_STRING"] = utility::get_query_string(firstLineParts[1]);
    utility::remove_string_queries(firstLineParts[1]);
    
    _request.header["URI"] = firstLineParts[1];
    
    check_the_absoluteURI ();
    
    _request.header["Protocol"] = firstLineParts[2];
    
}

void    clientRequestParser::parseOtherLines (std::string line)
{
    std::string key;
    std::string value;
    
    size_t  pos = line.find(":");
    key = line.substr(0, pos);
    for (std::string::iterator it = key.begin(); it != key.end(); it++)
        if (isspace(*it))
            throw StatusCode(BAD_REQUEST);
    {//This is to make sure that the key is in lower case .  field  host is case insensitive
    std::string::iterator itr = utility::caseInsensitiveSearch(key, "host");
    if (itr != key.end())
        key = "host";
    }
    //here I make sure to remove the the key part of the header
    line.erase(0, pos + 1);
    //I remove the leading spaces from the value part of the header
    value = utility::trim(line, SP);
    //I make sure that the value part of the header is not empty
    if (value.empty())
        throw StatusCode(BAD_REQUEST);
    //I make sure that the value part of the header does not contain any space other than the space character
    for (std::string::iterator it = value.begin(); it != value.end(); it++)
        if (isspace(*it) && *it != ' ' )
            throw StatusCode(BAD_REQUEST);
    _request.header[key] = value;
}

void    clientRequestParser::parseHeader ()
{
    try
    {
    parseFirstLine ();
    for (tokens_t::iterator it = _tokens.begin() + 1; it != _tokens.end() ; it++)
        parseOtherLines(*it);

    }
    catch(const std::exception& e)
    {
        std::cerr << "the problem is here" << '\n';
    }
    
    
}


bool    clientRequestParser::hasBody ()
{
    return (_request.body.size() > 0);
}

const header_t& clientRequestParser::getHeader()
{
    return (_request.header);
}

std::string clientRequestParser::getBody()
{
    return (_request.body);
}

int         clientRequestParser::getContentLength()
{
    header_t    &header = _request.header;

    if (header.find("Content-Length") == header.end())
        return (-1);
    return (std::atoi(header["Content-Length"].c_str()));
}

void    clientRequestParser::displayRequest ()
{
    // for (header_t::iterator it = _request.header.begin(); it != _request.header.end(); it++)
    //     std::cout << it->first << " | " << it->second << std::endl;
    // std::cout << "the body is :" << _request.body << std::endl;
}

