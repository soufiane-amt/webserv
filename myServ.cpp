/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myServ.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 06:54:04 by fech-cha          #+#    #+#             */
/*   Updated: 2023/03/31 23:11:46 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myServ.hpp"

polling::polling(void)
{
    
}

polling::~polling(void)
{
    
}

void    polling::pushFd(int sockfd, int event)
{
    struct pollfd tmp;

    tmp.fd = sockfd;
    tmp.events = event;
    this->_pollfds.push_back(tmp);
}

int polling::callPoll(struct pollfd *fds, nfds_t nfds, int timeout)
{
    return (poll(fds, nfds, timeout));
}

const struct pollfd    *polling::getPollfdAddrs(void) const
{
    return (&_pollfds[0]);
}

nfds_t  polling::getSize(void) const
{
    return (this->_pollfds.size());
}

void    polling::handlePoll(mySocket &sock)
{   
    //check if there a request on the sockfd
    if (this->_pollfds[0].revents & POLLIN)
    {
        //accept connections
        sock.acceptConnection();
        if (sock.getAcceptFd() < 0)
        {
            perror("Webserv (accept)");
            //case of exit or not /continue in the loop
        }
        else
        {
            //set the new sockfd to be non-blocking
            fcntl(sock.getAcceptFd(), F_SETFL, O_NONBLOCK);
            
            //push the new fd to pollfd vector
            polling::pushFd(sock.getAcceptFd(), POLLIN);
            std::cout << "Connection accepted!" << std::endl;
        }
        //get client address (that's the idea)
        sock.retrieveClientAdd();
        if (sock.getSockName() < 0)
        {
            perror("Webserv (getsockname)");
            //exit or continue in this loop
        }
    }

    //start from 1, skip listening socket
    for (unsigned int i = 1; i < getSize() ; i++)
    {
        std::cout << "HERE" << std::endl;
        //check which FD triggered the event
        if (this->_pollfds[i].events & POLLIN)
        {
            //recv from the client 
            int num = recv(this->_pollfds[i].fd, (void *)sock.getBuffer(), BUFFER_SIZE, 0);
            std::cout << "i read" << std::endl;
            (void)num;
        }   
    }
}