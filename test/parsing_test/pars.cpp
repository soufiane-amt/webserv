/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:21:57 by samajat           #+#    #+#             */
/*   Updated: 2023/03/16 15:08:02 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
typedef std::map<std::string, std::string> directive_t;
typedef std::map<std::string, directive_t> location_t;
typedef std::map<std::string, std::pair<directive_t, location_t> > server_t;


#define CRLF "\r\n"
#define SP " "

struct simpleConfPars
{
    void    get_configs ()
    {
        server_t server;
        directive_t directives;
        location_t locations;
        
        directives["listen"] = "80";
        directives["server_name"] = "example.com";
        locations["/"]["root"] = "/var/www/html";
        locations["/"]["index"] = "index.html";
        locations["/images/"]["root"] = "/var/www";
        locations["/images/"]["index"] = "index.html";
        directives["error_page"] = "404 /404.html";
        locations["/404.html"]["root"] = "/var/www/html";
        server[""] = std::make_pair(directives, locations);
    }
};


std::string msg= "GET / HTTP/1.1\r\n"
            "Host: 192.241.213.46:6880\n"
            "Upgrade-Insecure-Requests: 1\r\n"
            "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
            "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_3) AppleWebKit/602.4.8 (KHTML, like Gecko) Version/10.0.3 Safari/602.4.8\r\n"
            "Accept-Language: en-us\r\n"
            "Accept-Encoding: gzip, deflate\r\n"
            "Connection: keep-alive\r\n\r\n";

class utility
{
    public:
    static std::vector<std::string> split(std::string str, std::string delimiter) {
        std::vector<std::string> tokens;
        size_t pos = 0;
        std::string token;
        while ((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, pos);
            tokens.push_back(token);
            str.erase(0, pos + delimiter.length());
        }
        tokens.push_back(str);
        return tokens;
    }
};

class clientRequestParser
{
    private:
    std::map <std::string, std::string> request;
    std::vector<std::string>             tokens;

    public:
    
    clientRequestParser(std::string clientRequestMsg) //if one of the tokens lines has a height of two please declare it as an error
    {
        std::stringstream ss(clientRequestMsg);
        tokens =utility::split(clientRequestMsg, CRLF);
        // for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++)
        // {
        //     std::cout << *it << std::endl;
        // }
    }
    
    std::string getValue (std::string key)
    {
        return (request[key]);
    }
};


int main()
{
    clientRequestParser test(msg);
    
    return 0;
}