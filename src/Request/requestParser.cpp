/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requestParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:09 by samajat           #+#    #+#             */
/*   Updated: 2023/03/23 11:47:59 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "requestParser.hpp"




clientRequestParser::clientRequestParser(std::string clientRequestMsg):_header_fields (_request.first) //if one of the _tokens lines has a height of two please declare it as an error
{
    std::vector<std::string>spl_request = utility::split(clientRequestMsg, CRLF CRLF);
    if (spl_request.size() != 2)
        throw StatusCode(BAD_REQUEST);

    _tokens = utility::split(spl_request[0], CRLF);
    _request.second = spl_request[1];
    // for (tokens_t::iterator it = _tokens.begin(); it != _tokens.end(); it++)
    //     std::cout << "=>" << *it << std::endl;    
    parseHeader();
}


http_message_t& clientRequestParser::getRequest ()
{
    return (_request);
}

void    clientRequestParser::parseFirstLine ()
{
    std::vector<std::string> firstLineParts = utility::split(_tokens[0], SP);
    if (firstLineParts.size() != 3)
        throw StatusCode(BAD_REQUEST);
    _header_fields["Method"] = firstLineParts[0]; 
    _header_fields["URI"] = firstLineParts[1];
    _header_fields["Protocol"] = firstLineParts[2];
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
    line.erase(0, pos + 1);
    value = utility::trim(line, SP);
    for (std::string::iterator it = value.begin(); it != value.end(); it++)
        if (isspace(*it) && *it != ' ' )
            throw StatusCode(BAD_REQUEST);

    _header_fields[key] = value;
}

void    clientRequestParser::parseHeader ()
{
    parseFirstLine ();
    for (tokens_t::iterator it = _tokens.begin() + 1; it != _tokens.end() ; it++)
        parseOtherLines(*it);
}


bool    clientRequestParser::hasBody ()
{
    return (_request.second.size() > 0);
}

const header_t& clientRequestParser::getHeader()
{
    return (_header_fields);
}

std::string clientRequestParser::getBody()
{
    return (_request.second);
}

void    clientRequestParser::displayRequest ()
{
    for (header_t::iterator it = _header_fields.begin(); it != _header_fields.end(); it++)
        std::cout << it->first << " | " << it->second << std::endl;
    std::cout << "the body is :" << _request.second << std::endl;
}

