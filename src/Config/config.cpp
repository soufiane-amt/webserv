/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:48:32 by sismaili          #+#    #+#             */
/*   Updated: 2023/05/19 23:56:41 by sismaili         ###   ########.fr       */
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

void	Config::tokenize(std::vector<std::string> &lines)
{
	key_val	kv;

	for (vector_it it = lines.begin(); it != lines.end(); it++)
	{
		if (*it == "server")
		{
			kv.key = TOKEN_SERVER;
			kv.value = *it;
			tokens.push_back(kv);
		}
		else if (*it == "location")
		{
			kv.key = TOKEN_LOCATIOIN;
			kv.value = *it;
			tokens.push_back(kv);
		}
		else if (*it == "{")
		{
			kv.key = TOKEN_O_BRACE;
			kv.value = *it;
			tokens.push_back(kv);
		}
		else if (*it == "}")
		{
			kv.key = TOKEN_C_BRACE;
			kv.value = *it;
			tokens.push_back(kv);
		}
		else if (*it == ";")
		{
			kv.key = TOKEN_SEMICOLON;
			kv.value = *it;
			tokens.push_back(kv);
		}
		else if (it->at(0) == '#')
		{
			kv.key = TOKEN_COMMENTS;
			kv.value = *it;
			tokens.push_back(kv);
		}
		else if (it->at(0) == '/' && *(it - 1) == "location")
		{
			kv.key = TOKEN_L_VALUE;
			kv.value = *it;
			tokens.push_back(kv);
		}
		else if (*it == "listen" || *it == "server_name" || *it == "max_body_size"
			|| *it == "return" || *it == "root" || *it == "autoindex" || *it == "allow"
			|| *it == "index" || *it == "upload")
		{
			kv.key = TOKEN_DIRECTIVE;
			kv.value = *it;
			tokens.push_back(kv);
		}
		else if (it->back() == ';' || tokens.back().key == TOKEN_DIRECTIVE)
		{
			if (it->back() == ';')
			{
				it->pop_back();
				kv.key = TOKEN_D_VALUE;
				kv.value = *it;
				tokens.push_back(kv);
				kv.key = TOKEN_SEMICOLON;
				kv.value = ";";
				tokens.push_back(kv);	
			}
			else
			{
				kv.key = TOKEN_D_VALUE;
				kv.value = *it;
				tokens.push_back(kv);
			}
		}
		else
			throw Config::Error_config_file();
	}
}

Config::Config(std::ifstream &file)
{
	std::string	line;

	while (std::getline(file, line))
	{
		line = lstrtrim(line);
		line = rstrtrim(line);
		if (line.empty())
			continue;
		for (size_t i = 0; i < line.length(); i++)
		{
			if (line[i] == '\n' || line[i] == '\t')
				line[i] = ' ';
		}
		split_lines = utility::split(line, " ");
		for (std::vector<std::string>::const_iterator it = split_lines.begin(); it != split_lines.end(); ++it) {
            lines.push_back(*it);
        }
	}
	tokenize(lines);
}

const char*	Config::Error_config_file::what() const throw()
{
	return "Error in config file";
}