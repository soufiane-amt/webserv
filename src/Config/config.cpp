/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:48:32 by sismaili          #+#    #+#             */
/*   Updated: 2023/05/11 23:42:24 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"

std::string	Config::lstrtrim(std::string &str)
{
	size_t	start;

	start = str.find_first_not_of(" \t");
	if (start == std::string::npos)
		return ("");
	str = str.substr(start);
	return (str);
}

std::string	Config::rstrtrim(std::string &str)
{
	size_t	end;

	end = str.find_last_not_of(" \t");
	if (end == std::string::npos)
		return ("");
	str = str.substr(0, end + 1);
	return (str);
}

void	Config::server_block(vector_it &it)
{
	size_t	pos;

	pos = it->find_first_of("#");
	if (pos != std::string::npos)
	{
		*it = it->substr(0, pos);
		*it = rstrtrim(*it);
		if (it->length() != 8)
			throw "Error in server line";
	}
}

void	Config::check_server(std::vector<std::string> &lines)
{
	int	i = 0;

	for (vector_it it = lines.begin(); it != lines.end(); it++)
	{
		if (*it == "" || it->at(0) == '#')
			continue;
		else if (it->find("server {", 0) == std::string::npos && i == 0)
			throw "Error, first line must contains server block";
		else if (it->find("server {", 0) == 0)
		{
			server_block(it);
			i++;
		}
		else
			throw "Error";
	}
}

Config::Config(std::ifstream &file)
{
	std::string	line;

	while (std::getline(file, line))
	{
		line = lstrtrim(line);
		line = rstrtrim(line);
		lines.push_back(line);
	}
	check_server(lines);
}
