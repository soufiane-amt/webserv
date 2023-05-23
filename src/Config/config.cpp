/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:48:32 by sismaili          #+#    #+#             */
/*   Updated: 2023/05/23 17:40:03 by sismaili         ###   ########.fr       */
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

void	Config::tokenize(std::vector<std::string> &lines, std::vector<key_val> &tokens)
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
			else
				throw Config::Error_config_file();
		}
		else if (*it == "listen" || *it == "server_name" || *it == "max_body_size"
			|| *it == "return" || *it == "root" || *it == "autoindex" || *it == "allow"
			|| *it == "index" || *it == "upload" || *it == "max_body_size")
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
		else if (*it == "\n")
		{
			kv.key = TOKEN_NL;
			kv.value = *it;
			tokens.push_back(kv);
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
	else if ((it - 1)->value == "max_body_size")
	{
		int	number = 0;
		std::istringstream iss(it->value);
		if (!(iss >> number))
			throw Config::Error_config_file();
		else if (number < 0 || (it + 1)->key != TOKEN_SEMICOLON)
			throw Config::Error_config_file();
	}
	else if ((it - 1)->value == "autoindex")
	{
		if ((it->value != "on" && it->value != "off") || (it + 1)->key != TOKEN_SEMICOLON)
			throw Config::Error_config_file();
	}
	else if ((it - 1)->value == "root")
	{
		if (it->value.at(0) != '/' || (it + 1)->key != TOKEN_SEMICOLON)
			throw Config::Error_config_file();
	}
	else if ((it - 1)->value == "index" || (it - 1)->value == "server_name")
	{
		if (it->value.at(0) == '/' || (it + 1)->key != TOKEN_SEMICOLON)
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
		if ((it - 1)->key != TOKEN_NL)
				throw Config::Error_config_file();
		else if ((it + 1)->key != TOKEN_D_VALUE && (it + 1)->key != TOKEN_D_VALUE2)
				throw Config::Error_config_file();
	}
	else if (it->key == TOKEN_D_VALUE || it->key == TOKEN_D_VALUE2)
		d_value_check(it);
	else if (it->key == TOKEN_SEMICOLON)
	{
		if ((it + 1)->key != TOKEN_NL)
			throw Config::Error_config_file();
	}
	else if (it->key == TOKEN_C_BRACE)
	{
		if ((it + 1)->key != TOKEN_NL)
			throw Config::Error_config_file();
		(*i)--;
	}
	else if (it->key == TOKEN_O_BRACE && ((it - 1)->key != TOKEN_L_VALUE
		&& (it - 1)->key != TOKEN_SERVER) && (it + 1)->key != TOKEN_NL)
		throw Config::Error_config_file();
}

void Config::location_check(key_val_it &it)
{
	if ((it - 1)->key != TOKEN_NL)
			throw Config::Error_config_file();
	else if ((it + 1)->key != TOKEN_L_VALUE || (it + 2)->key != TOKEN_O_BRACE)
			throw Config::Error_config_file();
}

void Config::brace_counter(std::vector<key_val> &tokens)
{
	int	count = 0;

	for (key_val_it it = tokens.begin(); it != tokens.end(); it++)
	{
		if (it->key == TOKEN_O_BRACE)
			count++;
		else if (it->key == TOKEN_C_BRACE)
			count--;
	}	
	if (count != 0)
		throw Config::Error_config_file();
}

void Config::fill_containers(std::vector<key_val> &tokens)
{
	for (key_val_it it = tokens.begin(); it != tokens.end(); it++)
	{
		if (it->key == TOKEN_DIRECTIVE)
		{
			directives.insert(std::make_pair(it->value, (it + 1)->value));
			if ((it + 2)->key == TOKEN_D_VALUE || (it + 2)->key == TOKEN_D_VALUE2)
				directives[it->value] += ", " + (it + 2)->value;
			if ((it + 3)->key == TOKEN_D_VALUE || (it + 3)->key == TOKEN_D_VALUE2)
				directives[it->value] += ", " + (it + 3)->value;
		}
		else if (it->key == TOKEN_LOCATIOIN)
			locations.insert(std::make_pair(it->value, directives));
		else if (it->key == TOKEN_SERVER)
			servers.push_back(std::pair<directive_t, location_t>(directives, locations));
	}
}

void Config::server_check(std::vector<key_val> &tokens)
{
	int	i = 0;

	for (key_val_it it = tokens.begin(); it != tokens.end(); it++)
	{
		if (it->key == TOKEN_COMMENTS || (i == 0 && it->key == TOKEN_NL))
			continue;
		else if (i == 0 && it->key == TOKEN_SERVER)
		{
			i++;
			if ((it + 1)->key != TOKEN_O_BRACE || ((it + 2)->key != TOKEN_COMMENTS && (it + 2)->key != TOKEN_NL))
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
	brace_counter(tokens);
	// fill_containers(tokens);
}

Config::Config(std::ifstream &file)
{
	std::string	line;
	std::vector<std::string> split_lines;
	std::vector<std::string> lines;
	std::vector<key_val> tokens;

	while (std::getline(file, line))
	{
		line = lstrtrim(line);
		line = rstrtrim(line);
		if (line.empty())
			continue;
		line += '\n';
		for (size_t i = 0; i < line.length() + 1; i++)
		{
			if (line[i] == '\t')
				line[i] = ' ';
		}
		split_lines = utility::split(line, " ");
		for (vector_it it = split_lines.begin(); it != split_lines.end(); ++it)
			utility::split2(*it, "\n", lines);
	}
	tokenize(lines, tokens);
	server_check(tokens);
}

const char*	Config::Error_config_file::what() const throw()
{
	return "Error in config file";
}