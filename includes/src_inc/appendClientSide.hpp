/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appendClientSide.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:06:16 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/16 20:30:01 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPENDCLIENTSIDE_HPP
# define APPENDCLIENTSIDE_HPP

#include "pollingServ.hpp"
# define chunked 1
# define contentLength 2 
# define nobody 3
# define closeConnect 4
# define responseGo 5
# define lastChunk "0\r\n\r\n"
# define myCRLF "\r\n\r\n"
# define endOfBody 69
# define endOfHeader 420

class appendClient
{ 
    private:
    
        int64_t _time;
        
        //checking flags
        unsigned long        _contentLength;
        int         _checkHead;
        int         _checkBody;
        int         _bodyType;
        int         _responseStatus;
        
        //fd of the client
        int         _clientFd;
        
        std::string _tmp;
        std::string _header;
        std::string _body;
        std::string _httpRequest;
        std::vector<char> _httpRespond;
    public:
        appendClient();
        ~appendClient();
        
        
        // I/O methods for servers
        void    sendReq(int sockfd);
        void    recvHead();
        void    recvBody(std::string req);

        //getters & setters
        int     getClientFd(void);
        void    setClientFd(int fd);
        
        int     getHeadStatus();
        int     getBodyStatus();
        
        void    setHeadStatus(int head);
        void    setBodyStatus(int body);
        
        std::string getHeader();
        std::string getBody();

        void    setBody(std::string body);
        
        void                    parseChunked(std::string& chunkedData);
        void                    copyReq(char *req, int size);
        std::string::size_type  checkCRLForChunk(std::string test);
    
        void    getBodyType();
        void    getBodyRest();
        int     getResponseStat();
        void    setResponseStat(int stat);
        void    setHTTPRequest();
        std::string getHTTPRequest();
        void    getContentLength();
        std::vector<char> getHTTPResponse();
        void    setHTTPResponse(std::vector<char> res);

        void    setTime(int64_t t);
        int64_t getTime();

};

#endif