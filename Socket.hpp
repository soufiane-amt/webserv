/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:43:02 by fech-cha          #+#    #+#             */
/*   Updated: 2023/03/28 05:46:02 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>  
#include <string.h>

# define HTTP_PORT "80"
# define BACKLOG 20
/* getaddrinfo => socket => bind => lsiten*/
class mySocket
{
    private:
        struct addrinfo hints; //get info about the host network
        struct addrinfo *servinfo; //will point to the result 
        struct sockaddr_storage incomingStruct;
        socklen_t incomingAddSize;
        
        int sockfd;
        int bindRes;
        int acceptSockFd;
        
    public:
        mySocket();
        ~mySocket();
        void    testSysCall(int fd);
        void    rerunServ(void);
        void    listenRequest(void);
        void    acceptConnection(void);

        //getter functions
        int                 getSockFd() const;
        int                 getBindValue() const;
};

#endif