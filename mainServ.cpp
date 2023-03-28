/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainServ.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:51:46 by fech-cha          #+#    #+#             */
/*   Updated: 2023/03/28 08:02:03 by fech-cha         ###   ########.fr       */
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
    
    sock.rerunServ();
    sock.listenRequest();
    //usually this will be a fork, create children proccess to handle each connection
    while (1)
    {
        sock.acceptConnection();
        std::cout << "Connection accepted!" << std::endl;
        
        //recv from the browser
        sock.recvReq(sock.getAcceptFd(), buffer, BUFFER_SIZE, 0);
        
        // this msg from the browser is then sent to the parser for HTTP Message Parsing

        // generate message in http rules from the webserv to the browser
        sock.sendReq(sock.getAcceptFd(), resp, strlen(resp), 0);
    }
    sock.closeConnection();    
    return (0);
}