/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requestParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:09 by samajat           #+#    #+#             */
/*   Updated: 2023/03/16 17:48:56 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "requestParser.hpp"

clientRequestParser::clientRequestParser(std::string clientRequestMsg) //if one of the tokens lines has a height of two please declare it as an error
{
    tokens = utility::split(clientRequestMsg, CRLF);
    parseHeader();
}

std::string clientRequestParser::getValue (std::string key)
{
    return (request[key]);
}

void    clientRequestParser::parseFirstLine (std::string line)
{
    std::string key;
    std::string value;
    size_t  pos = tokens[0].find(SP);
    request["method"] = tokens[0].substr(0, pos);
    tokens[0].erase(0, pos + 1);
    pos = tokens[0].find(SP);
    request["uri"] = tokens[0].substr(0, pos);
    tokens[0].erase(0, pos + 1);
    request["version"] = tokens[0];
}

void    clientRequestParser::parseOtherLines (std::string line)
{
    std::string key;
    std::string value;
    size_t  pos = line.find(":");
    key = line.substr(0, pos);
    line.erase(0, pos + 1);
    value = line;
    request[key] = value;
}

void    clientRequestParser::parseHeader ()
{
    parseFirstLine (*tokens.begin());
    for (tokens_t::iterator it = tokens.begin() + 1; it != tokens.end() ; it++)
        parseOtherLines(*it);
}


void    clientRequestParser::displayRequest ()
{
    for (request_t::iterator it = request.begin(); it != request.end(); it++)
        std::cout << it->first << " | " << it->second << std::endl;
}

