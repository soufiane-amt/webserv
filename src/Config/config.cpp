/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:48:32 by sismaili          #+#    #+#             */
/*   Updated: 2023/05/22 17:54:13 by sismaili         ###   ########.fr       */
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
		else if (it->at(0) == '#')
		{
			kv.key = TOKEN_COMMENTS;
			kv.value = *it;
			tokens.push_back(kv);
		}
		else if (it->at(0) == '/' && it->back() != ';')
		{
			if (tokens.size() > 0 && tokens.back().key == TOKEN_LOCATIOIN)
			{
				kv.key = TOKEN_L_VALUE;
				kv.value = *it;
				tokens.push_back(kv);
			}
		}
		else if (*it == "listen" || *it == "server_name" || *it == "max_body_size"
			|| *it == "return" || *it == "root" || *it == "autoindex" || *it == "allow"
			|| *it == "index" || *it == "upload")
		{
			kv.key = TOKEN_DIRECTIVE;
			kv.value = *it;
			tokens.push_back(kv);
		}
		else if (it->back() == ';' || (tokens.size() > 0 && (tokens.back().key == TOKEN_DIRECTIVE || tokens.back().key == TOKEN_D_VALUE2)))
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
				kv.key = TOKEN_D_VALUE2;
				kv.value = *it;
				tokens.push_back(kv);
			}
		}
		else
			throw Config::Error_config_file();
	}
}

void Config::d_value_check(key_val_it &it)
{
	if ((it - 1)->value == "listen")
	{
		int	number = 0;
		std::istringstream iss(it->value);
		if (!(iss >> number))
			throw Config::Error_config_file();
		else if (number < 0 || number > 65535 || (it + 1)->key != TOKEN_SEMICOLON)
			throw Config::Error_config_file();
	}
	else if ((it - 1)->value == "autoindex")
	{
		if ((it->value != "on" && it->value != "off") || (it + 1)->key != TOKEN_SEMICOLON)
			throw Config::Error_config_file();
	}
	else if ((it - 1)->value == "return")
	{
		if (it->key != TOKEN_D_VALUE2 && (it + 1)->key != TOKEN_D_VALUE
			&& (it + 2)->key != TOKEN_SEMICOLON)
			throw Config::Error_config_file();
	}
	else if ((it - 1)->value == "allow")
	{
		std::vector<std::string> unique_values;
		while (it->key != TOKEN_SEMICOLON)
		{
			if (it->value == "POST" || it->value == "GET" || it->value == "DELETE")
			{
				if (std::find(unique_values.begin(), unique_values.end(), it->value) == unique_values.end())
					unique_values.push_back(it->value);
				else
					throw Config::Error_config_file();
			}
			else
				throw Config::Error_config_file();
			it++;
		}
		if (unique_values.size() < 1 || unique_values.size() > 3)
				throw Config::Error_config_file();
	}
}

void Config::directive_check(key_val_it &it, int *i)
{
	if (it->key == TOKEN_DIRECTIVE)
	{
		if ((it - 1)->key != TOKEN_SEMICOLON && (it - 1)->key != TOKEN_O_BRACE
			&& (it - 1)->key != TOKEN_C_BRACE && (it - 1)->key != TOKEN_COMMENTS)
				throw Config::Error_config_file();
		else if ((it + 1)->key != TOKEN_D_VALUE && (it + 1)->key != TOKEN_D_VALUE2)
				throw Config::Error_config_file();
	}
	else if (it->key == TOKEN_D_VALUE || it->key == TOKEN_D_VALUE2)
		d_value_check(it);
	else if (it->key == TOKEN_SEMICOLON)
	{
		if ((it + 1)->key == TOKEN_SEMICOLON)
			throw Config::Error_config_file();
	}
	else if (it->key == TOKEN_C_BRACE)
		(*i)--;
}

void Config::location_check(key_val_it &it)
{
	if ((it - 1)->key != TOKEN_SEMICOLON && (it - 1)->key != TOKEN_O_BRACE
		&& (it - 1)->key != TOKEN_C_BRACE && (it - 1)->key != TOKEN_COMMENTS)
			throw Config::Error_config_file();
	else if ((it + 1)->key != TOKEN_L_VALUE || (it + 2)->key != TOKEN_O_BRACE)
			throw Config::Error_config_file();
}

void Config::server_check(std::vector<key_val> &tokens)
{
	int	i = 0;

	for (key_val_it it = tokens.begin(); it != tokens.end(); it++)
	{
		if (it->key == TOKEN_COMMENTS)
			continue;
		else if (i == 0 && it->key == TOKEN_SERVER)
		{
			i++;
			if ((it + 1)->key != TOKEN_O_BRACE)
				throw Config::Error_config_file();
		}
		else if (i != 0 && it->key != TOKEN_SERVER)
		{
			if (i == 1 && it->key == TOKEN_LOCATIOIN)
			{
				location_check(it);
				i++;
			}
			else if (i == 2 && it->key != TOKEN_LOCATIOIN)
				directive_check(it, &i);
			else if (i == 1 && it->key != TOKEN_LOCATIOIN)
				directive_check(it, &i);
			else
				throw Config::Error_config_file();
		}
		else
			throw Config::Error_config_file();
	}
	if (i != 0)
		throw Config::Error_config_file();
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
	server_check(tokens);
}

const char*	Config::Error_config_file::what() const throw()
{
	return "Error in config file";
}