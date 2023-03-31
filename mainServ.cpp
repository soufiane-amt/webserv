/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainServ.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:51:46 by fech-cha          #+#    #+#             */
/*   Updated: 2023/03/31 05:44:08 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

int main(void)
{
    char resp[] = "HTTP/1.1 200 OK\r\n"
    "Server: webserver-cpp\r\n"
    "Content-type: text/html\r\n\r\n"
    "<html>hello, world</html>\r\n";
    
    //create socket and bind it
    mySocket sock;

    //listen for connections 
    sock.listenRequest();
    
    //this will be in a poll()
    while (1)
    {
        //accept connections 
        sock.acceptConnection();
        if (sock.getAcceptFd() < 0)
        {
            perror("Webserv (accept)");
            continue;
        }
        std::cout << "Connection accepted!" << std::endl;

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
    //calling destructor will close all connections
    return (0);
}