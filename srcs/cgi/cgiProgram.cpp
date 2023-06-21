/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgiProgram.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:16:53 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/21 13:49:17 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgiProgram.hpp"

	// HTTP_COOKIE="//get the cookie from the header 

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

CGI::CGI()
{

}

CGI::~CGI()
{
    
}

int CGI::hasPythonOrPhpExtension(const std::string& filename) {
    std::string extension = filename.substr(filename.length() - 3);

    for (std::string::iterator it = extension.begin(); it != extension.end(); ++it) {
        *it = std::tolower(static_cast<unsigned char>(*it));
    }

    if (extension == ".py")
        return 1;
    else if (extension == ".pl")
        return 2;
    return -1;
}

void    CGI::setCGIpath(std::string filename)
{   
    char *info = getenv("PATH_INFO");

    if (hasPythonOrPhpExtension(filename) == 1) {
        std::string exec = "/usr/local/bin/python3";
        std::string path = std::string(info) + filename;

        std::cerr << "path: " << path << std::endl;
        this->_cgi.push_back(exec);
        this->_cgi.push_back(path);
    } 
    else if (hasPythonOrPhpExtension(filename) == 2) {
        std::string exec = "/usr/bin/perl";
        std::string path = std::string(info) + filename;
    
        this->_cgi.push_back(exec);
        this->_cgi.push_back(path);
    }
}


int    CGI::handleCGI(std::string &body, std::string &cgiResp)
{

    extern char **environ;
    int check = 0;
    int fd[2];
    std::cout << "=> CGI" << std::endl;
    std::cout << getenv("PATH_INFO") << std::endl;
    
    //execution
    int tmp = dup(0);
    if (pipe(fd) < 0)
        return (-1);

    pid_t pid = fork();
    if (pid < 0)
        return (-1);

    if (pid == 0)
    {
        dup2(fd[1], 1);
		close(fd[1]);

        std::FILE* file;
        const char* name = "/tmp/.body";
        
        // Open the file in write/read mode, create if it doesn't exist
        file = std::fopen(name, "w+"); 

        if (file) 
        {
            // Write each character to the file
            for (size_t i = 0; i < body.size() ; ++i) {
                std::fputc(body[i], file);
            }
            std::rewind(file);
        }
        dup2(fileno(file), 0);
        // Close the file after writing
        std::fclose(file); 
        
        char *str = getenv("SCRIPT_FILENAME");
        std::string filename(str);
        this->setCGIpath(filename);

        //convert cgi strings to char **
        char    **cgiExec = convert_vector_to_char_array(this->_cgi);

        if (execve(cgiExec[0], cgiExec, environ) < 0)
            exit(EXIT_FAILURE);
            
        //free allocated memory
        freeConvertedArray(cgiExec,this->_cgi.size());
    }
    waitpid(pid, &check, 0);
    
    //checks if the child process was terminated by a signal
    if (WIFSIGNALED(check) || check != 0)
        return (-1);
    dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);

	char buffer[1];
	while (read(0, buffer, 1) > 0)
        cgiResp.push_back(buffer[0]);
    
	dup2(tmp, 0);
	close(tmp);
    return (1);
}
