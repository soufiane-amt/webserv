/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:56:03 by samajat           #+#    #+#             */
/*   Updated: 2023/03/31 23:27:02 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "requestParser.hpp"
#include "responding.hpp"
#include "errorManager.hpp"

std::string msg= "GET / HTTP/1.1\r\n"
            "host: 192.241.213.46:6880\r\n"
            "Upgrade-Insecure-Requests: 1\r\n"
            "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
            "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_3) AppleWebKit/602.4.8 (KHTML, like Gecko) Version/10.0.3 Safari/602.4.8\r\n"
            "Accept-Language: en-us\r\n"
            "Accept-Encoding: gzip, deflate\r\n"
            "Connection: keep-alive\r\n\r\n";

// std::string msg= "POST /sdfdsf/fdsf HTTP/1.1\r\n"
//             "Host: example.com\r\n"
//             "Content-Type: application/json\r\n"
//             "Content-Length: 43\r\n\r\n"
//             "{\"name\": \"John Doe\", \"email\": \"johndoe@example.com\"}";

//According to RFC "Each header field consists of a name followed by a colon (":") and the field value. Field names are case-insensitive. "
//So we need to convert all the keys to lower case
// std::string toLower(std::string str)
// {
//     std::transform(str.begin(), str.end(), str.begin(), ::tolower);
//     return str;
// }
/*temp server headers*/
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
// #define PORT 4004
#define PORT 1234


std::string    request_response(std::string msg)
{
    clientRequestParser test(msg);
    http_message_t &_request = test.getRequest();

    try
    {
        errorManager::isRequestValid(_request);
        responsePreparation response(_request);
        return response.get_response();
    }
    catch(const StatusCode& e)
    {
        responsePreparation response(_request, e);
        return response.get_response();
    }
    return "";

}

void    tempServer ()
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
        std::cout << request_response(buffer).c_str() << std::endl;
        write(new_socket , request_response(buffer).c_str() , request_response(buffer).length());
        printf("------------------Hello message sent-------------------\n");
        close(new_socket);
    }
}

int main ()
{
    try
    {
        tempServer();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    // clientRequestParser test(msg);
    // http_message_t &_request = test.getRequest();

    // try
    // {
    //     errorManager::isRequestValid(_request);
    //     responsePreparation response(_request);
    //     std::cout << response.get_response();
    // }
    // catch(const StatusCode& e)
    // {
    //     responsePreparation response(_request, e);
    //     std::cout << response.get_response();
    // }
}