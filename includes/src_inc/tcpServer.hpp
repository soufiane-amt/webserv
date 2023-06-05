/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcpServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:43:02 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/04 16:42:35 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCPSERVER_HPP
# define TCPSERVER_HPP

#include <string>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>  
#include <string.h>
#include <cstring>
#include <fcntl.h>
#include <arpa/inet.h>
#include <poll.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <csignal>
#include <unistd.h>

//close / keep-alive option

#include "pollingServ.hpp"

# define closeConnect 3
# define responseGo 1
# define lastChunk "0\r\n\r\n"
# define CRLF "\r\n\r\n"
# define endOfBody 69
# define endOfHeader 420

# define HTTP_PORT 6969
# define BACKLOG 100

//temp buff size
# define BUFFER_SIZE 1024

class   polling;
class tcpServer
{
    private:
        //server/client addresses info
        struct sockaddr_in  webservAddr;
        int                 webservAddrlen;
        struct sockaddr_in  clientAddr;
        int                 clientAddrlen;
        
        
        int sockfd;
        int bindRes;
        int acceptSockFd;
        int sendRes;
        int recvRes;
        int sockName;
        char    buffer[BUFFER_SIZE];

        
    public:
        tcpServer(polling &pl, int port, std::string host);
        ~tcpServer();
        void    testSysCall(int fd);
        void    rerunServ(void);
        void    listenConnection(void);
        void    closeConnection(void);

        //still not clear about this part
        void    printLogs(void);
        void     retrieveClientAdd(void);
        
        //getter functions
        int                 getSockFd(void) const;
        int                 getBindValue(void) const;
        int                 getAcceptFd(void) const;
        int                 getSockName(void) const;
        const char                *getBuffer(void) const;

        //setters
};

#endif