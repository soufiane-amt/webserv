/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:48:32 by sismaili          #+#    #+#             */
/*   Updated: 2023/06/24 09:52:38 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"
#include "utils.hpp"

Config& Config::operator= (const Config& copy)
{
	this->servers = copy.servers;
	this->host = copy.host;
	this->ports_number = copy.ports_number;
	return *this;
}

location_t	Config::get_server_locations(int server_id)
{
	return (servers[server_id].second);
}

std::string Config::get_server_directives (int server_id, std::string directive)
{
    return (servers[server_id].first.at(directive));
}

std::vector<std::pair<std::string, std::string> > &Config::get_host()
{
	return (this->host);
}

std::vector<std::string>	&Config::get_ports_number() 
{
	return (ports_number);
}

void	Config::server_host(server_t &servers)
{
	for (server_t::iterator it = servers.begin(); it != servers.end(); ++it)
	{
		directive_t& dir = it->first;
		std::vector<std::string> ports;
		for (directive_t::iterator ite = dir.begin(); ite != dir.end(); ite++)
		{
			if (ite->first == "listen")
			{
				ports_number.push_back(ite->second);
				ports = utility::split(ite->second, " ");
			}
			else if (ite->first == "server_name")
			{
				if (ports.size() > 0)
				{
					for (std::vector<std::string>::iterator iter = ports.begin(); iter != ports.end(); iter++)
						host.push_back(std::pair<std::string, std::string>(*iter, ite->second));
				}
			}
		}
		ports.clear();
	}
	
}

void	Config::server_print()
{
	for (server_t::iterator it = servers.begin(); it != servers.end(); ++it)
	{
        directive_t& directives = it->first;
        location_t& locations = it->second;

        std::cout << "Directive_t content:" << std::endl;
        for (directive_t::iterator dir_it = directives.begin(); dir_it != directives.end(); ++dir_it) {
            std::cout << "Key: " << dir_it->first << " || Value: " << dir_it->second << std::endl;
        }

        std::cout << "Location_t content:" << std::endl;
        for (location_t::iterator loc_it = locations.begin(); loc_it != locations.end(); ++loc_it) {
            std::cout << "Key: " << loc_it->first << std::endl;
            directive_t& temp_dir = loc_it->second;
            for (directive_t::iterator dir_it = temp_dir.begin(); dir_it != temp_dir.end(); ++dir_it) {
                std::cout << "    Key: " << dir_it->first << " || Value: " << dir_it->second << std::endl;
            }
        }
    }
}


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
		else if (*it == ";")
		{
			kv.key = TOKEN_SEMICOLON;
			kv.value = *it;
			tokens.push_back(kv);
		}
		else if (it->at(0) == '#')
		{
			while (*it != "\n")
			{
				kv.key = TOKEN_COMMENTS;
				kv.value = *it;
				tokens.push_back(kv);
				it++;
			}
			kv.key = TOKEN_NL;
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
			|| *it == "index" || *it == "upload" || *it == "path_info" || *it == "cgi")
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
				if (it->back() == ';')
					throw Config::Error_config_file();
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

void Config::d_value_check(directive_t &directives, key_val_it &it, int i)
{
	if ((it - 1)->value == "listen")
	{
		if (directives.find("listen") != directives.end() && i == 1)
			throw Config::Error_config_file();
		std::vector<std::string> unique_values;
		int	number = 0;
		while (it->key != TOKEN_SEMICOLON)
		{
			std::istringstream iss(it->value);
			if (!(iss >> number))
				throw Config::Error_config_file();
			if (std::find(unique_values.begin(), unique_values.end(), it->value) == unique_values.end()
				&& number >= 0 && number <= 65535)
			{
				unique_values.push_back(it->value);
				if (i == 1)
				{
					directives["listen"] += it->value + " ";
				}
				else
					throw Config::Error_config_file();
			}
			else
				throw Config::Error_config_file();
			it++;
		}
	}
	else if ((it - 1)->value == "max_body_size")
	{
		int	number = 0;
		std::istringstream iss(it->value);
		if (!(iss >> number))
			throw Config::Error_config_file();
		else if (number < 0 || (it + 1)->key != TOKEN_SEMICOLON)
			throw Config::Error_config_file();
		if (directives.find((it - 1)->value) != directives.end() && i == 1)
			throw Config::Error_config_file();
		else if (i == 1)
			directives[(it - 1)->value] = it->value;
	}
	else if ((it - 1)->value == "autoindex")
	{
		if ((it->value != "on" && it->value != "off") || (it + 1)->key != TOKEN_SEMICOLON)
			throw Config::Error_config_file();
		if (directives.find((it - 1)->value) != directives.end() && i == 1)
			throw Config::Error_config_file();
		else if (i == 1)
			directives[(it - 1)->value] = it->value;
	}
	else if ((it - 1)->value == "root" || (it - 1)->value == "upload" || (it - 1)->value == "cgi")
	{
		if ((it - 1)->value == "cgi" && i != 1)
			throw Config::Error_config_file();
		if ((it - 1)->value == "upload")
		{
			if (it->value.back() != '/')
				it->value += '/';
		}
		if ((it + 1)->key != TOKEN_SEMICOLON)
			throw Config::Error_config_file();
		if (it->value.back() == '/' && it->value.size() > 1 && (it - 1)->value != "upload")
			it->value.pop_back();
		if (directives.find((it - 1)->value) != directives.end() && i == 1)
			throw Config::Error_config_file();
		else if (i == 1)
			directives[(it - 1)->value] = it->value;
	}
	else if ((it - 1)->value == "index" || (it - 1)->value == "server_name")
	{
		if (it->value.at(0) == '/' || (it + 1)->key != TOKEN_SEMICOLON)
			throw Config::Error_config_file();
		if (directives.find((it - 1)->value) != directives.end() && i == 1)
			throw Config::Error_config_file();
		else if (i == 1)
			directives[(it - 1)->value] = it->value;
		else if (i == 2 && (it - 1)->value == "server_name")
			throw Config::Error_config_file();
	}
	else if ((it - 1)->value == "return")
	{
		if (it->key != TOKEN_D_VALUE2 || (it + 1)->key != TOKEN_D_VALUE
			|| (it + 2)->key != TOKEN_SEMICOLON)
			throw Config::Error_config_file();
		int	number = 0;
		std::istringstream iss(it->value);
		if (!(iss >> number))
			throw Config::Error_config_file();
		else if (number < 100 || number > 599)
			throw Config::Error_config_file();
		if (directives.find((it - 1)->value) != directives.end() && i == 1)
			throw Config::Error_config_file();
		else if (i == 1)
			directives[(it - 1)->value] = it->value + " " + (it + 1)->value;
	}
	else if ((it - 1)->value == "path_info")
	{
		if (it->key != TOKEN_D_VALUE2 || (it + 1)->key != TOKEN_D_VALUE
			|| (it + 2)->key != TOKEN_SEMICOLON || i == 1)
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
				{
					unique_values.push_back(it->value);
					if (i == 1 && directives["allow"].size() < 16)
						directives["allow"] += it->value + " ";
					else if (i != 2)
						throw Config::Error_config_file();
				}
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

void Config::fill_locations(key_val_it &t_it, location_t &locations, key_val_it &it)
{
	std::string	temp;
	size_t	i = 0;

	t_it++;
	for (; t_it->key != TOKEN_SERVER && t_it != it; t_it++)
	{
		if (t_it->key == TOKEN_L_VALUE)
		{
			if (locations.find(t_it->value) != locations.end())
				throw Config::Error_config_file();
			temp = t_it->value;
			i = temp.length();
			for (size_t l = temp.length(); l > 1 && temp.back() == '/'; l--)
			{
 				if (l + 2 == i || l - 1 == 1)
					throw Config::Error_config_file();
				temp.pop_back();
			}
			t_it++;
			i = 0;
			while (t_it->key != TOKEN_C_BRACE)
			{
				if (t_it->key == TOKEN_DIRECTIVE)
				{
					i = 1;
					if (locations[temp].find(t_it->value) != locations[temp].end() && t_it->value != "path_info")
						throw Config::Error_config_file();
					if ((t_it + 2)->key == TOKEN_SEMICOLON)
						locations[temp][t_it->value] = (t_it + 1)->value;
					else if ((t_it + 3)->key == TOKEN_SEMICOLON && t_it->value == "path_info")
						locations[temp][t_it->value] += (t_it + 1)->value + " " + (t_it + 2)->value + " ";
					else if ((t_it + 3)->key == TOKEN_SEMICOLON)
						locations[temp][t_it->value] = (t_it + 1)->value + " " + (t_it + 2)->value;
					else if ((t_it + 4)->key == TOKEN_SEMICOLON)
						locations[temp][t_it->value] = (t_it + 1)->value + " " + (t_it + 2)->value + " " + (t_it + 3)->value;
				}
				t_it++;
			}
			if (i == 0)
				throw Config::Error_config_file();
			i = 0;
		}
	}
}

void Config::fill_servers(directive_t &directives, location_t &locations)
{
	bool	already_exists = false;

	for (server_t::iterator it = servers.begin(); it != servers.end(); ++it)
	{
		if (it->first["server_name"] == directives["server_name"]
			&& it->first["listen"] == directives["listen"])
			already_exists = true;
	}
	if (!already_exists)
		servers.push_back(std::pair<directive_t, location_t>(directives, locations));
}

void Config::directive_check(key_val_it &t_it, location_t &locations, directive_t &directives, key_val_it &it, int *i)
{
	if (it->key == TOKEN_DIRECTIVE)
	{
		if ((it - 1)->key != TOKEN_NL)
			throw Config::Error_config_file();
		else if ((it + 1)->key != TOKEN_D_VALUE && (it + 1)->key != TOKEN_D_VALUE2)
			throw Config::Error_config_file();
	}
	else if (it->key == TOKEN_D_VALUE || it->key == TOKEN_D_VALUE2)
		d_value_check(directives, it, *i);
	else if (it->key == TOKEN_SEMICOLON)
	{
		if ((it + 1)->key != TOKEN_NL)
			throw Config::Error_config_file();
	}
	else if (it->key == TOKEN_C_BRACE)
	{
		if ((it + 1)->key != TOKEN_NL && (it + 1)->key != TOKEN_COMMENTS)
			throw Config::Error_config_file();
		(*i)--;
		if (*i == 0)
		{
			if (directives.find("listen") == directives.end() || directives.find("server_name") == directives.end())
				throw Config::Error_config_file();
			fill_locations(t_it, locations, it);
			if (directives.size() == 0 && locations.size() == 0)
				throw Config::Error_config_file();
			fill_servers(directives, locations);
			directives.clear();
			locations.clear();
		}
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

void Config::server_check(std::vector<key_val> &tokens)
{
	directive_t directives;
	location_t locations;
	key_val_it t_it;
	int	i = 0;

	for (key_val_it it = tokens.begin(); it != tokens.end(); it++)
	{
		if (it->key == TOKEN_COMMENTS || (i == 0 && it->key == TOKEN_NL))
			continue;
		else if (i == 0 && it->key == TOKEN_SERVER)
		{
			t_it = it;
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
				directive_check(t_it, locations, directives, it, &i);
			else if (i == 1 && it->key != TOKEN_LOCATIOIN)
				directive_check(t_it, locations, directives, it, &i);
			else
				throw Config::Error_config_file();
		}
		else
			throw Config::Error_config_file();
	}
	brace_counter(tokens);
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
	server_host(servers);
}
