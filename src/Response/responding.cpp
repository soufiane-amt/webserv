/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responding.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:58:01 by samajat           #+#    #+#             */
/*   Updated: 2023/03/25 15:52:48 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "responding.hpp"
#include <string>


responsePreparation::responsePreparation(const http_message_t& request, const  StatusCode& statusCode):_request(request), _statusCode(statusCode), _response("")
{
    if(_statusCode.is_error_status())
        sendError();
    else if (_request.first["Method"] == "GET")
        exceute_get();
    else if (_request.first["Method"] == "POST")
        exceute_post();
    else if (_request.first["Method"] == "DELETE")
        exceute_delete();
    // else
    //     throw (exception("Method not implemented")
}

responsePreparation::response_t responsePreparation::get_response() const
{
    return _response;
}

void responsePreparation::prepare_statusLine()
{
    _response += "HTTP/1.1 " + std::string(_statusCode.what());
    _response += CRLF;
}

void responsePreparation::prepare_other_headers()
{
    _response += "Server: Webserv/1.0";
    _response += CRLF;
    _response += "Date: " + utility::get_date();
    _response += CRLF;
    _response += "Content-Type: text/html";
    _response += CRLF;
}

void responsePreparation::prepare_body() //I'm gonna assume for now that the uri is a file
{
    if (_statusCode.is_error_status())
    {
        std::string appropriate_page = _statusCode.get_associated_page();
        _response += "Content-Length: " + std::to_string(appropriate_page.length());
        _response += CRLF;
        _response += CRLF;
        std::cout << appropriate_page << std::endl;
        _response += appropriate_page;
        return;
    }
    _response += CRLF;
    std::cout << _request.first["URI"] << std::endl;
    _response += utility::get_file_content(_request.first["URI"]);
}


// void responsePreparation::prepare_content_length()
// {
//     _response += "Content-Length: " + std::to_string(_response.length());
//     _response += CRLF;
// }

void    responsePreparation::exceute_get()
{
    prepare_statusLine();
    prepare_other_headers();
    prepare_body();
}

void    responsePreparation::exceute_post()
{
}

void    responsePreparation::exceute_delete()
{
}


void   responsePreparation::sendError()
{
    prepare_statusLine();
    prepare_other_headers();
    prepare_body();
}