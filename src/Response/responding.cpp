/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responding.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:58:01 by samajat           #+#    #+#             */
/*   Updated: 2023/03/23 20:06:20 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "responding.hpp"
#include <string>
#include <fstream>


responsePreparation::responsePreparation(const http_message_t& request, const  statusCode_t& statusCode):_request(request), _statusCode(statusCode), _response("")
{
    if (_request.first["Method"] == "GET")
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
    _response += "HTTP/1.1 " + _statusCode;
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
    _response += CRLF;
    _response += get_file_content(_request.first["URI"]);
}

std::string responsePreparation::get_file_content(const std::string& uri)
{
    std::ifstream file(uri);
    std::string content;
    std::string line;

    if (file.is_open())
    {
        while (getline(file, line))
            content += line + "\n";
        file.close();
    }
    return content;
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