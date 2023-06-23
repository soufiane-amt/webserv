/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pollingServ.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 06:54:04 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/23 15:27:46 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pollingServ.hpp"


int64_t timing() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t currentTime = tv.tv_sec;
    return currentTime;
}

std::vector<char>    request_response(std::string msg, int targeted_serv)
{
    clientRequestParser test(msg);
    http_message_t &_request = test.getRequest();


    try
    {
        
            errorManager::isRequestValid(_request, targeted_serv);
            responsePreparation response(_request, targeted_serv);
            return response.get_response();
        
    }
    catch(const StatusCode& e)
    {
        responsePreparation response(_request,targeted_serv, e);
        
        std::cout << "======> Response : <======="<< std::endl;
        std::cout << response.get_response().data()<< std::endl;
        return response.get_response();
    }
    return std::vector<char>();
}


polling::polling(void): _timeout(0)
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
std::vector<appendClient>::iterator   polling::findClient(std::vector<tcpServer> &server, int fd, int *found)
{
    std::vector<tcpServer>::iterator servIT;
    std::vector<appendClient>::iterator end;;

    for (servIT = server.begin(); servIT != server.end(); servIT++)
    {    
        std::vector<appendClient>::iterator clientIT;
        for (clientIT = servIT->getClientsVec().begin(); clientIT != servIT->getClientsVec().end(); clientIT++)
        {
            if (clientIT->getClientFd() == fd)
            {
                *found = servIT->getIndex();
                this->_timeout = 1;
                return (clientIT);
            }
        }
        end = servIT->getClientsVec().end();
    }
    *found = 0;
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
    client.setTime(timing());
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
    int found = 0;
    for (size_t index = 0; index < this->_pollfds.size(); index++)
    {
        
        pollfd& pfd = this->_pollfds[index];
        
        //client hang up
        if (pfd.revents & POLLHUP)
        {
            std::vector<appendClient>::iterator checkSend = polling::findClient(this->_servers, pfd.fd, &found);
            polling::closeConnections(checkSend, pfd.fd, index);
        }
        //check if someone ready to read/connect
        else if (pfd.revents & POLLIN)
        {
            //handle new connections 
            if (pfd.fd == this->_sockets[index] && index < this->_sockets.size())
            {
                appendClient    newClient;
                this->acceptConnection(newClient, this->_sockets[index], this->_servers[index]);
                std::cout << "New server connection on socket : " << newClient.getClientFd() << std::endl;
            }
            else //just regular client ready to recieve 
            {   
                std::vector<appendClient>::iterator checkRecv = polling::findClient(this->_servers, pfd.fd, &found);
                checkRecv->setTime(timing());
                checkRecv->recvHead();
                //client Fd executed the recv and now ready to send
                if (checkRecv->getResponseStat() == responseGo)
                {
                    std::cout << "Printing the request:" << std::endl;
                    std::cout << checkRecv->getHTTPRequest() << std::endl;
                    checkRecv->setHTTPResponse(request_response(checkRecv->getHTTPRequest(), found));
                    pfd.events = POLLOUT;
                }
            }
        }
        //data ready to be sent 
        else if (pfd.revents & POLLOUT)
        {
            std::vector<appendClient>::iterator checkSend = polling::findClient(this->_servers, pfd.fd, &found);
            checkSend->sendReq(pfd.fd);
            if (checkSend->getResponseStat() == closeConnect)
                polling::closeConnections(checkSend,pfd.fd, index);
        }
    }
}

void    polling::handleTimeout()
{
    int found = 0;

    this->_timeout = 0;
    for (size_t i = 0; i < this->_pollfds.size(); i++)
    {
        pollfd& pfd = this->_pollfds[i];
        std::vector<appendClient>::iterator checkRecv = polling::findClient(this->_servers, pfd.fd, &found);
        if (this->_timeout != 0)
        {
            if (timing() - checkRecv->getTime() >= 10)
            {
                std::cout << "Client Timedout!" << std::endl;
                polling::closeConnections(checkRecv, pfd.fd, i);
            }
        }
    }
}