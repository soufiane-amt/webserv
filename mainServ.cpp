/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainServ.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:51:46 by fech-cha          #+#    #+#             */
/*   Updated: 2023/03/31 09:04:00 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myServ.hpp"

int main(void)
{
    char resp[] = "HTTP/1.1 200 OK\r\n"
    "Server: webserver-cpp\r\n"
    "Content-type: text/html\r\n\r\n"
    "<html>hello, world</html>\r\n";
    
    //create socket and bind it
    mySocket sock;
    
    //create poll struct 
    polling pl;

    //push the socket fd to poll()
    pl.pushFd(sock.getSockFd(), POLLIN);
    
    //listen for connections 
    sock.listenRequest();
    
    while (1)
    {
        //waiting for events using poll()
        if (pl.callPoll((pollfd *)pl.getPollfdAddrs(), pl.getSize(), -1) > 0)
        {
            //handle I/O events
            pl.handlePoll(sock);

             //get client address (that's the idea)
        sock.retrieveClientAdd();
        if (sock.getSockName() < 0)
        {
            perror("Webserv (getsockname)");
            continue;
        }
        
        //recv from the browser
        sock.recvReq(sock.getAcceptFd(), (void *)sock.getBuffer(), BUFFER_SIZE, 0);
        
        //print_logs
        sock.printLogs();
        
        // this msg from the browser is then sent to the parser for HTTP Message Parsing

        // generate message in http rules from the webserv to the browser
        sock.sendReq(sock.getAcceptFd(), resp, strlen(resp), 0);
        }
    }
    //calling destructor will close all connections
    return (0);
}