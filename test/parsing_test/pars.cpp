/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:21:57 by samajat           #+#    #+#             */
/*   Updated: 2023/03/15 12:53:48 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <vector>
#include <map>
#include <set>

typedef std::map<std::string, std::string> directive_t;
typedef std::map<std::string, directive_t> location_t;
typedef std::map<std::string, std::pair<directive_t, location_t>> server_t;

struct simpleConfPars
{
    void    get_configs ()
    {
        server_t server;
        directive_t directives;
        location_t locations;
        
        directives["listen"] = "80";
        directives["server_name"] = "example.com";
        locations["/"]["root"] = "/var/www/html";
        locations["/"]["index"] = "index.html";
        locations["/images/"]["root"] = "/var/www";
        locations["/images/"]["index"] = "index.html";
        directives["error_page"] = "404 /404.html";
        locations["/404.html"]["root"] = "/var/www/html";
        server[""] = std::make_pair(directives, locations);
    }
};
