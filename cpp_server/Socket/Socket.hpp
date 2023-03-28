/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:43:02 by fech-cha          #+#    #+#             */
/*   Updated: 2023/03/28 01:43:17 by fech-cha         ###   ########.fr       */
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

//domaine: ip_version
//service: SOCK_STREAM
//protocol: TCP
class mySocket
{
    private:
        struct addrinfo hints; //get info about the host network
        struct addrinfo *servinfo; //will point to the result 
        int sockfd;
        int bindRes;
    public:
        mySocket();
        ~mySocket();
        void    testSysCall(int fd);

        //getter functions
        struct sockaddr_in  getAddress() const;
        int                 getSockFd() const;
        int                 getBindValue() const;
};

#endif