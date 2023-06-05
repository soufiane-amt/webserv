/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pollingServ.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 06:54:04 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/05 06:13:39 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/fech-cha/Desktop/webserv/inc/pollingServ.hpp"

polling::polling(void)
{
    
}

polling::~polling(void)
{
    
}

int     polling::findClientFd(std::vector<appendClient> &client, int fd)
{
    std::vector<appendClient>::iterator it;
    
    it = std::find(client.begin(), client.end(), fd);
    if (it != client.end())
        return (it->getClientFd());
    return (-1);
    
}

void    polling::pushFd(int sockfd, int event)
{
    struct pollfd tmp;

    tmp.fd = sockfd;
    tmp.events = event;
    tmp.revents = 0;
    this->_pollfds.push_back(tmp);
}

void    polling::pushClient(appendClient &client)
{
    this->_clients.push_back(client);
}

void    polling::acceptConnection(appendClient &client, int fd)
{
    int check = 1;
    int newFd = accept(fd, 0, 0);
    if (newFd < 0)
    {
        perror("accept");
        //maybe exit or set error status
    }
    setsockopt(newFd, SOL_SOCKET, SO_NOSIGPIPE, &check, sizeof(check));
    client.setClientFd(fd);
    this->pushFd(client.getClientFd(), POLLIN);
    this->_clients.push_back(client);
}

void    polling::pushSocket(int fd)
{
    this->_sockets.push_back(fd);
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

int polling::closeConnections(int i)
{
    close(this->_pollfds[i].fd);
    this->_clients.erase(this->_pollfds[i].fd);
    this->_pollfds.erase(this->_pollfds.begin() + i);
    
    return (0);
}

void    polling::handlePoll(char *resp)
{
    for (size_t index = 0; index < this->_pollfds.size(); index++)
    {
        
        pollfd& pfd = this->_pollfds[index];
        
        //check if someone ready to read/connect
        if (pfd.revents & POLLIN)
        {
            //handle new connections 
            //check if index < _socket.size()
            if (pfd.fd == this->_sockets[index])
            {
                appendClient    newClient;
                this->acceptConnection(newClient, this->_sockets[index]);

                //print logs of new connection
                // sock.retrieveClientAdd(); // print the ip of the connection later
                std::cout << "New server connection on socket : " << newClient.getClientFd() << std::endl;
            }
            else //just regular client ready to recieve 
            {
                int checkRecv = polling::findClientFd(this->_clients, pfd.fd);
                if (checkRecv != -1)
                {
                    //start receiving for the specific client
                    this->_clients[checkRecv].recvHead();
                    
                    //client Fd executed the recv and now ready to send
                    pfd.events = POLLOUT;
                }
            }
        }
        //data ready to be sent 
        else if (pfd.revents & POLLOUT)
        {
            int checkSend = polling::findClientFd(this->_clients, pfd.fd);
            if (checkSend != -1)
            {
                this->_clients[checkSend].sendReq(checkSend);
            }
            if (this->_clients.getResponseStat() == 1)
                polling::closeConnections(index);
        }
        //client hang up
        if (pfd.revents & POLLHUP)
            polling::closeConnections(index);
    }
}