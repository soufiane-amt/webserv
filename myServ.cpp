/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myServ.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 06:54:04 by fech-cha          #+#    #+#             */
/*   Updated: 2023/03/31 08:55:41 by fech-cha         ###   ########.fr       */
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
    if (this->_pollfds[0].revents & POLLIN)
    {
        //accept connections
        sock.acceptConnection();
        if (sock.getAcceptFd() < 0)
        {
            perror("Webserv (accept)");
            //case of exit or not 
        }
        else
        {
            //set the new sockfd to be non-blocking
            fcntl(sock.getAcceptFd(), F_SETFL, O_NONBLOCK);
            
            //push the new fd to pollfd vector
            polling::pushFd(sock.getAcceptFd(), POLLIN);
            std::cout << "Connection accepted!" << std::endl;
        }
    }
}