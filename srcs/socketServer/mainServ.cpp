/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainServ.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:51:46 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/01 16:24:01 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/fech-cha/Desktop/webserv/inc/pollingServ.hpp"
#include <fstream>

int main(void)
{  
    char resp[] = "HTTP/1.1 200 OK\r\n"
    "Server: webserver-cpp\r\n"
    "Content-type: text/html\r\n\r\n"
    "<html>hello, world</html>\r\n";
    
    
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
            pl.handlePoll(resp);        
        }
    }
    
    //calling destructor will close all connections
    return (0);
}