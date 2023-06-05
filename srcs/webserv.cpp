/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:56:03 by samajat           #+#    #+#             */
/*   Updated: 2023/06/05 17:12:00 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*temp server headers*/
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "requestParser.hpp"
#include "responding.hpp"
#include "errorManager.hpp"
#include <fcntl.h>


std::string msg= "GET / HTTP/1.1\r\n"
            "host: 192.241.213.46:6880\r\n"
            "Upgrade-Insecure-Requests: 1\r\n"
            "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
            "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_3) AppleWebKit/602.4.8 (KHTML, like Gecko) Version/10.0.3 Safari/602.4.8\r\n"
            "Accept-Language: en-us\r\n"
            "Accept-Encoding: gzip, deflate\r\n"
            "Connection: keep-alive\r\n\r\n";

std::string resp = "HTTP/1.1 200 OK\r\n"
    "Server: webserver-cpp\r\n"
    "Content-type: text/html\r\n\r\n"
    "<html>hello, world</html>\r\n";
    
//According to RFC "Each header field consists of a name followed by a colon (":") and the field value. Field names are case-insensitive. "
//So we need to convert all the keys to lower case
// std::string toLower(std::string str)
// {
//     std::transform(str.begin(), str.end(), str.begin(), ::tolower);
//     return str;
// }


Config	parser;

int	check_file_name(std::string config, std::string end_char)
{
	if (config.length() <= end_char.length()
		|| config.substr(config.length() - end_char.length()) != end_char)
	{
		std::cout << "error in file name" << std::endl;
		return (1);
	}
	return (0);
}

int	ft_parsing(int ac, char *av)
{
	if (ac != 2)
	{
		std::cerr << "Bad arguments" << std::endl;
		return (1);
	}
	std::string		config = av;
	std::ifstream file (config);
	
	std::string		end_char = ".conf";

	if (file)
	{
		if (check_file_name(config, end_char))
			return (1);
	}
	else
	{
		std::cout << "there is no config file" << std::endl;
		return (1);
	}
	try
	{
		Config parser2(file);
		parser = parser2;
		parser.server_print();
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}


std::vector<char>    request_response(std::string msg)
{
    clientRequestParser test(msg);
    http_message_t &_request = test.getRequest();

    try
    {
            errorManager::isRequestValid(_request);
            responsePreparation response(_request);
        
            return response.get_response();
        
    }
    catch(const StatusCode& e)
    {
        responsePreparation response(_request, e);
        return response.get_response();
    }
    return std::vector<char>();
}

// int main (int argc, char **argv)
// {
// 	if (ft_parsing(argc, argv[1]))
// 		return (1);
//     if (argc != 2)
//     {
//         std::cout << "Usage: ./webserv [port]" << std::endl;
//         return 0;
//     }
//     try
//     {
// 		int port;
// 		std::cin >> port;
//         tempServer(port);
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
    
    // clientRequestParser test(msg);
    // http_message_t &_request = test.getRequest();

    // try
    // {
    //     errorManager::isRequestValid(_request);
    //     responsePreparation response(_request);
    //     std::cout << response.get_response();
    // }
    // catch(const StatusCode& e)
    // {
    //     responsePreparation response(_request, e);
    //     std::cout << response.get_response();
    // }
// }
