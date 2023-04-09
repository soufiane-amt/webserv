/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainServ.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:51:46 by fech-cha          #+#    #+#             */
/*   Updated: 2023/04/09 22:29:18 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myServ.hpp"

int main(void)
{
    char resp[] = "HTTP/1.1 200 OK\r\n"
    "Server: webserver-cpp\r\n"
    "Content-type: text/html\r\n\r\n"
    "<html>hello, world</html>\r\n";
    
    //create socket object and bind it
    tcpServer sock;
    
    //create poll object 
    polling pl;

    //push the socket fd to poll()
    pl.pushFd(sock.getSockFd(), POLLIN);
    
    //listen for connections 
    sock.listenRequest();
    
    while (1)
    {
        //waiting for events using poll()
        int poll_count = pl.callPoll((pollfd *)pl.getPollfdAddrs(), pl.getSize(), -1);
        
        if (poll_count  == -1)
        {
            perror("poll");
            exit(EXIT_FAILURE);
        }
        else
        {
            //handle I/O events
            pl.handlePoll(sock, resp);        
        }
    }
    
    //calling destructor will close all connections
    return (0);
}