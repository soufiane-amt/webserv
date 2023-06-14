/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcpServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:43:02 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/14 16:55:03 by fech-cha         ###   ########.fr       */
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

#include "pollingServ.hpp"

# define BACKLOG 100

# define BUFFER_SIZE 1024

class   polling;
class   appendClient;
class tcpServer
{
    private:
        //server/client addresses info
        struct sockaddr_in  webservAddr;
        int                 webservAddrlen;
        struct sockaddr_in  clientAddr;
        int                 clientAddrlen;
        
        int index;
        int sockfd;
        int bindRes;
        int acceptSockFd;
        int sendRes;
        int recvRes;
        int sockName;
        std::vector<appendClient>   _clients;
        
    public:
        tcpServer(polling &pl, int port, std::string host, int index);
        ~tcpServer();
        void    testSysCall(int fd);
        void    rerunServ(void);
        void    listenConnection(void);
        void    closeConnection(void);

        //still not clear about this part
        void    printLogs(void);
        void    retrieveClientAdd(void);
        
        //getter functions
        int                 getIndex();
        int                 getSockFd(void) const;
        int                 getBindValue(void) const;
        int                 getAcceptFd(void) const;
        int                 getSockName(void) const;
        std::vector<appendClient>& getClientsVec();

        //setters
        void    setClient(appendClient &client);
};

#endif