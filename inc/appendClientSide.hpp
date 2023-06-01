/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appendClientSide.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:06:16 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/01 16:50:54 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPENDCIENTSIDE_HPP
# define APPENDCIENTSIDE_HPP

#include "/Users/fech-cha/Desktop/webserv/inc/pollingServ.hpp"

# define endOfBody 69
# define endOfHeader 420

class appendClient
{
    private:
        int         _checkHead;
        int         _checkBody;
        int         _clientFd;
        std::string _header;
        std::string _body;
    public:
        appendClient();
        ~appendClient();
        
        
        // I/O methods for servers
        void    sendReq(int sockfd);
        void    recvReq(int sockfd);

        //getters & setters
        int     getClientFd(void);
        void    setClientFd(int fd);
        int     getStatus(void);
        void    setStatus(int update);

};

#endif