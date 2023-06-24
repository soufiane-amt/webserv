/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:35:13 by sismaili          #+#    #+#             */
/*   Updated: 2023/06/24 09:47:00 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

#include "utils.hpp"

/* ************************************************************************** */
                            // Typedefs :
/* ************************************************************************** */


typedef enum e_type
{
	TOKEN_SERVER,
	TOKEN_LOCATIOIN,
	TOKEN_DIRECTIVE,
	TOKEN_D_VALUE,
	TOKEN_D_VALUE2,
	TOKEN_L_VALUE,
	TOKEN_O_BRACE,
	TOKEN_C_BRACE,
	TOKEN_SEMICOLON,
	TOKEN_COMMENTS,
	TOKEN_NL,
}	t_type;

struct	key_val
{
	int	key;
	std::string	value;
};

class	Config
{
	private:
		server_t servers;
		std::vector<std::pair<std::string, std::string> > host;
		std::vector<std::string> ports_number;
	public:
		typedef	std::vector<std::string>::iterator vector_it;
		typedef	std::vector<key_val>::iterator key_val_it;
		class Error_config_file : public std::exception
		{
			virtual const char *what() const throw()
			{
				  return "Error in configuration file";
			};
		};
		Config(){};
		Config(std::ifstream &file);
		Config& operator= (const Config& copy);
		void	server_print();
		std::string	lstrtrim(std::string	&str);
		std::string	rstrtrim(std::string	&str);
		void	tokenize(std::vector<std::string> &lines, std::vector<key_val> &tokens);
		void	server_check(std::vector<key_val> &tokens);
		void	directive_check(key_val_it &t_it, location_t &locations, directive_t &directives, key_val_it &it, int *i);
		void	d_value_check(directive_t &directives, key_val_it &it, int i);
		void	location_check(key_val_it &it);
		std::string get_server_directives (int server_id, std::string directive);
		void	brace_counter(std::vector<key_val> &tokens);
		void	fill_locations(key_val_it &t_it, location_t &locations, key_val_it &it);
		location_t	get_server_locations(int server_id);
		std::vector<std::pair<std::string, std::string> > &get_host();
		void	fill_servers(directive_t &directives, location_t &locations);
		void	server_host(server_t &servers);
		std::vector<std::string> &get_ports_number();
};

#endif