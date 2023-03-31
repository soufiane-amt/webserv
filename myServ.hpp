/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myServ.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 06:52:32 by fech-cha          #+#    #+#             */
/*   Updated: 2023/03/31 06:54:32 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSERV_HPP
# define MYSERV_HPP

#include "Socket.hpp"

class   myServ
{
    private:
        std::vector<pollfd> _pollfds;
    public:
        myServ(void);
        ~myServ(void);
        void    pushFd(int sockfd, int event);
};

#endif