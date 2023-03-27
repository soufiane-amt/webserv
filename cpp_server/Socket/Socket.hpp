/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:43:02 by fech-cha          #+#    #+#             */
/*   Updated: 2023/03/27 07:42:59 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>  

//domaine: ip_version
//service: SOCK_STREAM
//protocol: TCP
class mySocket
{
    private:
        struct sockaddr_in  address;
        int sockfd;
        int connection;
    public:
        mySocket(int domain, int serviceType, int protocol, int port, u_long interface); 
        void    testSysCall(int fd);

        //getter functions
        struct sockaddr_in  getAddress() const;
        int                 getSockFd() const;
        int                 getBindValue() const;
};

#endif