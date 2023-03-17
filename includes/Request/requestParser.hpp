/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requestParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:09 by samajat           #+#    #+#             */
/*   Updated: 2023/03/17 14:21:37 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include "utils.hpp"



std::string msg= "GET / HTTP/1.1\r\n"
            "Host: 192.241.213.46:6880\r\n"
            "Upgrade-Insecure-Requests: 1\r\n"
            "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
            "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_3) AppleWebKit/602.4.8 (KHTML, like Gecko) Version/10.0.3 Safari/602.4.8\r\n"
            "Accept-Language: en-us\r\n"
            "Accept-Encoding: gzip, deflate\r\n"
            "Connection: keep-alive\r\n\r\n";

#define CRLF "\r\n"
#define SP " "


class clientRequestParser
{
    private:
    typedef    std::vector<std::string>             tokens_t;
    typedef    std::map <std::string, std::string>  request_t;


    tokens_t                    tokens;
    request_t                   request;
    
    public:
    
    clientRequestParser(std::string clientRequestMsg); //if one of the tokens lines has a height of two please declare it as an error;
    std::string getValue (std::string key);

    private:
    void    parseFirstLine ();
    void    parseOtherLines (std::string line);
    void    parseHeader ();

    public:
    void    displayRequest ();
};

