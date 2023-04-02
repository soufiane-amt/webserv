/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myServ.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 06:54:04 by fech-cha          #+#    #+#             */
/*   Updated: 2023/04/02 23:48:03 by fech-cha         ###   ########.fr       */
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

int polling::closeConnections(int fd)
{
    close(fd);
    for (unsigned int i = 0; i < getSize(); i++)
    {
        pollfd& tmp = this->_pollfds[i];
        if (tmp.fd == fd)
        {
            this->_pollfds.erase(this->_pollfds.begin() + i);       
            return (1);
        }
    }
    return (0);
}

void    polling::handlePoll(mySocket &sock, char *resp)
{
    for (unsigned int i = 0; i < this->_pollfds.size() ; i++)
    {
        pollfd& pfd = this->_pollfds[i];
        //check if someone ready to read/connect
        if (pfd.revents & POLLIN)
        {
            //handle new connections
            if (pfd.fd == sock.getSockFd())
            {
                sock.acceptConnection();
                if (sock.getAcceptFd() == -1)
                    perror ("accept");
                else
                {
                    this->pushFd(sock.getAcceptFd(), POLLIN);
                    sock.retrieveClientAdd(); // print the ip of the connection later
                    std::cout << "New server connection on socket : " << sock.getAcceptFd() << std::endl;
                }
            }
            else //just regular client
            {
                int count = recv(pfd.fd, (void *)sock.getBuffer(), BUFFER_SIZE, 0);
                //request need to go through the parser

                //error or connection closed 
                if (count <= 0)
                {
                    if (count == 0)
                    {
                        //connection closed
                        std::cout << "Server: socket  " << pfd.fd <<  " closed." << std::endl;
                    }
                    else
                        perror ("recv");
                    polling::closeConnections(pfd.fd);
                }
                else
                {
                    //got data from client
                    sock.printLogs();
                    //send a response/generate HTTP response
                    int test = send(pfd.fd, resp, strlen(resp), 0);
                    if (test == -1)
                    {
                        perror("send");
                    }
                    polling::closeConnections(pfd.fd);
                }
            }
        }
    }
}