/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pollingServ.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 06:54:04 by fech-cha          #+#    #+#             */
/*   Updated: 2023/05/31 02:12:33 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/fech-cha/Desktop/webserv/inc/pollingServ.hpp"

polling::polling(void)
{
    
}

polling::~polling(void)
{
    
}

void    polling::pushSocket(int fd)
{
    this->_sockets.push_back(fd);
}

void    polling::pushFd(int sockfd, int event)
{
    struct pollfd tmp;

    tmp.fd = sockfd;
    tmp.events = event;
    tmp.revents = 0;
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


//check keep-alive section in page 79
//timing of the connection (heartbeat)
//message structure
//checking for client termination page 92
//using keeo-alives in setsockopt page 94
//Understand How to Time Out a connect Call page 183

int     polling::sendAll(int fd, char *buff, int *len)
{
    int check;
    
    check = send(fd, buff, BUFFER_SIZE, 0);
    return (check);
}


//from tcp/ip programming fig 2.27, also check page 53-54
int     polling::recvAll(int fd, char *buff, int len)
{
    int check;
    check = recv(fd, buff, BUFFER_SIZE, 0);
    return (len);
}

void    polling::handlePoll(char *resp)
{
    for (size_t i = 0; i < this->_pollfds.size(); i++)
    {
        pollfd& pfd = this->_pollfds[i];
        
        //check if someone ready to read/connect
        if (pfd.revents & POLLIN)
        {
            //handle new connections 
            //check if i < _socket.size()
            if (pfd.fd == this->_sockets[i])
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
                int count = polling::recvAll(pfd.fd, (char *)sock.getBuffer(), BUFFER_SIZE);
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
                    int tmpLen = strlen(resp);
                    //check the len of the resp is it the same
                    int test2 = polling::sendAll(pfd.fd, resp, &tmpLen);
                    if (test2 == -1)
                    {
                        perror("send");
                        std::cout << "We only sent: " << tmpLen << " because of the error!" << std::endl;
                    }
                    polling::closeConnections(pfd.fd);
                }
            }
        }
        //client hang up
        if (pfd.revents & POLLHUP)
            polling::closeConnections(pfd.fd);
    }
}