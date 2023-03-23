/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:48:32 by sismaili          #+#    #+#             */
/*   Updated: 2023/03/23 17:56:06 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Utility/utils.hpp"
#include "../../includes/config/config.hpp"

Config::Config(std::ifstream &file)
{
	while (std::getline(file, line))
	{
		pos = line.find_first_not_of(" \t");
		if (pos != std::string::npos)
			line = line.substr(pos);
		lines.push_back(line);
	}
	checker();
}

void	Config::checker()
{
	for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); it++)
	{
		line = *it;
		pos = line.find(' ');
		if (pos != std::string::npos)
		{
			key = line.substr(0, pos);
			value = line.substr(pos + 1);
			map_config[key] = value;
		}
	}
}

const std::string	Config::get_key(const std::string &key) const
{
	std::map<std::string, std::string>::const_iterator it = map_config.find(key);
	if (it != map_config.end())
		return it->second;
	return "Not found";
}

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
		Config	test(file);
		std::cout << test.get_key("listen") << std::endl;
	}
	return (0);
}