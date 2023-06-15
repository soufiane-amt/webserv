/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgiProgram.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:16:53 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/15 17:30:06 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgiProgram.hpp"
#include <string>
#include <cstring>
#include <iostream>
#include <vector>

	// HTTP_COOKIE="//get the cookie from the header 

    //cgiExec = usr/bin/executable + path

char** convert_vector_to_char_array(std::vector<std::string>& vec) 
{
    char** arr = new char*[vec.size() + 1];
    for (size_t i = 0; i < vec.size(); ++i) {
        arr[i] = new char[vec[i].size() + 1];
        std::strcpy(arr[i], vec[i].c_str());
    }
    arr[vec.size()] = NULL;
    return arr;
}

//avoid memory leaks
void freeConvertedArray(char** array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        delete[] array[i];
    }
    delete[] array;
}


void    handleSignalTimeout(int signal)
{
    if (signal == SIGALRM)
    {
        std::cout << "Timeout occured!" << std::endl;
        exit (EXIT_FAILURE);
    }
}

CGI::CGI()
{

}

CGI::~CGI()
{
    
}

int hasPythonOrPhpExtension(const std::string& filename) {
    std::string extension = filename.substr(filename.length() - 3);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    if (extension == ".py")
        return (1);
    else if (extension == "php")
        return (2);
    return (-1);
}

void    CGI::setCGIpath(std::string filename)
{   
    if (hasPythonOrPhpExtension(filename) == 1) {
        std::string exec = "/usr/local/bin/python3";
        std::string path = "./www/cgi_files" + filename;
    
        this->_cgi.push_back(exec);
        this->_cgi.push_back(path);
    } 
    else if (hasPythonOrPhpExtension(filename) == 2) {
        std::cout << "The filename have a .php extension." << std::endl;
    }
    // else
        //error case    
}


void    CGI::handleCGI(std::string &body, std::string &cgiResp)
{
    extern char **environ;
    int check = 0;
    int fd[2];
    
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
            //null terminate the string in char *
        	std::fprintf(tempStore, "%s", body.c_str());
            
            //set the file position indicator of the temporary file back to the beginning
            std::fseek(tempStore, 0, SEEK_SET);
    	}
        //make the body as input 
		dup2(fileno(tempStore), 0);
		std::fclose(tempStore);

        //alarm 
        signal(SIGALRM, handleSignalTimeout);
        alarm(5);
        
        char *str = getenv("SCRIPT_FILENAME");
        std::string filename(str);
        this->setCGIpath(filename);

        //convert cgi strings to char **
        char    **cgiExec = convert_vector_to_char_array(this->_cgi);
        
        // char *const args[] = {"python3", "cgi_exemple.py", NULL};
        if (execve(cgiExec[0], cgiExec, environ) < 0)
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

    //free allocated memory
    // int getSize;
	// freeConvertedArray(cgiEnv,getSize);
	// freeConvertedArray(cgiExec,getSize);

    //parse the cgiResp, and generate HTTP Response (HEADER + BODY)
    
    std::cout << "Printing Response:" <<std::endl;
    std::cout << cgiResp << std::endl;

    
}
