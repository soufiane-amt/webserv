/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgiProgram.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:16:53 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/07 14:31:10 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cgiProgram.hpp"

// 	// HTTP_COOKIE="//get the cookie from the header 

//     //cgiExec = usr/bin/executable + path

// void    handleSignalTimeout(int signal)
// {
//     if (signal == SIGALRM)
//     {
//         std::cout << "Timeout occured!" << std::endl;
//         exit (EXIT_FAILURE);
//     }
// }

// CGI::CGI()
// {

// }

// CGI::~CGI()
// {
    
// }

// //expect &req in arg
// void    CGI::setCGIpath()
// {   
//     //retrieve it from the config file
//     std::string exec = "/usr/local/bin/python3";
//     //retrieve path of the script
//     std::string path = "cgi-bin/todo.py";
    
//     this->_cgi.push_back(exec);
//     this->_cgi.push_back(path);
// }


// void    CGI::handleCGI()
// {
//     int check = 0;
//     int fd[2];

//     //store output of cgi script
//     std::string cgiResp;

//     //set cgi 
//     this->setCGIpath();
  

//     //convert cgi strings to char **
//     // char    **cgiEnv = convert_vector_to_char_array(this->_env);
//     char    **cgiExec = convert_vector_to_char_array(this->_cgi);
//     (void)cgiExec;
//     //cgiExec[0] = "python3" cgiExec[1] = "todo.py"
    
//     //execution
//     int tmp = dup(0);
//     if (pipe(fd) < 0)
//     {
//         //set http return status to 502
//         return ;
//     }

//     pid_t pid = fork();
//     if (pid < 0)
//     {
//         //set http return status to 502
//         return ;
//     }
    
//     if (pid == 0)
//     {
//         dup2(fd[1], STDOUT_FILENO);
//         close(fd[1]);

//         //create a file to store the body of the http request
//         std::FILE *tempStore;
// 		tempStore = tmpfile();
		
//     	if (tempStore) 
//         {
//             //get the body of the http request
// 			// std::string body = getHTTPBody();
//             //null terminate the string in char *
//         	// std::fprintf(tempStore, "%s", body.c_str());
//             std::fseek(tempStore, 0, SEEK_SET);
//     	}

// 		dup2(fileno(tempStore), 0);
// 		std::fclose(tempStore);

//         //The CGI should be run in the correct directory for relative path file access.
//         // changes the current working directory of the child process to the root directory of the server
//         //chdir to the root of the cgi

//         //location of the script
//         std::string location;
//         if (chdir(location.c_str()) < 0)
//         {
//             //set http return status to 502
//             return;
//         }
//         //alarm 
//         signal(SIGALRM, handleSignalTimeout);
//         alarm(5);

//         // char *const args[] = {"python3", "cgi_exemple.py", NULL};
//         // if (execve(cgiExec[0], cgiExec, cgiEnv) < 0)
//         //     exit(EXIT_FAILURE);
//     }
//     waitpid(pid, &check, 0);
//     //checks if the child process was terminated by a signal
//     if (WIFSIGNALED(check) || check != 0)
//     {
//         //set http return status to 502
//         return ;
//     }
//     dup2(fd[0], 0);
// 	close(fd[0]);
// 	close(fd[1]);

// 	char buffer[1];
// 	while (read(0, buffer, 1) > 0)
// 	   cgiResp.append(buffer, 1);

// 	dup2(tmp, 0);
// 	close(tmp);

//     //free allocated memory
//     // int getSize;
// 	// freeConvertedArray(cgiEnv,getSize);
// 	// freeConvertedArray(cgiExec,getSize);

//     //parse the cgiResp, and generate HTTP Response (HEADER + BODY)
//     std::cout << cgiResp << std::endl;
    
// }
