/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:35:13 by sismaili          #+#    #+#             */
/*   Updated: 2023/05/11 18:25:57 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

#include "utils.hpp"

typedef std::map<std::string, std::string> directive_t;
typedef std::map<std::string, directive_t> location_t;
typedef std::vector<std::pair<directive_t, location_t> > server_t;

class	Config
{
	private:
		std::string	key;
		std::string value;
		std::vector<std::string> lines;
		directive_t directives;
		location_t locations;
		server_t servers;
	public:
		typedef	std::vector<std::string>::iterator vector_it;
		Config(std::ifstream &file);
		std::string	lstrtrim(std::string	&str);
		std::string	rstrtrim(std::string	&str);
		void	check_server(std::vector<std::string> &lines);
		void	server_block(vector_it &it);
};

#endif