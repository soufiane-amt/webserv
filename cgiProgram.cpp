/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgiProgram.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:16:53 by fech-cha          #+#    #+#             */
/*   Updated: 2023/05/23 18:22:27 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgiProgram.hpp"

    //idk if we gonna need this one
	// HTTP_COOKIE="//get the cookie from the header 

    //cgi_cmd = cgiPath + file to set in execve



CGI::CGI()
{

}

CGI::~CGI()
{
    
}

//expect &req in arg
void    CGI::setEnvCgi()
{
    this->_env.push_back("SERVER_NAME=" + getServerNameFromReq());
    this->_env.push_back("SERVER_SOFTWARE=webserv");
    this->_env.push_back("SERVER_PORT="+getPortFromReq());
    this->_env.push_back("REQUEST_METHOD="+getReqMeth());
    this->_env.push_back("GATEWAY_INTERFACE=CGI");
    this->_env.push_back("SERVER_PROTOCOL=HTTP1.1");
    this->_env.push_back("CONTENT_TYPE="+getContentTypeFromReq());
    this->_env.push_back("CONTENT_LENGTH="+getContentLength());
    this->_env.push_back("DOCUMENT_ROOT="+getRootDirectory());
    this->_env.push_back("QUERY_STRING="+getQueryStr());
    this->_env.push_back("SCRIPT_FILENAME="+getCGIScriptName());
}

//check cgi scripts extensions
void    CGI::checkCGI()
{
    
}

void    CGI::handleCGI()
{

    char buffer[1024];
    int fd[2];
    int check = 0;

    //store output of cgi script
    std::string cgiResp;

    //set cgi cmd
    //set cgi env
    //content type
    //content length

    //convert cgi strings to char **
    
    
    //execution
    int tmp = dup(0);
    if (pipe(fd) < 0)
    {
        //set http return status to 502
        return ;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        //set http return status to 502
        return ;
    }
    
    if (pid == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        //create a file to store the body of the http request

        //The CGI should be run in the correct directory for relative path file access.
        // changes the current working directory of the child process to the root directory of the server
        //chdir to the root of the cgi
        

        char *const args[] = {"python3", "cgi_exemple.py", NULL};
        //change to directory of the cgi
        
        if (execve("/usr/bin/python3", args, NULL) < 0)
            exit(EXIT_FAILURE);
    }
    waitpid(pid, &check, 0);

    if (pid > 0)
    {
        close(fd[1]);
        int nbytes = read(fd[0], buffer, sizeof(buffer));
        buffer[nbytes] = '\0';
    }

    
    std::cout << buffer << std::endl;
}

int main()
{
    CGI cg;

    cg.handleCGI();

    return(0);
}