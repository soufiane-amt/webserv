/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainServ.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:51:46 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/05 18:21:54 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pollingServ.hpp"

int main(void)
{  
    //create poll object to handle servers
    polling pl;
    
    //create socket object and bind it (socket could take args depends on the config)
    //socket should take ports amd host from config
    //for each socket, push it's fd to poll list
    //loop through servers
    tcpServer sock(pl, HTTP_PORT, INADDR_ANY);
    pl.pushServer(sock);
    
    
    while (1)
    {
        //waiting for events using poll()
        int poll_count = pl.callPoll((pollfd *)pl.getPollfdAddrs(), pl.getSize(), -1);
        
        if (poll_count  == -1)
        {
            perror("poll");
            // exit(EXIT_FAILURE);
            continue;
        }
        else
        {
            //handle I/O events
            pl.handlePoll();        
        }
    }
    
    //calling destructor will close all connections
    return (0);
}