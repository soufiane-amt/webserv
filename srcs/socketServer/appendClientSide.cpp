/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appendClientSide.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:05:34 by fech-cha          #+#    #+#             */
/*   Updated: 2023/05/31 03:37:38 by fech-cha         ###   ########.fr       */
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

void    appendClient::sendReq(int sockfd, const void *buf, int len, int flags)
{
    this->sendRes = send(sockfd, buf, len, flags);
    //close sockfd of the connection
    close(sockfd);
    appendClient::testSysCall(this->sendRes);
}

void    appendClient::recvReq(int sockfd, void *buf, int len, int flags)
{
    this->recvRes = recv(sockfd, buf, len, flags);
    appendClient::testSysCall(this->recvRes);
}
