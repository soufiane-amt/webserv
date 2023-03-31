/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:43:07 by fech-cha          #+#    #+#             */
/*   Updated: 2023/03/31 08:59:38 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myServ.hpp"

mySocket::mySocket()
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
    mySocket::testSysCall(mySocket::getAcceptFd());

    //set the socket to be non-blocking
    fcntl(this->sockfd, F_SETFL, O_NONBLOCK);
    
    std::cout << "Socket created succesfully." << std::endl;
    
    //fix bind: socket already in use error
    mySocket::rerunServ();
    
    //bind socket to the address
    this->bindRes = bind(getSockFd(), (struct sockaddr *)&this->webservAddr, this->webservAddrlen);
    mySocket::testSysCall(mySocket::getBindValue());
    std::cout << "Socket succesfully bound to address." << std::endl;

}

mySocket::~mySocket()
{
    std::cout << "Socket default deconstructor." << std::endl;
    mySocket::closeConnection();
}

void    mySocket::testSysCall(int fd)
{
    if (fd < 0)
    {
        perror("Network Failure.");
        exit(EXIT_FAILURE);
    }
}

void    mySocket::rerunServ(void)
{
    int enable = 1;
    
    int check = setsockopt(getSockFd(), SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    mySocket::testSysCall(check);
}

int mySocket::getSockFd(void) const
{
    return (this->sockfd);    
}

int mySocket::getBindValue(void) const
{
    return (this->bindRes);
}

int mySocket::getAcceptFd(void) const
{
    return (this->acceptSockFd);
}

int mySocket::getSockName(void) const
{
    return (this->sockName);
}

const char*   mySocket::getBuffer(void) const
{
    return (buffer);
}

void    mySocket::listenRequest(void)
{
    int check = listen(getSockFd(), BACKLOG);
    mySocket::testSysCall(check);
    std::cout << "Server listening for connections ... " << std::endl;
}

void    mySocket::acceptConnection(void)
{
    this->clientAddrlen = sizeof(this->clientAddr);
    this->acceptSockFd = accept(getSockFd(), (struct sockaddr *)&this->clientAddr, (socklen_t *)&this->clientAddrlen);
}

void    mySocket::closeConnection(void)
{
    close(this->acceptSockFd);
    close(this->sockfd);
}

void    mySocket::sendReq(int sockfd, const void *buf, int len, int flags)
{
    this->sendRes = send(sockfd, buf, len, flags);
    //close sockfd of the connection
    close(sockfd);
    mySocket::testSysCall(this->sendRes);
}

void    mySocket::recvReq(int sockfd, void *buf, int len, int flags)
{
    this->recvRes = recv(sockfd, buf, len, flags);
    mySocket::testSysCall(this->recvRes);
}

void    mySocket::retrieveClientAdd(void)
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

void    mySocket::printLogs(void)
{

    char method[BUFFER_SIZE], uri[BUFFER_SIZE], version[BUFFER_SIZE];
        sscanf(this->buffer, "%s %s %s", method, uri, version);
        printf("[%s:%u] %s %s %s\n", inet_ntoa(this->clientAddr.sin_addr),
               ntohs(this->clientAddr.sin_port), method, version, uri);
}