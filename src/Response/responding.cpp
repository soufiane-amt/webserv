/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responding.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:58:01 by samajat           #+#    #+#             */
/*   Updated: 2023/05/25 14:30:30 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "responding.hpp"
#include <string>


responsePreparation::responsePreparation(const http_message_t& request, const  StatusCode& statusCode):_request(request), _statusCode(statusCode)
{
    _init();
    // check_if_cgi(_request.header["URI"]);
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
        size_t body_size = (_response.end() - it - 4);//the 4 is for the CRLF CRLF
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
        appropriate_page = utility::list_directory(_request.header["URI"], _request.targeted_Location);
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
    prepare_last_modified();
    prepare_eTag();
    prepare_connection ();
    if (_statusCode.get_status_code() == OK)
    {
        prepare_body();//this function must always be called first than the next one
        prepare_meta_body_data();
    }
    else
        add_CRLF();
}

void    responsePreparation::exceute_post()
{
    //output an std::map of the form data
    // std::map<std::string, std::string> form_data = utility::decode_x_www_form_urlencoded_format(_request.body);

    // for(std::map<std::string, std::string>::iterator it = form_data.begin(); it != form_data.end(); ++it)
    // {
    //     std::cout << it->first << " => " << it->second << '\n';
    // }
    // std::string command;
    // command = _request.body.substr(_request.body.find('=') + 1);
    // command[command.find('+')] = ' ';
    // system(command.c_str());
    
    // prepare_statusLine();
    // add_CRLF();
    // std::vector <char> tmp = utility::get_file_content("www/command.html");
    // _response.insert(_response.end(), tmp.begin(), tmp.end());
    
    // prepare_server_name();
    // prepare_date();
    
    // prepare_location();
    // prepare_body();
    // prepare_meta_body_data();

}



void    responsePreparation::exceute_delete()
{
    //Check if the file to delete is the sameone in random/ zone
    //if yes, then delete it
    //else, return 403 forbidden
    
    if ()
    {
        std::string command;
        command = "rm " + _request.header["URI"];
        system(command.c_str());
        _statusCode.set_status_code(OK);
    }
    else
        _statusCode.set_status_code(FORBIDDEN);
    prepare_statusLine();
    prepare_server_name();
    prepare_date();
    prepare_location();
    prepare_body();
    prepare_meta_body_data();
}


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


void responsePreparation::_init()
{
    _dir_listing_on = (utility::check_file_or_directory(_request.header.at("URI")) == S_DIRECTORY && 
                        utility::search_directive("autoindex", parser.get_server_locations(0)[_request.targeted_Location]) == "on");
    _allowed_methods = utility::search_directive("allow", parser.get_server_locations(0)[_request.targeted_Location]);
    // _execute_cgi    = (_request.header.at("URI") == "www/cgi/" + FIRST_SCRIPT || _request.header.at("URI") == "www/cgi/" + SECOND_SCRIPT)
    // std::cout << _request.header.at("URI") << std::endl;
}

void responsePreparation::prepare_eTag()
{
    std::string file_hash = utility::get_file_hash(_request.header["URI"]);
    if (_request.header.find("If-None-Match") != _request.header.end() && _request.header["If-None-Match"] == file_hash)
        change_status_line(NOT_MODIFIED);
    std::string eTag = "ETag: " + file_hash;
    _response.insert(_response.end(), eTag.begin(), eTag.end());
    add_CRLF();
}

void    responsePreparation::prepare_last_modified()
{
    std::string last_modified =  utility::get_last_modified(_request.header["URI"]);
    if (_request.header.find("If-Modified-Since") != _request.header.end() && _request.header["If-Modified-Since"] == last_modified)
        change_status_line(NOT_MODIFIED);
    last_modified.insert(0, "Last-Modified: ");
    _response.insert(_response.end(), last_modified.begin(), last_modified.end());
    add_CRLF();
}



void    responsePreparation::prepare_connection()
{
    std::string connection = "Connection: ";
    if (!_statusCode.is_error_status() && _request.header.find("Connection") != _request.header.end())
        connection += _request.header["Connection"];
    else
        connection += "close";
    _response.insert(_response.end(), connection.begin(), connection.end());
    add_CRLF();
}

void        responsePreparation::change_status_line(const char *status_code)
{
    this->_statusCode = StatusCode(status_code);
    _response.erase(_response.begin(), _find_in_response(CRLF));
    std::string status_line = "HTTP/1.1 " + std::string(status_code);
    _response.insert(_response.begin(), status_line.begin(), status_line.end());
}

bool        responsePreparation::file_is_deletable(const std::string& file_path)
{
    // check if that file exits and it is the same one as the one in the random zone
    
    //if not, return 403 forbidden
    static std::string random_path = "www/random/";
    static std::vector<std::string> random_files =  utility::get_directory_files (random_path);

    for (size_t i = 0; i < random_files.size(); i++)
        if (random_files[i] == file_path)
            return true;
    
    return false;
}

// #include <unistd.h>


// bool             responsePreparation::check_if_cgi(std::string file_path)
// {
//     static std::string cgi_path = "www/cgi/";


//     //check if the path leads to the right cgi script

//     size_t pos = file_path.rfind("/");
//     // if (cgi_path == )
//     // if (file_path.find(cgi_path) != std::string::npos)
//     // {
//     //     std::string cgi_script = file_path.substr(file_path.find(cgi_path) + cgi_path.size());
//     //     std::string cgi_script_path = cgi_path + cgi_script;
//     //     if (access(cgi_script_path.c_str(), F_OK) == -1)
//     //         change_status_line(NOT_FOUND);
//     //     else if (access(cgi_script_path.c_str(), X_OK) == -1)
//     //         change_status_line(FORBIDDEN);
//     //     return true;
//     // }
//     return false;
// }