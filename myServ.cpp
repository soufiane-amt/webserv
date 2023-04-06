/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myServ.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 06:54:04 by fech-cha          #+#    #+#             */
/*   Updated: 2023/04/06 02:31:42 by fech-cha         ###   ########.fr       */
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

int     polling::sendAll(int fd, char *buff, int *len)
{
    int total = 0; //checking how many bytes we've sent
    int rest = *len; //rest of the data
    int check;

    while (total < *len)
    {
        check = send(fd, buff + total, rest, 0);
        if (check == -1)
            break;
        total += check; //update the total of bytes sent
        rest -= check; //update how nuch bytes are left
    }
    *len = total; //actual number of bytes sent

    return (check == -1 ? -1 : 0); //-1 on failure, 0 on success
}


//from tcp/ip programming fig 2.27, also check page 53-54
int     polling::recvAll(int fd, char *buff, int len)
{
    // std::string store;
    int cnt = 0;
    int rc = 0;

    cnt = len;
    while (cnt > 0)
    {
        rc = recv(fd, buff, cnt, 0);
        if (rc == -1)
            break;
        if (rc == 0)
            return (len - cnt);
        buff += rc;
        cnt -= rc;
    }
    return (len);

    //BUFFER_SIZE should be set the in the object and it should be the size of the message sent
    // while (recd < BUFFER_SIZE)
    // {
        // int rest = 
    // }
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
    }
}