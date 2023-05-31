/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appendClientSide.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:06:16 by fech-cha          #+#    #+#             */
/*   Updated: 2023/05/31 02:51:43 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPENDCIENTSIDE_HPP
# define APPENDCIENTSIDE_HPP

#include "/Users/fech-cha/Desktop/webserv/inc/pollingServ.hpp"


class appendClient
{
    private:
        int         _clientFd;
        std::string _header;
        std::string _body;
    public:
        appendClient();
        ~appendClient();
        
        int     getClientFd(void);
        void    setClientFd(int fd);
};

#endif