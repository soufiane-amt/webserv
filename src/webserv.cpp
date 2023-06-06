/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:56:03 by samajat           #+#    #+#             */
/*   Updated: 2023/06/06 21:40:01 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"
#include "utils.hpp"

std::ifstream	file;
Config	test;

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
		Config test2(file);
		test = test2;
		// test.server_print();
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}

int	main(int ac, char **av)
{
	if (ft_parsing(ac, av[1]))
		return (1);
	return (0);
}