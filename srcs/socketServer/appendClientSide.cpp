
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appendClientSide.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:05:34 by fech-cha          #+#    #+#             */
/*   Updated: 2023/05/31 05:15:44 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
const int BUFFER_SIZE = 1024;

#include "/Users/fech-cha/Desktop/webserv/inc/pollingServ.hpp"


appendClient::appendClient(): _check(0), _clientFd(-69)
{
    
}

appendClient::~appendClient()
{
    
}

void    appendClient::setClientFd(int fd)
{
    this->_clientFd = fd;
}

int appendClient::getClientFd(void)
{
    return (this->_clientFd);
}

int appendClient::getStatus(void)
{
    return (this->_check);
}

void    appendClient::setStatus(int update)
{
    this->_check = update;
}

void    appendClient::sendReq(int sockfd)
{
    this->sendRes = send(sockfd, buf, len, flags);
    //close sockfd of the connection
    close(sockfd);
    appendClient::testSysCall(this->sendRes);
}

void    appendClient::recvReq(int sockfd)
{
    this->recvRes = recv(sockfd, buf, len, flags);
    appendClient::testSysCall(this->recvRes);
}



struct Client {
    int socket;
    std::string request;
};

std::string receiveHttpRequest(int clientSocket) {
    std::vector<char> buffer(BUFFER_SIZE, '\0');
    std::string request;

    // Read until the end of the request header
    while (true) {
        ssize_t bytesRead = recv(clientSocket, &buffer[0], buffer.size() - 1, 0);

        if (bytesRead == -1) {
            std::cerr << "Error in recv\n";
            return "";
        } else if (bytesRead == 0) {
            // Client disconnected
            return "";
        } else {
            buffer[bytesRead] = '\0';
            request += &buffer[0];

            // Check if the full request header has been received
            std::size_t found = request.find("\r\n\r\n");
            if (found != std::string::npos) {
                // Process the complete request header
                break;
            }

            // Check if the buffer is full
            if (bytesRead == BUFFER_SIZE - 1) {
                buffer.resize(buffer.size() + BUFFER_SIZE);
            }
        }
    }

    // Check if the request has a "Content-Length" header
    std::size_t contentLengthPos = request.find("Content-Length:");
    if (contentLengthPos != std::string::npos) {
        std::size_t startPos = contentLengthPos + sizeof("Content-Length:");
        std::size_t endPos = request.find("\r\n", startPos);
        std::string contentLengthStr = request.substr(startPos, endPos - startPos);
        int contentLength = std::atoi(contentLengthStr.c_str());

        // Read the request body based on the content length
        while (request.length() < contentLength + found + sizeof("\r\n\r\n")) {
            std::vector<char> buffer(BUFFER_SIZE, '\0');
            ssize_t bytesRead = recv(clientSocket, &buffer[0], buffer.size() - 1, 0);

            if (bytesRead == -1) {
                std::cerr << "Error in recv\n";
                return "";
            } else if (bytesRead == 0) {
                // Client disconnected
                return "";
            } else {
                buffer[bytesRead] = '\0';
                request += &buffer[0];
            }
        }
    }

    // Check if the request has "Transfer-Encoding: chunked" header
    std::size_t chunkedEncodingPos = request.find("Transfer-Encoding: chunked");
    if (chunkedEncodingPos != std::string::npos) {
        std::string requestBody;
        std::size_t bodyStartPos = request.find("\r\n\r\n") + sizeof("\r\n\r\n");

        // Read each chunk of the request body
        while (true) {
            std::vector<char> chunkSizeStr(BUFFER_SIZE, '\0');
            ssize_t bytesRead = recv(clientSocket, &chunkSizeStr[0], chunkSizeStr.size() - 1, 0);

            if (bytesRead == -1) {
                std::cerr << "Error in recv\n";
                return "";
            } else if (bytesRead == 0) {
                // Client disconnected
                return "";
            } else {
                chunkSizeStr[bytesRead] = '\0';
                int chunkSize = std::strtol(&chunkSizeStr[0], nullptr, 16);
                            if (chunkSize == 0)
                break;

            std::vector<char> chunkData(chunkSize + 2, '\0'); // Add 2 for CRLF
            bytesRead = recv(clientSocket, &chunkData[0], chunkData.size() - 1, 0);

            if (bytesRead == -1) {
                std::cerr << "Error in recv\n";
                return "";
            } else if (bytesRead == 0) {
                // Client disconnected
                return "";
            } else {
                chunkData[bytesRead] = '\0';
                requestBody += &chunkData[0];

                // Read the CRLF after each chunk
                std::vector<char> crlf(2, '\0');
                bytesRead = recv(clientSocket, &crlf[0], crlf.size() - 1, 0);

                if (bytesRead == -1) {
                    std::cerr << "Error in recv\n";
                    return "";
                } else if (bytesRead == 0) {
                    // Client disconnected
                    return "";
                } else {
                    // Check for the final CRLF indicating the end of the request body
                    if (crlf[0] != '\r' || crlf[1] != '\n') {
                        std::cerr << "Invalid chunk format\n";
                        return "";
                    }
                }
            }
        }
    }

    // Append the request body to the complete request
    request += requestBody;
}

return request;
)