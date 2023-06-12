/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pollingServ.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 06:54:04 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/12 02:11:18 by fech-cha         ###   ########.fr       */
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
std::vector<appendClient>::iterator   polling::findClient(std::vector<tcpServer> &server, int fd)
{
    std::vector<tcpServer>::iterator servIT;
    std::vector<appendClient>::iterator end;;

    for (servIT = server.begin(); servIT != server.end(); servIT++)
    {    
        std::vector<appendClient>::iterator clientIT;
        for (clientIT = servIT->getClientsVec().begin(); clientIT != servIT->getClientsVec().end(); clientIT++)
        {
            if (clientIT->getClientFd() == fd)
                return (clientIT);
        }
        end = servIT->getClientsVec().end();
    }
    return (end);
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
    client.setClientFd(newFd);
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

int polling::closeConnections(std::vector<appendClient>::iterator findClient,int cfd, int index)
{
    close(cfd);
    this->_pollfds.erase(this->_pollfds.begin() + index);

    std::vector<tcpServer>::iterator servIT;
    for (servIT = this->_servers.begin(); servIT != this->_servers.end(); servIT++)
    {
        std::vector<appendClient>::iterator clientIT;
        for (clientIT = servIT->getClientsVec().begin(); clientIT != servIT->getClientsVec().end(); clientIT++)
        {
            if (findClient->getClientFd() == clientIT->getClientFd())
            {
                servIT->getClientsVec().erase(clientIT);
                break;
            }
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
                std::vector<appendClient>::iterator checkRecv = polling::findClient(this->_servers, pfd.fd);
                checkRecv->recvHead();
                //client Fd executed the recv and now ready to send
                if (checkRecv->getResponseStat() == responseGo)
                {
                    std::cout << "Printing the request:" << std::endl;
                    std::cout << checkRecv->getHTTPRequest() << std::endl;
                    checkRecv->setHTTPResponse(request_response(checkRecv->getHTTPRequest()));
                    pfd.events = POLLOUT;
                }
            }
        }
        //data ready to be sent 
        else if (pfd.revents & POLLOUT)
        {
            std::vector<appendClient>::iterator checkSend = polling::findClient(this->_servers, pfd.fd);
            checkSend->sendReq(pfd.fd);
            if (checkSend->getResponseStat() == closeConnect)
                polling::closeConnections(checkSend,pfd.fd, index);
        }
        //client hang up
        if (pfd.revents & POLLHUP)
        {
            std::vector<appendClient>::iterator checkSend = polling::findClient(this->_servers, pfd.fd);
            polling::closeConnections(checkSend, pfd.fd, index);
        }
    }
}