/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responding.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:58:01 by samajat           #+#    #+#             */
/*   Updated: 2023/04/10 17:51:18 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "responding.hpp"
#include <string>


responsePreparation::responsePreparation(const http_message_t& request, const  StatusCode& statusCode):_request(request), _statusCode(statusCode)
{
    init_dir_listing();
    if(_statusCode.is_error_status())
        prepare_error_response();
    else if (_request.header["Method"] == "GET")
        exceute_get();
    // else if (_request.header["Method"] == "POST")
    //     exceute_post();
    // else if (_request.header["Method"] == "DELETE")
    //     exceute_delete();
}


std::vector<char>& responsePreparation::get_response()
{
    return _response;
}

void responsePreparation::prepare_statusLine()
{
    std::string statusLine =  "HTTP/1.1 " + std::string(_statusCode.what());
    statusLine += CRLF;
    _response.insert(_response.end(), statusLine.begin(), statusLine.end());
}


void    responsePreparation::add_CRLF()
{
    static std::string crlf = CRLF;
    _response.insert(_response.end(), crlf.begin(), crlf.end());
    
}


void responsePreparation::prepare_server_name()
{
    std::string server_name = "Server: Webserv/1.0";
    _response.insert(_response.end(), server_name.begin(), server_name.end());
    add_CRLF();
}

void responsePreparation::prepare_date()
{
    std::string date = "Date: " + utility::get_date();
    _response.insert(_response.end(), date.begin(), date.end());
    add_CRLF();
}

void responsePreparation::prepare_location()
{
    if (_statusCode.get_redir_location() != "")
    {
        std::string location = "Location: " + _statusCode.get_redir_location();
        _response.insert(_response.end(), location.begin(), location.end());
        add_CRLF();
    }
}

void responsePreparation::prepare_content_length(response_t::iterator& it)
{
    if (_response.end() != it)
    {
        std::string  content_length = CRLF "Content-Length: ";
        size_t body_size = (_response.end() - it - 4);
        if (body_size != 0)
        {
            content_length  += std::to_string(body_size);
            it = _response.insert(it, content_length.begin(), content_length.end());
        }
    }
}


void responsePreparation::prepare_content_type(response_t::iterator& it)
{
    if (_response.end() != it)
    {
        std::string content_type = CRLF "Content-Type: ";
        if (!_statusCode.is_error_status() && _dir_listing_on == false)
            content_type += get_mime_type(_request.header["URI"]);
        else
            content_type += "text/html";
        it = _response.insert(it, content_type.begin(), content_type.end());
    }
}

void        responsePreparation::prepare_meta_body_data()
{
    response_t::iterator    it = _find_in_response(CRLF CRLF);
    prepare_content_length(it);
    prepare_content_type(it);
}

void responsePreparation::prepare_allow()
{
    
        std::cout << _statusCode.get_status_code() <<"\n";
    if (_statusCode.get_status_code() == METHOD_NOT_ALLOWED)
    {
        std::string allow = "Allow: "+ _allowed_methods + CRLF;
        _response.insert(_response.end(), allow.begin(), allow.end());
        add_CRLF();
    }
}


void responsePreparation::prepare_body() //I'm gonna assume for now that the uri is a file
{
    std::string appropriate_page ;

    add_CRLF();

    if (_statusCode.get_redir_location() != "") return;
    
    if (_statusCode.is_error_status())
    {
        appropriate_page = _statusCode.get_associated_page();
        _response.insert(_response.end(), appropriate_page.begin(), appropriate_page.end());
        return;
    }
    if (_dir_listing_on == true)//here we need to check if autoindex is on
    {
        appropriate_page = utility::list_directory(_request.header["URI"]);
        _response.insert(_response.end(), appropriate_page.begin(), appropriate_page.end());
    }
    else
    {
        std::vector <char> tmp = utility::get_file_content(_request.header["URI"]);
        _response.insert(_response.end(), tmp.begin(), tmp.end());
    }
}

void    responsePreparation::exceute_get()
{
    prepare_statusLine();
    prepare_server_name();
    prepare_date();
    prepare_location();
    prepare_body();
    prepare_meta_body_data();
}

void    responsePreparation::exceute_post()
{
    prepare_statusLine();
    prepare_server_name();
    prepare_date();
    prepare_location();
    prepare_body();
    prepare_meta_body_data();

}

// void    responsePreparation::exceute_delete()
// {
// }


void   responsePreparation::prepare_error_response()
{
    prepare_statusLine();
    prepare_server_name();
    prepare_date();
    prepare_allow();
    prepare_body();
    prepare_meta_body_data();
}



responsePreparation::response_t::iterator    responsePreparation::_find_in_response(const std::string& str)
{
    for (response_t::iterator it = _response.begin(); it != _response.end(); it++)
        if (*it == str[0])
            if (std::string(it, it + str.size()) == str)
                return it;
    return _response.end();
}



std::string responsePreparation::get_mime_type(const std::string& filename) {
    size_t idx = filename.rfind('.');
    if (idx != std::string::npos) {
        std::string extension = filename.substr(idx + 1);
        if (extension == "txt")
            return "text/plain";
        else if (extension == "html" || extension == "htm")
            return "text/html";
        else if (extension == "jpg" || extension == "jpeg")
            return "image/jpeg";
        else if (extension == "gif")
            return "image/gif";
        else if (extension == "png")
            return "image/png";
    }
    return "application/octet-stream";
}


void responsePreparation::init_dir_listing()
{
    // _dir_listing_on = (utility::check_file_or_directory(_request.header.at("URI")) == S_DIRECTORY && 
    //                     parser.get_server_locations(0).
    //                     find(_request.targeted_Location)->second.find("autoindex")->second == "on");
    _dir_listing_on = (utility::check_file_or_directory(_request.header.at("URI")) == S_DIRECTORY && 
                        utility::search_directive("autoindex", parser.get_server_locations(0)[_request.targeted_Location]) == "on");
    _allowed_methods = utility::search_directive("allow", parser.get_server_locations(0)[_request.targeted_Location]);
}
