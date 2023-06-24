/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:56:03 by samajat           #+#    #+#             */
/*   Updated: 2023/06/24 10:39:04 by fech-cha         ###   ########.fr       */
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

int                            errorManager::targeted_serv = 0;
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
		exit (1);
	}
	std::string		config = av;
	std::ifstream file (config);
	
	std::string		end_char = ".conf";

	if (file)
	{
		if (check_file_name(config, end_char))
			exit (1);
	}
	else
	{
		std::cout << "Invalid config file" << std::endl;
		exit (1);
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
		exit (1);
	}
	return (0);
}


int main (int argc, char **argv)
{
	//create poll object to handle servers
    polling pl;
	
	ft_parsing(argc, argv[1]);
	std::cout << "Welcome To Webserv1.0: " << std::endl;
    std::vector<std::pair<std::string, std::string> > servs = parser.get_host();
	std::vector<std::pair<std::string, std::string> >::iterator it = servs.begin();
	int index = 0;
	std::vector<std::string> ports = parser.get_ports_number();
	std::vector<std::string>::iterator iter = ports.begin();
	std::vector<std::string> temp;
	std::vector<std::string>::iterator temp_it;
	for (;it != servs.end(); it++)
	{
		if (iter != ports.end())
		{
			temp = utility::split(*iter, " ");
		 	temp_it = temp.begin();
		}
		for (size_t i = temp.size(); i > 0 && iter != ports.end(); i--)
		{
			std::istringstream iss(*temp_it);
			int port;
			iss >> port;
			tcpServer sock(pl, port, it->second, index);
			pl.pushServer(sock);
			temp_it++;
		}
		if (iter != ports.end())
			iter++;
		index++;
	}

	 while (1)
    {
        //waiting for events using poll()
        int poll_count = pl.callPoll((pollfd *)pl.getPollfdAddrs(), pl.getSize(), 5000);
        
        if (poll_count  == -1)
        {
            perror("poll");
            // exit(EXIT_FAILURE);
            continue;
        }
        else
        {
			//handle timeout
			pl.handleTimeout();   
			
            //handle I/O events
            pl.handlePoll();     
        }
    }
    
    //calling destructor will close all connections
    return (0);
}
