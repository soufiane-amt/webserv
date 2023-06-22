
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

#include "pollingServ.hpp"


int toDec(std::string &hexString)
{
    int result = 0;
    int multiplier = 1;

    for (int i = hexString.length() - 1; i >= 0; --i) {
        char c = hexString[i];
        int digit;

        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'A' && c <= 'F') {
            digit = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'f') {
            digit = c - 'a' + 10;
        } else {
            return -1;  // Not a valid hexadecimal number
        }

        result += digit * multiplier;
        multiplier *= 16;
    }

    return result;
}

appendClient::appendClient(): _contentLength(-1), _checkHead(-1), _checkBody(-1), _bodyType(-1), _responseStatus(-1),  _clientFd(-69)
{
    
}

appendClient::~appendClient()
{
    std::cout << "client destructor" << std::endl;
}

void    appendClient::setTime(int64_t t)
{
    this->_time = t;
}

int64_t appendClient::getTime()
{
    return (this->_time);
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

void    appendClient::fillBody(std::string body)
{
    for(size_t i = 0; i < body.size(); i++)
        this->_body.push_back(body[i]);
}

int appendClient::getResponseStat()
{
    return (_responseStatus);
}

void appendClient::setResponseStat(int stat)
{
    this->_responseStatus = stat;
}

void    appendClient::setHTTPResponse(std::vector<char> res)
{
    this->_httpRespond = res;
}

std::vector<char> appendClient::getHTTPResponse()
{
    return (this->_httpRespond);
}

void    appendClient::sendReq(int sockfd)
{
    int check;
    std::vector<char>::iterator hold = this->_httpRespond.begin();
    check = send(sockfd, this->_httpRespond.data(), this->_httpRespond.size(), 0);
    if (check < 0)
    {
        perror("send");
        // error
    }
    if (this->_httpRespond.size() > 0)
        this->_httpRespond.erase(hold, hold + check);
    if (this->_httpRespond.size() == 0)
        this->setResponseStat(closeConnect);
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
    if (this->getHeadStatus() != endOfHeader)
    {
        for (size_t j = 0 ; j < this->_tmp.size(); j++)
            this->_header.push_back(this->_tmp[j]);
    }
}

std::string::size_type appendClient::checkCRLForChunk(std::string test)
{
    if (test == myCRLF)
    {
        std::string::size_type pos = this->_header.find(test);
        if (pos != std::string::npos)
            return (pos);
    }
    if (test == lastChunk)
    {
        std::string::size_type pos = this->_body.find(test);
        if (pos != std::string::npos)
            return (pos);
    }
    return (-1);
}

void    appendClient::getBodyRest()
{
    //check pos of CRLF and get the beginning of the body
    std::string::size_type pos = this->_header.find(myCRLF);
    if (pos != std::string::npos)
    {
        //extract body
        for (std::string::size_type i = pos + 4; i < this->_header.size(); i++)
            this->_body.push_back(this->_header[i]);
        this->_header.erase(pos + 4);
        if ((unsigned long)this->_contentLength <= this->_body.size())
            this->_checkBody = endOfBody;
    }
}

void    appendClient::getBodyRestChunk()
{
    //check pos of CRLF and get the beginning of the body
    std::string::size_type pos = this->_header.find(myCRLF);
    if (pos != std::string::npos)
    {
        //extract body
        for (std::string::size_type i = pos + 4; i < this->_header.size(); i++)
            this->_body.push_back(this->_header[i]);
        this->_header.erase(pos + 4);
        if (this->checkCRLForChunk(lastChunk) != std::string::npos)
        {
            this->resolveChunk(this->_body);
            this->_responseStatus = responseGo;
        }
    }
}

void    appendClient::recvBody(std::string req)
{
    this->fillBody(req);
    if (this->_bodyType == contentLength)
    {
        if ((unsigned long)this->_contentLength <= this->_body.size())
            this->_checkBody = endOfBody;
    }
    else if (this->_bodyType == chunked)
    {
        if (this->checkCRLForChunk(lastChunk) != std::string::npos)
        {
            this->resolveChunk(this->_body);
            this->_responseStatus = responseGo;
        }
    }
    else
    {
        this->_bodyType = nobody;
        this->_body.erase();
        this->setHTTPRequest();
        this->_responseStatus = responseGo;
    }
}

void    appendClient::getBodyType()
{
    std::string::size_type content_length = this->_header.find("Content-Length");
    std::string::size_type transfer_chunked = this->_header.find("Transfer-Encoding: chunked");
    if (content_length != std::string::npos) {
        this->_bodyType = contentLength;
    } else if (transfer_chunked != std::string::npos){
        this->_bodyType = chunked;
    }
    else
        this->_bodyType = nobody;
}

void    appendClient::setHTTPRequest()
{
    this->_httpRequest.append(this->_header);
    for (size_t i = 0; i < this->_body.size(); i++)
        this->_httpRequest.push_back(this->_body[i]);
}

std::string appendClient::getHTTPRequest()
{
    return (this->_httpRequest);
}

void    appendClient::getContentLength()
{
   std::string::size_type contentLengthPos = this->_header.find("Content-Length:");
    if (contentLengthPos != std::string::npos) {
        contentLengthPos += 16; // Move to the end of "Content-Length: "
        std::string::size_type endPos = this->_header.find("\r\n", contentLengthPos);
        if (endPos != std::string::npos) {
            std::string lengthStr = this->_header.substr(contentLengthPos, endPos - contentLengthPos);

            // Check if the length string contains only digits
            for (std::string::size_type i = 0; i < lengthStr.length(); ++i) {
                if (!std::isdigit(lengthStr[i])) {
                    this->_contentLength = -1;
                }
            }
            this->_contentLength = std::atol(lengthStr.c_str());
        }
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
    appendClient::copyReq(tmp, check);
    if (this->getHeadStatus() == endOfHeader && this->_bodyType != nobody)
    {
        this->getBodyType();
        appendClient::recvBody(this->_tmp);
    }
    if (this->getHeadStatus() != endOfHeader)
    {
        //check for CRLF at the end of the string
        if (this->checkCRLForChunk(myCRLF) >= 0)
            {
                this->setHeadStatus(endOfHeader);
                if (this->getHeadStatus() == endOfHeader)
                    this->getBodyType();
                if (this->_bodyType == contentLength)
                {
                    this->getContentLength();
                    if (this->_contentLength > 0)
                        this->getBodyRest();
                    else if (this->_contentLength < 0)
                    {
                        this->getBodyRest();
                        this->_bodyType = nobody;
                    }
                }
                if (this->_bodyType == chunked)
                    this->getBodyRestChunk();
                if (this->_bodyType == chunked && this->checkCRLForChunk(lastChunk) != std::string::npos)
                    this->resolveChunk(this->_body);
            }
    }
    if (this->getHeadStatus() == endOfHeader && this->_bodyType == nobody)
    {
        this->_header.append(myCRLF);
        this->_httpRequest = this->_header;
        this->_responseStatus = responseGo;
    }
    else if (this->getHeadStatus() == endOfHeader && this->getBodyStatus() == endOfBody)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
    {
        this->setHTTPRequest();
        this->_responseStatus = responseGo;
    }
}

void    appendClient::resolveChunk(std::string &body)
{
    std::string size;
    std::string result;
    size_t cSize = -1;

    while(cSize != 0)
    {
        size_t pos = body.find(newline);
        if (pos == std::string::npos)
            break;
        
        //clear string before the iteration (it can come with garbage value)
        size.clear();
        for (size_t i = 0; i < pos ; i++)
            size.push_back(body[i]);
        
        cSize = toDec(size);
        if (static_cast<int>(cSize) == -1 || cSize > body.size())
        {
            this->_body.clear();
            this->_bodyType = nobody;
            return ;
        }
        if (cSize == 0)
            break;

        body.erase(0, pos + 2);

        for (size_t i = 0; i < cSize; i++)
            result.push_back(body[i]);

        body.erase(0, cSize);
        body.erase(0, 2);
    }
    this->_body.clear();
    for (size_t i = 0 ; i < result.size(); i++)
        this->_body.push_back(result[i]);
    this->_checkBody = endOfBody;
}
