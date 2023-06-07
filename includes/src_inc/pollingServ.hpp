/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pollingServ.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 06:52:32 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/07 15:10:35 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLLINGSERV_HPP
# define POLLINGSERV_HPP

#include "tcpServer.hpp"
#include "appendClientSide.hpp"
#include "requestParser.hpp"
#include "responding.hpp"
#include "errorManager.hpp"
#include "config.hpp"
#include <vector>

class tcpServer;
class appendClient;
class   polling
{
    private:
        std::vector<pollfd>         _pollfds;
        std::vector<int>            _sockets;
        std::vector<tcpServer>      _servers;
       
    public:
        polling(void);
        ~polling(void);
        
        void    pushSocket(int fd);
        int     callPoll(struct pollfd *fds, nfds_t nfds, int timeout);
        void    pushFd(int sockfd, int event);
        void    handlePoll();
        void    acceptConnection(appendClient &client, int fd, tcpServer &serv);
        int     closeConnections(std::vector<appendClient>::iterator clientIT,int fd, int index);
        void    pushServer(tcpServer &server);
        std::vector<appendClient>::iterator findClient(std::vector<appendClient> &client, int fd);
        std::vector<tcpServer>::iterator findServer(std::vector<tcpServer> &server, int fd);
        
        //getters
        nfds_t  getSize(void) const;
        const struct pollfd    *getPollfdAddrs(void) const;
};

#endif