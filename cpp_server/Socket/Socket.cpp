/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:43:07 by fech-cha          #+#    #+#             */
/*   Updated: 2023/03/28 01:46:55 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

mySocket::mySocket()
{
    //define address structure
    memset(&this->hints, 0, sizeof(this->hints)); //empty the struct
    this->hints.ai_family = AF_UNSPEC; //IPv4 or IPv6
    this->hints.ai_socktype = SOCK_STREAM; //TCP sockets
    this->hints.ai_flags = AI_PASSIVE; // indicates that the address is intended for a listening socket

    if (int val = getaddrinfo(NULL, "80", &this->hints, &this->servinfo))
    {
        std::string err = gai_strerror(val);
        std::cout << "getaddrinfo error: " << err << std::endl;
        exit(EXIT_FAILURE);
    }
    //create socket
    this->sockfd = socket(this->servinfo->ai_family, this->servinfo->ai_socktype, this->servinfo->ai_protocol);
    testSysCall(this->sockfd);
    
    //bind (though it should be outside the constructor)
    this->bindRes = bind(getSockFd(), (struct sockaddr *)&(getAddress()), sizeof(getAddress()));
    testSysCall(this->bindRes);
}

mySocket::~mySocket()
{
    freeaddrinfo(this->servinfo);
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
    return (this->bindRes);
}
