/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requestParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:09 by samajat           #+#    #+#             */
/*   Updated: 2023/03/18 10:51:47 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "requestParser.hpp"




clientRequestParser::clientRequestParser(std::string clientRequestMsg) //if one of the _tokens lines has a height of two please declare it as an error
{
    _tokens = utility::split(clientRequestMsg, CRLF);
    parseHeader();
}

std::string clientRequestParser::getValue (std::string key)
{
    return (_request[key]);
}

void    clientRequestParser::parseFirstLine ()
{
    std::string key;
    std::string value;
    size_t  pos = _tokens[0].find(SP);
    _request["method"] = _tokens[0].substr(0, pos);
    _tokens[0].erase(0, pos + 1);
    pos = _tokens[0].find(SP);
    _request["uri"] = _tokens[0].substr(0, pos);
    _tokens[0].erase(0, pos + 1);
    _request["version"] = _tokens[0];
}

void    clientRequestParser::parseOtherLines (std::string line)
{
    std::string key;
    std::string value;
    size_t  pos = line.find(":");
    key = line.substr(0, pos);
    line.erase(0, pos + 1);
    value = line;
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
    for (int i = 255; i >= 0; i--)
    {
        if ((_request.begin())->second[0] == i)
            std::cout << "the char is " << i << std::endl;
        if ((_request.begin())->second[1] == i)
            std::cout << "the char is " << i << std::endl;
    }
    std::cout << (_request.begin())->first.size () <<std::endl;
    std::cout << (_request.begin())->second.size () <<std::endl;
    
        
}

