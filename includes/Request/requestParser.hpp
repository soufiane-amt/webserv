/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requestParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:09 by samajat           #+#    #+#             */
/*   Updated: 2023/03/21 18:38:02 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include "utils.hpp"
#include "exception.hpp"





class clientRequestParser
{
    private:
    typedef    std::vector<std::string>                        tokens_t;
    typedef    std::pair<header_t, std::string>                request_t;


    http_message_t              _request;//This is the pair that will contain request's header and body
    tokens_t                    _tokens;//This is the vector that will contain the request tokens
    
    header_t&                   _header_fields;//This is the map that will contain the request key value pairs
    
    public:
    
    clientRequestParser(std::string clientRequestMsg); //if one of the tokens  has more than one line please declare it as an error;
    
    //Getters
    http_message_t getRequest ();
    const header_t&             getHeader();
    std::string           getBody();
    // std::string        getMethod();
    // std::string        getURI();
    // std::string        getProtocol();
    // std::string        getPort();
    
    //confirmation functions
    bool    hasBody ();
    private:
    void    parseFirstLine ();
    void    parseOtherLines (std::string line);
    void    parseHeader ();

    public:
    void    displayRequest ();
};

#endif