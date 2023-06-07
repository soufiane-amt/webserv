/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pollingServ.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 06:54:04 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/07 15:14:36 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pollingServ.hpp"


std::vector<char>    request_response(std::string msg)
{
    clientRequestParser test(msg);
    http_message_t &_request = test.getRequest();

    try
    {
            errorManager::isRequestValid(_request);
            responsePreparation response(_request);
        
            return response.get_response();
        
    }
    catch(const StatusCode& e)
    {
        responsePreparation response(_request, e);
        return response.get_response();
    }
    return std::vector<char>();
}

polling::polling(void)
{
    
}

polling::~polling(void)
{
    
}

void    polling::pushServer(tcpServer &serv)
{
    this->_servers.push_back(serv);
}


//find the right server
std::vector<tcpServer>::iterator   polling::findServer(std::vector<tcpServer> &server, int fd)
{
    std::vector<tcpServer>::iterator servIT;

    for (servIT = server.begin(); servIT != server.end(); servIT++)
    {    
        std::vector<appendClient>::iterator clientIT;
        for (clientIT = servIT->getClientsVec().begin(); clientIT != servIT->getClientsVec().end(); clientIT++)
        {
            if (clientIT->getClientFd() == fd)
                return (servIT);
        }
    }
    return (server.end());
}

//find the right client
std::vector<appendClient>::iterator   polling::findClient(std::vector<appendClient> &client, int fd)
{
        std::vector<appendClient>::iterator clientIT;
        for (clientIT = client.begin(); clientIT != client.end(); clientIT++)
        {
            if (clientIT->getClientFd() == fd)
                return (clientIT);
        }
    return (client.end());
}

void    polling::pushFd(int sockfd, int event)
{
    struct pollfd tmp;

    tmp.fd = sockfd;
    tmp.events = event;
    tmp.revents = 0;
    this->_pollfds.push_back(tmp);
}

void    polling::acceptConnection(appendClient &client, int fd, tcpServer &serv)
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
    serv.setClient(client);
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

int polling::closeConnections(std::vector<appendClient>::iterator findClient,int fd, int index)
{
    close(fd);
    this->_pollfds.erase(this->_pollfds.begin() + index);

    std::vector<tcpServer>::iterator servIT;
    for (servIT = this->_servers.begin(); servIT != this->_servers.end(); servIT++)
    {
        std::vector<appendClient>::iterator clientIT;
        for (clientIT = servIT->getClientsVec().begin(); clientIT != servIT->getClientsVec().end(); clientIT++)
        {
            if (findClient == clientIT)
                servIT->getClientsVec().erase(clientIT);
        }
    }
    std::cout << "Connection Closed!" << std::endl;
    return (0);
}

void    polling::handlePoll()
{
    for (size_t index = 0; index < this->_pollfds.size(); index++)
    {
        
        pollfd& pfd = this->_pollfds[index];
        
        //check if someone ready to read/connect
        if (pfd.revents & POLLIN)
        {
            //handle new connections 
            //check if index < _socket.size()
            if (pfd.fd == this->_sockets[index] && index < this->_sockets.size())
            {
                appendClient    newClient;
                this->acceptConnection(newClient, this->_sockets[index], this->_servers[index]);

                //print logs of new connection
                // sock.retrieveClientAdd(); // print the ip of the connection later
                std::cout << "New server connection on socket : " << newClient.getClientFd() << std::endl;
            }
            else //just regular client ready to recieve 
            {   
                std::vector<tcpServer>::iterator rightServ = polling::findServer(this->_servers, pfd.fd);
                std::vector<appendClient>::iterator checkRecv = polling::findClient(rightServ->getClientsVec(), pfd.fd);
                if (checkRecv != rightServ->getClientsVec().end())
                {
                    //start receiving for the specific client
                    checkRecv->recvHead();
                    
                    //client Fd executed the recv and now ready to send
                    if (checkRecv->getResponseStat() == responseGo)
                        //parse request
                        checkRecv->setHTTPResponse(request_response(checkRecv->getHTTPRequest()));
                        pfd.events = POLLOUT;
                }
            }
        }
        //data ready to be sent 
        else if (pfd.revents & POLLOUT)
        {
            std::vector<tcpServer>::iterator rightServ = polling::findServer(this->_servers, pfd.fd);
            std::vector<appendClient>::iterator checkSend = polling::findClient(rightServ->getClientsVec(), pfd.fd);
            if (checkSend != rightServ->getClientsVec().end())
                checkSend->sendReq(pfd.fd);
            if (checkSend->getResponseStat() == closeConnect)
                polling::closeConnections(checkSend,pfd.events, index);
        }
        //client hang up
        if (pfd.revents & POLLHUP)
        {
            std::vector<tcpServer>::iterator rightServ = polling::findServer(this->_servers, pfd.fd);
            std::vector<appendClient>::iterator checkSend = polling::findClient(rightServ->getClientsVec(), pfd.fd);
            polling::closeConnections(checkSend, pfd.fd, index);
        }
    }
}