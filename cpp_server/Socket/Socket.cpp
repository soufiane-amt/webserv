/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:43:07 by fech-cha          #+#    #+#             */
/*   Updated: 2023/03/27 07:21:04 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

mySocket::mySocket(int domain, int serviceType, int protocol, int port, u_long interface)
{
    //define address structure
    address.sin_family = domain;
    address.sin_port = htons(port); //byte order
    address.sin_addr.s_addr = htonl(interface);
    //create socket
    this->sockfd = socket(domain, serviceType, protocol);
    testSysCall(this->sockfd);
    //bind (though it should be outside the constructor)
    this->connection = bind(getSockFd(), (struct sockaddr *)&(getAddress()), sizeof(getAddress()));
    testSysCall(this->connection);
}


void    mySocket::testSysCall(int fd)
{
    if (fd < 0)
    {
        perror("Network Failure.");
        exit(EXIT_FAILURE);
    }
}

struct sockaddr_in mySocket::getAddress()  const
{
    return (this->address);
}

int mySocket::getSockFd() const
{
    return (this->sockfd);    
}

int mySocket::getBindValue() const
{
    return (this->connection);
}
