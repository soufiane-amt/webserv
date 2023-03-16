/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:44:52 by samajat           #+#    #+#             */
/*   Updated: 2023/03/16 17:49:39 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <vector>
#include <iostream>

struct utility
{
    static std::vector<std::string> split(std::string str, std::string delimiter);
};

