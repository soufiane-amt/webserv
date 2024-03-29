/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responding.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:58:01 by samajat           #+#    #+#             */
/*   Updated: 2023/06/24 00:06:59 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responding.hpp"
#include <string>


responsePreparation::responsePreparation(const http_message_t& request, int targeted_serv,const  StatusCode& statusCode):_request(request), _statusCode(statusCode)
{
    _init(targeted_serv);
    if(_statusCode.is_error_status())
        prepare_error_response();
    else if (_request.header["Method"] == "GET")
        exceute_get();
    else if (_request.header["Method"] == "POST")
        exceute_post();
    else if (_request.header["Method"] == "DELETE")
        exceute_delete();
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
    if (_statusCode.get_status_code() == METHOD_NOT_ALLOWED)
    {
        std::string allow = "Allow: "+ _allowed_methods;
        _response.insert(_response.end(), allow.begin(), allow.end());
        add_CRLF();
    }
}


void responsePreparation::prepare_body() //I will change this to cases later 
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
    else if (_request.header["Method"] == "DELETE")
    {
        std::vector <char> tmp = utility::get_file_content("www/delete_msg.html");
        _response.insert(_response.end(), tmp.begin(), tmp.end());
    }
    else
    {
        std::vector <char> tmp = utility::get_file_content(_request.header["URI"]);
        _response.insert(_response.end(), tmp.begin(), tmp.end());
    }
}

void    responsePreparation::exceute_get()
{
    if (utility::ressource_is_cgi(_request.header["URI"]))
    {
        set_env_variables_for_cgi();
        execute_cgi();
        return;
    }
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

void    responsePreparation::execute_cgi()
{
    CGI cgi;
    std::string resp;

    std::string body = _request.body;
    if (cgi.handleCGI(_request.body,resp) == -1)
    {
        _statusCode = StatusCode(BAD_GATEWAY);
        prepare_error_response();
        return;
    }
        
    _response.insert(_response.end(), resp.begin(), resp.end());
}

void    responsePreparation::exceute_post()
{
    if (utility::ressource_is_cgi(_request.header["URI"]))
    {
        set_env_variables_for_cgi();
        execute_cgi();
        return;
    }
    _statusCode = StatusCode(NOT_FOUND);
    prepare_error_response();
}



bool        responsePreparation::file__delet_is_allowed(const std::string& file_path)
{
    // check if that file exits and it is the same one as the one in the random zone
    
    //if not, return 403 forbidden
    static std::string random_path = "www/random/";
    static std::vector<std::string> random_files =  utility::get_directory_files (random_path);

    for (size_t i = 0; i < random_files.size(); i++)
    {
        if (utility::arePathsSame((random_path + random_files[i]).c_str(), file_path.c_str()))
            return true;
    }
    return false;
}

void    responsePreparation::exceute_delete()
{
    //Check if the file to delete is the sameone in random/ zone
    //here I check if the request to delete a file is allowed by my glorious server

    if (file__delet_is_allowed(_request.header.at("URI")))
    {
        if (std::remove(_request.header.at("URI").c_str()) != 0)
            this->_statusCode = StatusCode(INTERNAL_SERVER_ERROR);
    }
    else
        this->_statusCode = StatusCode(FORBIDDEN);
    if (_statusCode.get_status_code() == OK)
    {
        prepare_statusLine();
        prepare_server_name();
        prepare_date();
        prepare_location();
        add_CRLF();
        prepare_body();
        prepare_meta_body_data();
    }
    else
        prepare_error_response();
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


void responsePreparation::_init(int targeted_serv)
{
    
    id = targeted_serv;
    if (!_statusCode.is_error_status())
    {
        server_locations = parser.get_server_locations(targeted_serv);
        _dir_listing_on = (utility::check_file_or_directory(_request.header.at("URI")) == S_DIRECTORY && 
                            utility::search_directive("autoindex", server_locations[_request.targeted_Location], id) == "on");
    }
    else
    {
        _allowed_methods = utility::search_directive("allow", server_locations[_request.targeted_Location], id);
        _allowed_methods == "" ? _allowed_methods = "GET, POST, DELETE" : _allowed_methods;
    }
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


void        initialize_variable_2_empty()
{
    setenv("SERVER_NAME", "", 1);
    setenv("REQUEST_METHOD", "", 1);
    setenv("QUERY_STRING", "", 1);
    setenv("PATH_INFO", "", 1);
    setenv("UPLOAD_DIR", "", 1);
    setenv("CONTENT_TYPE", "", 1);
    setenv("CONTENT_LENGTH", "", 1);
    setenv("SCRIPT_FILENAME", "", 1);
    setenv("SERVER_PORT", "", 1);
    setenv("SERVER_SOFTWARE", "", 1);
    setenv("GATEWAY_INTERFACE", "", 1);
    setenv("SERVER_PROTOCOL", "", 1);
    setenv("HTTTP_COOKIE", "", 1);
}
void        responsePreparation::set_env_variables_for_cgi()
{
    std::string software = "webserv";
    std::string gateway = "CGI";
    std::string protocol = "HTTP1.1";
    std::string port  = utility::search_directive("listen", parser.get_server_locations(id)[_request.targeted_Location], id);
    
    initialize_variable_2_empty () ;
    setenv("REDIRECT_STATUS","200",1);
    setenv("SERVER_NAME", parser.get_server_directives(id, "server_name").c_str(), 1);
    setenv("REQUEST_METHOD", _request.header.at("Method").c_str(), 1);
    setenv("QUERY_STRING", _request.header.at("QUERY_STRING").c_str(), 1);
    
    try{setenv("PATH_INFO", parser.get_server_directives(id, "cgi").c_str(),1);}
    catch(const std::out_of_range& e){}
    
    try{setenv("PATH_INFO", parser.get_server_directives(id, "cgi").c_str(),1);}
    catch(const std::out_of_range& e){}
    
    try{setenv("UPLOAD_DIR", parser.get_server_directives(id, "upload").c_str(),1);}
    catch(const std::out_of_range& e){}
    
    try{setenv("CONTENT_TYPE", _request.header.at("Content-Type").c_str(), 1);}
    catch(const std::out_of_range& e){}
    
    try{setenv("CONTENT_LENGTH", _request.header.at("Content-Length").c_str(), 1);}
    catch(const std::out_of_range& e){}
    
    try{setenv("HTTP_COOKIE", _request.header.at("Cookie").c_str(), 1);}
    catch(const std::out_of_range& e){}
    
    std::string script_name = _request.header.at("URI");
    setenv("SCRIPT_FILENAME", script_name.substr(script_name.rfind('/')).c_str(), 1);
    setenv("SERVER_PORT", port.c_str(), 1);
    setenv("SERVER_SOFTWARE", software.c_str(), 1);
    setenv("GATEWAY_INTERFACE", gateway.c_str(),1);
    setenv("SERVER_PROTOCOL", protocol.c_str(),1);
    setenv("SERVER_PROTOCOL", protocol.c_str(),1);
    
    }
