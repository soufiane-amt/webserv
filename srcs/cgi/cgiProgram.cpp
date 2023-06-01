/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgiProgram.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:16:53 by fech-cha          #+#    #+#             */
/*   Updated: 2023/05/25 11:15:18 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgiProgram.hpp"

    //idk if we gonna need this one
	// HTTP_COOKIE="//get the cookie from the header 

    //cgiExec = usr/bin/executable + path
CGI::CGI()
{

}

CGI::~CGI()
{
    
}

// Helper function to add environment variables to the vector
void addToEnvVector(std::vector<std::string>& vec, const std::string& key, const std::string& value)
{
    vec.push_back(key + "=" + value);
}

//expect &req in arg
void    CGI::setEnvCgi()
{
    addToEnvVector(this->_env, "SERVER_NAME", getServerNameFromReq());
    addToEnvVector(this->_env, "SERVER_SOFTWARE", "webserv");
    addToEnvVector(this->_env, "SERVER_PORT", getPortFromReq());
    addToEnvVector(this->_env, "REQUEST_METHOD", getReqMeth());
    addToEnvVector(this->_env, "GATEWAY_INTERFACE", "CGI");
    addToEnvVector(this->_env, "SERVER_PROTOCOL", "HTTP1.1");
    addToEnvVector(this->_env, "CONTENT_TYPE", getContentTypeFromReq());
    addToEnvVector(this->_env, "CONTENT_LENGTH", getContentLength());
    addToEnvVector(this->_env, "DOCUMENT_ROOT", getRootDirectory());
    //get or post (body)
    addToEnvVector(this->_env, "QUERY_STRING", getQueryStr());
    addToEnvVector(this->_env, "SCRIPT_FILENAME", getCGIScriptName());
}

//expect &req in arg
void    CGI::setCGIpath()
{   
    //retrieve it from the config file
    std::string exec = "/usr/local/bin/python3";
    //retrieve path of the script
    std::string path = "cgi-bin/todo.py";
    
    this->_cgi.push_back(exec);
    this->_cgi.push_back(path);
}

//check cgi scripts extensions
void    CGI::checkCGI()
{
    
}

void    CGI::handleCGI()
{
    int check = 0;
    int fd[2];

    //store output of cgi script
    std::string cgiResp;

    //set cgi 
    this->setCGIpath();
    //set cgi env
    this->setEnvCgi();

    //convert cgi strings to char **
    char    **cgiEnv = convert_vector_to_char_array(this->_env);
    char    **cgiExec = convert_vector_to_char_array(this->_cgi);
    //cgiExec[0] = "python3" cgiExec[1] = "todo.py"
    
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
        std::FILE *tempStore;
		tempStore = tmpfile();
		
    	if (tempStore) 
        {
            //get the body of the http request
			std::string body = getHTTPBody();
            //null terminate the string in char *
        	std::fprintf(tempStore, "%s", body.c_str());
            std::fseek(tempStore, 0, SEEK_SET);
    	}

		dup2(fileno(tempStore), 0);
		std::fclose(tempStore);

        //The CGI should be run in the correct directory for relative path file access.
        // changes the current working directory of the child process to the root directory of the server
        //chdir to the root of the cgi

        //location of the script
        std::string location;
        if (chdir(location.c_str()) < 0)
        {
            //set http return status to 502
            return;
        }
        //alarm 

        // char *const args[] = {"python3", "cgi_exemple.py", NULL};
        if (execve(cgiExec[0], cgiExec, cgiEnv) < 0)
            exit(EXIT_FAILURE);
    }
    waitpid(pid, &check, 0);
    //checks if the child process was terminated by a signal
    if (WIFSIGNALED(check) || check != 0)
    {
        //set http return status to 502
        return ;
    }
    dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);

	char buffer[1];
	while (read(0, buffer, 1) > 0)
	   cgiResp.append(buffer, 1);

	dup2(tmp, 0);
	close(tmp);

    int getSize;
	freeConvertedArray(cgiEnv,getSize);
	freeConvertedArray(cgiExec,getSize);

    //parse the cgiResp, and generate HTTP Response (HEADER + BODY)
    
}
