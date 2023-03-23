/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:35:13 by sismaili          #+#    #+#             */
/*   Updated: 2023/03/23 17:55:57 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

#include "../Utility/utils.hpp"

typedef std::map<std::string, std::string> directive_t;
typedef std::map<std::string, directive_t> location_t;
typedef std::vector<std::pair<directive_t, location_t> > server_t;

class	Config
{
	private:
		std::map<std::string, std::string> map_config;
		std::string	key;
		std::string value;
		std::vector<std::string> lines;
		std::string	line;
		std::string::size_type pos;
	public:
		Config(std::ifstream &file);
		void	checker();
		const	std::string	get_key(const std::string &key) const;
};

#endif