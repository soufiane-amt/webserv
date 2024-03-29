/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requestParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:09 by samajat           #+#    #+#             */
/*   Updated: 2023/06/02 16:14:14 by samajat          ###   ########.fr       */
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
    
    
    public:
    
    clientRequestParser(std::string clientRequestMsg); //if one of the tokens  has more than one line please declare it as an error;
    
    //Getters
    http_message_t        &getRequest ();
    const header_t&       getHeader();
    std::string           getBody();
    int                   getContentLength();//this function returns the content length specified in the header if there is any, otherwise it returns -1 as a sign of the abscence of the header
    
    //confirmation functions
    bool    hasBody ();
    private:
    void    parseFirstLine ();
    void    parseOtherLines (std::string line);
    void    parseHeader ();
    void    check_the_absoluteURI ();

    void    sendError ();

    bool    is_error_status ();
    public:
    void    displayRequest ();
};

#endif