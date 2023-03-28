/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainServ.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:51:46 by fech-cha          #+#    #+#             */
/*   Updated: 2023/03/28 11:17:29 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

int main(void)
{
    char buffer[BUFFER_SIZE];
    char resp[] = "HTTP/1.1 200 OK\r\n"
    "Server: webserver-cpp\r\n"
    "Content-type: text/html\r\n\r\n"
    "<html>hello, world</html>\r\n";
    
    mySocket sock;

    sock.listenRequest();
    //usually this will be a fork, create children proccess to handle each connection
    //or this will be in a poll()
    while (1)
    {
        sock.acceptConnection();
        std::cout << "Connection accepted!" << std::endl;

        //get client address (that's the idea)
        sock.retrieveClientAdd();
        
        //recv from the browser
        sock.recvReq(sock.getAcceptFd(), buffer, BUFFER_SIZE, 0);
        
        //print_logs
        char method[BUFFER_SIZE], uri[BUFFER_SIZE], version[BUFFER_SIZE];
        sscanf(buffer, "%s %s %s", method, uri, version);
        sock.printLogs();

        // this msg from the browser is then sent to the parser for HTTP Message Parsing

        // generate message in http rules from the webserv to the browser
        sock.sendReq(sock.getAcceptFd(), resp, strlen(resp), 0);
    }
    sock.closeConnection();    
    return (0);
}