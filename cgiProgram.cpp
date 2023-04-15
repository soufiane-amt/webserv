/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgiProgram.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:16:53 by fech-cha          #+#    #+#             */
/*   Updated: 2023/04/14 00:59:53 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgiProgram.hpp"

CGI::CGI()
{
    this->_name = "/Users/fech-cha/Desktop/webserv/cgi_exemple.py";
}

CGI::~CGI()
{
    
}


//check cgi scripts extensions
void    CGI::checkCGI()
{
    
}

void    CGI::handleCGI()
{
    char buffer[1024];
    int fd[2];
    pipe(fd);

    pid_t pid = fork();
    
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

         char *const args[] = {"python3", "cgi_exemple.py", NULL};
        execve("/usr/bin/python3", args, NULL);
    }

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