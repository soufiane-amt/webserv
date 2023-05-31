/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pollingServ.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 06:52:32 by fech-cha          #+#    #+#             */
/*   Updated: 2023/05/31 02:10:45 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLLINGSERV_HPP
# define POLLINGSERV_HPP

#include "tcpServer.hpp"
#include "appendClientSide.hpp"

//add class for packet

class tcpServer;
class   polling
{
    private:
        std::vector<pollfd>     _pollfds;
        std::vector<int>        _sockets;
        std::vector<tcpServer>  _servers;
    public:
        polling(void);
        ~polling(void);
        
        void    pushSocket(int fd);
        int     callPoll(struct pollfd *fds, nfds_t nfds, int timeout);
        void    pushFd(int sockfd, int event);
        void    handlePoll(char *event);
        int     closeConnections(int fd);
        int     sendAll(int fd, char *buf, int *len);
        int     recvAll(int fd, char *buf, int len);
        void    pushServer(tcpServer &server);
        
        //getters
        nfds_t  getSize(void) const;
        const struct pollfd    *getPollfdAddrs(void) const;
};

#endif