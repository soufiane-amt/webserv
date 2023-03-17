/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:49:48 by samajat           #+#    #+#             */
/*   Updated: 2023/03/17 18:51:28 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORMANAGER_HPP
# define ERRORMANAGER_HPP
#include <iostream>
#include <string>

class errorManager
{
    private:
    static const std::string    _validMethods[3];
    static const std::string    _validProtocol;

    public:
    errorManager();
};

#endif