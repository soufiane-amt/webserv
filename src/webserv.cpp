/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:56:03 by samajat           #+#    #+#             */
/*   Updated: 2023/05/19 17:51:26 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"
#include "utils.hpp"

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

int	main(int ac, char **av)
{

	if (ac == 2)
	{
		std::string		config = av[1];
		std::ifstream	file(config);
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
			Config	test(file);
		}
		catch(std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	return (0);
}