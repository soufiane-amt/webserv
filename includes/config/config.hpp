/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:35:13 by sismaili          #+#    #+#             */
/*   Updated: 2023/05/23 17:25:38 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

#include "utils.hpp"

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
		directive_t directives;
		location_t locations;
		server_t servers;
	public:
		typedef	std::vector<std::string>::iterator vector_it;
		typedef	std::vector<key_val>::iterator key_val_it;
		class Error_config_file : public std::exception
		{
			virtual const char *what() const throw();
		};
		Config(std::ifstream &file);
		std::string	lstrtrim(std::string	&str);
		std::string	rstrtrim(std::string	&str);
		void	tokenize(std::vector<std::string> &lines, std::vector<key_val> &tokens);
		void	server_check(std::vector<key_val> &tokens);
		void	directive_check(key_val_it &it, int *i);
		void	d_value_check(key_val_it &it);
		void	location_check(key_val_it &it);
		void	brace_counter(std::vector<key_val> &tokens);
		void	fill_containers(std::vector<key_val> &tokens);
};

#endif