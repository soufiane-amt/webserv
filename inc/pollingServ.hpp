/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pollingServ.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 06:52:32 by fech-cha          #+#    #+#             */
/*   Updated: 2023/05/31 04:18:43 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLLINGSERV_HPP
# define POLLINGSERV_HPP

#include "tcpServer.hpp"
#include "appendClientSide.hpp"

class tcpServer;
class appendClient;
class   polling
{
    private:
        std::vector<pollfd>         _pollfds;
        std::vector<int>            _sockets;
        std::vector<tcpServer>      _servers;
        std::vector<appendClient>   _clients;
    public:
        polling(void);
        ~polling(void);
        
        void    pushSocket(int fd);
        int     callPoll(struct pollfd *fds, nfds_t nfds, int timeout);
        void    pushFd(int sockfd, int event);
        void    handlePoll(char *event);
        void    acceptConnection(appendClient &client, int fd);
        int     closeConnections(int fd);
        int     sendAll(int fd, char *buf, int *len);
        int     recvAll(int fd, char *buf, int len);
        void    pushServer(tcpServer &server);
        void    pushClient(appendClient &client);
        int     findClientFd(std::vector<appendClient> &client, int fd);
        
        //getters
        nfds_t  getSize(void) const;
        const struct pollfd    *getPollfdAddrs(void) const;
};

#endif