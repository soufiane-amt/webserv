/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appendClientSide.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:05:34 by fech-cha          #+#    #+#             */
/*   Updated: 2023/05/31 02:52:53 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "/Users/fech-cha/Desktop/webserv/inc/pollingServ.hpp"


appendClient::appendClient()
{
    
}

appendClient::~appendClient()
{
    
}

void    appendClient::setClientFd(int fd)
{
    this->_clientFd = fd;
}

int appendClient::getClientFd(void)
{
    return (this->_clientFd);
}