
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

#include "/Users/fech-cha/Desktop/webserv/inc/pollingServ.hpp"


appendClient::appendClient(): _checkHead(0), _checkBody(0), _clientFd(-69), _responseStatus(0)
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

int appendClient::getHeadStatus()
{
    return (this->_checkHead);
}

void    appendClient::setHeadStatus(int head)
{
    this->_checkHead = head;
}

int appendClient::getBodyStatus()
{
    return (this->_checkBody);
}

void    appendClient::setBodyStatus(int Body)
{
    this->_checkBody = Body;
}

std::string appendClient::getHeader()
{
    return (this->_header);
}

std::string appendClient::getBody()
{
    return (this->_body);
}

void    appendClient::setBody(std::string body)
{
    this->_body.append(body);
}

std::string appendClient::getRestOfRes(int size)
{

}

void    appendClient::sendReq(int sockfd)
{
    int check;
    check = send(sockfd, getResponse().c_str(), getResponse.size(), 0);
    if (check < 0)
    {
        // error
    }
    this->response.erase(0, check);
    if (this->response.size() == 0)
    {
        this->_responseStatus = closeConnect;
    }
    if (this->_responseStatus == closeConnect)
        //close connection
}

void    appendClient::copyReq(char *req, int size)
{
    int i = 0;
    if (!this->_tmp.empty())
        this->_tmp.erase();
    while (i < size)
    {
        this->_tmp.push_back(req[i]);
        i++;
    }
}

std::string::size_type appendClient::checkCRLForChunk(std::string test)
{
    std::string::size_type pos = this->_header.find(test);
    if (pos != std::string::npos)
        return (pos);
    return (-1);
}

void    appendClient::getBodyRest()
{
    //check pos of CRLF and get the beginning of the body
    std::string::size_type pos = this->_header.find(CRLF);

    if (pos != std::string::npos)
    {
        //extract body
        std::string res = this->_header.substr(pos + 4);
        this->_body.append(res);
        this->_header.erase(pos);
    }
}

void    appendClient::recvBody(std::string req)
{
    this->setBody(req);
    if (this->_bodyType == contentlength)
    {
        if (getContentLengthValue <= this->_body.size())
        {
            this->_responseStatus = responseGo;
        }
    }
    else if (this->_bodyType == chunked)
    {
        if (this->checkCRLForChunk(lastChunk))
        {
            this->parseChunked(req);
            this->_responseStatus = responseGo;
        }
        else
            this->parseChunked(req);
    }
    else
    {
        //error
    }
    
}

void    appendClient::recvHead()
{
    int check;
    char tmp[BUFFER_SIZE];
    check = recv(this->_clientFd, tmp, BUFFER_SIZE, 0);
    if (check < 0)
    {
        perror("recv");
        //exit or return 
    }
    appendClient::copyReq(tmp, BUFFER_SIZE);
    if (this->getHeadStatus() == endOfHeader)
    {
        appendClient::recvBody(this->_tmp);
    }
    else if (this->getHeadStatus() != endOfHeader)
    {
        this->_header.append(this->_tmp);

        //check for CRLF at the end of the string
        if (this->checkCRLForChunk(CRLF) >= 0)
            {
                this->setHeadStatus(endOfHeader);
                this->getBodyRest();
                //pass it to parser
                this->_header.parse();
                //check body type , if bodytype is not chunked, content length => error
                if (this->_bodyType == chunked && this->checkCRLForChunk(lastChunk))
            {
                this->parseChunked(this->_body);
                this->_responseStatus = responseGo;
            }
            }
        else //error cases
        {
            //exit or return or throw exception
        }
    }
    if (this->_responseStatus == responseGo)
    {
        //get response and send it 
    }
}

void    appendClient::parseChunked(std::string& chunkedData)
{
     int chunkflag = 0;
    std::istringstream iss(chunkedData);
    std::string res;

    std::string line;
    std::size_t chunkSize;
    std::string chunk = "";

    // Read and process each chunk
    while (std::getline(iss, line)) {
        if (chunkflag == 0)
        {
        std::istringstream chunkSizeStream(line);
        if (!(chunkSizeStream >> std::hex >> chunkSize)) {
            std::cerr << "Error: Invalid chunk size." << std::endl;
            break ;
        }
        else
        {
            chunkflag = 1;
            continue;
        }
        }

        if (chunkSize == 0) {
            break;  // Reached the end of the chunked data
        }

        if (chunkflag == 1)
        {   
            std::stringstream chunkStream(line);
            chunkStream >> chunk;
            if (chunk.size() != chunkSize)
            {
                std::cout << "Error size doesn't match" << std::endl;
                break;
            }
            else
            {
                res.append(chunk);
                chunk = "";
            }
            chunkflag = 0;
        }
    }
    this->_body.clear();
    this->_body.append(res);
}
