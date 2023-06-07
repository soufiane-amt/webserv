/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:56:03 by samajat           #+#    #+#             */
/*   Updated: 2023/06/07 16:30:27 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*temp server headers*/
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "pollingServ.hpp"
#include <fcntl.h>
    
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
		// parser.server_print();
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return (-1);
	}
	return (0);
}


int main (int argc, char **argv, char **env)
{
	(void)env;
	//create poll object to handle servers
    polling pl;
	
	if (ft_parsing(argc, argv[1]) < 0)
		return (1);
    if (argc != 2)
    {
        std::cout << "Usage: ./webserv [port]" << std::endl;
        return 0;
    }
	std::cout << "Welcome To Webserv1.0: " << std::endl;
    std::multimap<std::string,std::string> servs = parser.get_host();
	std::multimap<std::string, std::string>::iterator it = servs.begin();
	std::cout << "Size = " << servs.size() << std::endl;
	for (;it != servs.end(); it++)
	{
		std::istringstream iss(it->first);
		int port;
		iss >> port;
		std::cout << port << std::endl;
		std::cout << it->second << std::endl;
		tcpServer sock(pl, port, it->second);
		pl.pushServer(sock);
	}

	 while (1)
    {
        //waiting for events using poll()
        int poll_count = pl.callPoll((pollfd *)pl.getPollfdAddrs(), pl.getSize(), -1);
        
        if (poll_count  == -1)
        {
            perror("poll");
            // exit(EXIT_FAILURE);
            continue;
        }
        else
        {
            //handle I/O events
            pl.handlePoll();        
        }
    }
    
    //calling destructor will close all connections
    return (0);
   
}
