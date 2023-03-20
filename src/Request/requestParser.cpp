/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requestParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:09 by samajat           #+#    #+#             */
/*   Updated: 2023/03/20 17:15:49 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "requestParser.hpp"




clientRequestParser::clientRequestParser(std::string clientRequestMsg) //if one of the _tokens lines has a height of two please declare it as an error
{
    _tokens = utility::split(clientRequestMsg, CRLF);
    for (tokens_t::iterator it = _tokens.begin(); it != _tokens.end(); it++)
        std::cout << "=>" << *it << std::endl;    
    parseHeader();
    
}

std::string clientRequestParser::getValue (std::string key)
{
    return (_request[key]);
}


const request_t& clientRequestParser::getRequest ()
{
    return (_request);
}

void    clientRequestParser::parseFirstLine ()
{
    std::vector<std::string> firstLineParts = utility::split(_tokens[0], SP);
    if (firstLineParts.size() != 3)
        throw ParsingErrorDetected(BAD_REQUEST);
    _request["Method"] = firstLineParts[0];
    _request["URI"] = firstLineParts[1];
    _request["Protocol"] = firstLineParts[2];
}

void    clientRequestParser::parseOtherLines (std::string line)
{
    std::string key;
    std::string value;
    size_t  pos = line.find(":");
    key = line.substr(0, pos);
    for (std::string::iterator it = key.begin(); it != key.end(); it++)
        if (isspace(*it))
            throw ParsingErrorDetected(BAD_REQUEST);
    
    line.erase(0, pos + 1);
    value = line.;
    for (std::string::iterator it = value.begin(); it != value.end(); it++)
        if (isspace(*it))
            throw ParsingErrorDetected(BAD_REQUEST);
    std::cout << "-------\n";
    _request[key] = value;
}

void    clientRequestParser::parseHeader ()
{
    parseFirstLine ();
    for (tokens_t::iterator it = _tokens.begin() + 1; it != _tokens.end() ; it++)
        parseOtherLines(*it);
}


void    clientRequestParser::displayRequest ()
{
    for (request_t::iterator it = _request.begin(); it != _request.end(); it++)
        std::cout << it->first << " | " << it->second << std::endl;
    // for (int i = 255; i >= 0; i--)
    // {
    //     if ((_request.begin())->second[0] == i)
    //         std::cout << "the char is " << i << std::endl;
    //     if ((_request.begin())->second[1] == i)
    //         std::cout << "the char is " << i << std::endl;
    // }
    // std::cout << (_request.begin())->first.size () <<std::endl;
    // std::cout << (_request.begin())->second.size () <<std::endl;
    
        
}

