/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myServ.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 06:54:04 by fech-cha          #+#    #+#             */
/*   Updated: 2023/04/01 03:14:56 by fech-cha         ###   ########.fr       */
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

// void    polling::handlePoll(mySocket &sock, char *resp)
// {   
//     //check if there a request on the sockfd
//     if (this->_pollfds[0].revents & POLLIN)
//     {
//         //accept connections
//         sock.acceptConnection();
//         if (sock.getAcceptFd() < 0)
//         {
//             perror("Webserv (accept)");
//             //case of exit or not /continue in the loop
//         }
//         else
//         {
//             //set the new sockfd to be non-blocking
//             fcntl(sock.getAcceptFd(), F_SETFL, O_NONBLOCK);
            
//             //push the new fd to pollfd vector
//             polling::pushFd(sock.getAcceptFd(), POLLIN);
//             std::cout << "Connection accepted!" << std::endl;
//         }
//         //get client address (that's the idea)
//         sock.retrieveClientAdd();
//         if (sock.getSockName() < 0)
//         {
//             perror("Webserv (getsockname)");
//             //exit or continue in this loop
//         }
//     }

//     //start from 1, skip listening socket
//     for (unsigned int i = 1; i < getSize() ; i++)
//     {
//         std::cout << "HERE" << std::endl;
//         //check which FD triggered the event
//         if (this->_pollfds[i].events & POLLIN)
//         {
//             //recv from the client 
//             int num = recv(this->_pollfds[i].fd, (void *)sock.getBuffer(), BUFFER_SIZE, MSG_DONTWAIT);
//             std::cout << "i read" << std::endl;
//             (void)num;
//         }   
//     }
    
//     //print logs of the request
//     sock.printLogs();

//     // this msg from the browser is then sent to the parser for HTTP Message Parsing

//     // generate message in http rules from the webserv to the browser
//     sock.sendReq(sock.getAcceptFd(), resp, strlen(resp), 0);
    
// }

void    polling::handlePoll(mySocket &sock, char *resp)
{
    for (unsigned int i = 0; i < this->_pollfds.size() ; i++)
    {
        pollfd& pfd = this->_pollfds[i];
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
                    std::cout << "New server connection from : " << pfd.fd << std::endl;
                }
            }
            else //just regular client
            {
                int count = recv(pfd.fd, (void *)sock.getBuffer(), BUFFER_SIZE, 0);

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
                    close(pfd.fd);
                    for (unsigned int i = 0; i < getSize(); i++)
                    {
                        pollfd& tmp = this->_pollfds[i];
                        if (tmp.fd == pfd.fd)
                            this->_pollfds.erase(this->_pollfds[i]);
                            
                    }
                }
                
            }
        }
    }
}