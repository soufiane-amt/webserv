/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcpServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:43:07 by fech-cha          #+#    #+#             */
/*   Updated: 2023/04/09 22:27:22 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myServ.hpp"

tcpServer::tcpServer()
{
    std::cout << "Socket default constructor and initializer." << std::endl;
    //init len of structs
    this->webservAddrlen = sizeof(this->webservAddr);
    
    //define and init address structure of webserv
    memset(&this->webservAddr, 0, sizeof(this->webservAddr)); //empty the struct
    this->webservAddr.sin_family = AF_INET; //IPv4
    this->webservAddr.sin_port = htons(HTTP_PORT); //convert port to network byte order(short)
    this->webservAddr.sin_addr.s_addr = htonl(INADDR_ANY); // convert IP@ to network byte order (long) /any network interface available on the hos 

    //create socket
    this->sockfd = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
    tcpServer::testSysCall(tcpServer::getAcceptFd());

    //set the socket to be non-blocking
    fcntl(this->sockfd, F_SETFL, O_NONBLOCK);
    
    std::cout << "Socket created succesfully." << std::endl;
    
    //fix bind: socket already in use error
    tcpServer::rerunServ();
    
    //bind socket to the address
    this->bindRes = bind(getSockFd(), (struct sockaddr *)&this->webservAddr, this->webservAddrlen);
    tcpServer::testSysCall(tcpServer::getBindValue());
    std::cout << "Socket succesfully bound to address." << std::endl;

}

tcpServer::~tcpServer()
{
    std::cout << "Socket default deconstructor." << std::endl;
    tcpServer::closeConnection();
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
    
    int check = setsockopt(getSockFd(), SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    tcpServer::testSysCall(check);
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

const char*   tcpServer::getBuffer(void) const
{
    return (buffer);
}

void    tcpServer::listenRequest(void)
{
    int check = listen(getSockFd(), BACKLOG);
    tcpServer::testSysCall(check);
    std::cout << "Server listening for connections ... " << std::endl;
}

void    tcpServer::acceptConnection(void)
{
    this->clientAddrlen = sizeof(this->clientAddr);
    this->acceptSockFd = accept(getSockFd(), (struct sockaddr *)&this->clientAddr, (socklen_t *)&this->clientAddrlen);
}

void    tcpServer::closeConnection(void)
{
    close(this->acceptSockFd);
    close(this->sockfd);
}

void    tcpServer::sendReq(int sockfd, const void *buf, int len, int flags)
{
    this->sendRes = send(sockfd, buf, len, flags);
    //close sockfd of the connection
    close(sockfd);
    tcpServer::testSysCall(this->sendRes);
}

void    tcpServer::recvReq(int sockfd, void *buf, int len, int flags)
{
    this->recvRes = recv(sockfd, buf, len, flags);
    tcpServer::testSysCall(this->recvRes);
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

void    tcpServer::printLogs(void)
{

    char method[BUFFER_SIZE], uri[BUFFER_SIZE], version[BUFFER_SIZE];
        sscanf(this->buffer, "%s %s %s", method, uri, version);
        printf("[%s:%u] %s %s %s\n", inet_ntoa(this->clientAddr.sin_addr),
               ntohs(this->clientAddr.sin_port), method, version, uri);
}