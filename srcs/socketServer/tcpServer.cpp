/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcpServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:43:07 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/23 16:54:08 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pollingServ.hpp"

tcpServer::tcpServer(polling &pl, int port, std::string host, int index)
{
    std::cout << "Socket default constructor and initializer." << std::endl;
    //init len of structs
    this->webservAddrlen = sizeof(this->webservAddr);
    
    //define and init address structure of webserv
    memset(&this->webservAddr, 0, sizeof(this->webservAddr)); //empty the struct
    this->webservAddr.sin_family = AF_INET; //IPv4
    this->webservAddr.sin_port = htons(port); //convert port to network byte order(short)
    this->webservAddr.sin_addr.s_addr = inet_addr(host.c_str()); // convert IP@ to network byte order (long) /any network interface available on the host 

    this->index = index;
    //create socket
    this->sockfd = socket(PF_INET, SOCK_STREAM,IPPROTO_TCP);
    tcpServer::testSysCall(this->sockfd);

    //set the socket to be non-blocking
    fcntl(this->sockfd, F_SETFL, O_NONBLOCK);
    
    std::cout << "Socket created succesfully." << std::endl;
    
    //fix bind: socket already in use error
    tcpServer::rerunServ();
    
    //bind socket to the address
    this->bindRes = bind(this->sockfd, (struct sockaddr *)&this->webservAddr, this->webservAddrlen);
    tcpServer::testSysCall(this->bindRes);
    std::cout << "Socket succesfully bound to address." << std::endl;

    //make the socket listen for connections
    tcpServer::listenConnection();

    //push socket to socket list
    pl.pushSocket(this->sockfd);

    //push the socket fd to poll()
    pl.pushFd(this->sockfd, POLLIN);

}

tcpServer::~tcpServer()
{

}

void    tcpServer::testSysCall(int fd)
{
    if (fd < 0)
    {
        perror("Network Failure.");
        exit(EXIT_FAILURE);
    }
}

void    tcpServer::rerunServ(void)
{
    int enable = 1;
    
    int check = setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    tcpServer::testSysCall(check);
}

int tcpServer::getIndex()
{
    return (this->index);
}

int tcpServer::getSockFd(void) const
{
    return (this->sockfd);    
}

int tcpServer::getBindValue(void) const
{
    return (this->bindRes);
}

int tcpServer::getAcceptFd(void) const
{
    return (this->acceptSockFd);
}

int tcpServer::getSockName(void) const
{
    return (this->sockName);
}

void    tcpServer::listenConnection(void)
{
    int check = listen(getSockFd(), BACKLOG);
    tcpServer::testSysCall(check);
    std::cout << "Server listening for connections ... " << std::endl;
}

std::vector<appendClient>& tcpServer::getClientsVec()
{
    return (this->_clients);
}

void    tcpServer::setClient(appendClient &client)
{
    this->_clients.push_back(client);
}

void    tcpServer::closeConnection(void)
{
    close(this->acceptSockFd);
    close(this->sockfd);
}

void    tcpServer::retrieveClientAdd(void)
{
    this->sockName = getsockname(getAcceptFd(), (struct sockaddr *)&this->clientAddr, (socklen_t *)&this->clientAddrlen);
}

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// void    tcpServer::printLogs(void)
// {

//     char method[BUFFER_SIZE], uri[BUFFER_SIZE], version[BUFFER_SIZE];
//         sscanf(this->buffer, "%s %s %s", method, uri, version);
//         printf("[%s:%u] %s %s %s\n", inet_ntoa(this->clientAddr.sin_addr),
//                ntohs(this->clientAddr.sin_port), method, version, uri);
// }