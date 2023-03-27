/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:23:51 by fech-cha          #+#    #+#             */
/*   Updated: 2023/03/22 16:12:54 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

//getaddressinfo()

// int main()
// {
//     int status;
//     struct addrinfo hints;
//     struct addrinfo *servinfo;  //linked list will point to the results

//     memset(&hints, 0, sizeof hints); // make sure the struct is empty
//     hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
//     hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
//     hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

//     if ((status = getaddrinfo(NULL, "http", &hints, &servinfo)) != 0) {
//         fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
//         exit(1);
//     }

//     // servinfo now points to a linked list of 1 or more struct addrinfos

//     // ... do everything until you don't need servinfo anymore ....

//     freeaddrinfo(servinfo); // free the linked-list
// }

//getaddrinfo()
//socket(): return a socket descriptor
//bind(): link a socket with a port number
//listen()
//accept()

# define MYPORT "3490"
# define BACKLOG 10


/*Often, there will only be one server on a machine, and that server will handle multiple clients using fork().
 The basic routine is: server will wait for a connection, accept() it, and fork() a child process to handle it.
  This is what our sample server does in the next section.*/
int main()
{
    socklen_t addr_size;
    int check, sockfd, new_fd;
    struct addrinfo hints, *res;
    struct sockaddr_storage their_addr;
    
    //fill the structure
    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    if ((check = getaddrinfo(NULL, MYPORT, &hints, &res)) != 0)
    {
        //print error message and exit
        exit(1);
    }

    //make a socket, returns socket address
    //we should check on the SD returned
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    //bind it to the port we passed in to getaddrinfo() (associate the socket with a port)
    //binds the socket to the host the program is running on, port 3490
    bind(sockfd, res->ai_addr, res->ai_addrlen);
    std::cout << "Listening:" << std::endl;
    listen(sockfd, BACKLOG);

    //accept an incoming connection
    addr_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    
    //ready to communicate on socket descriptor new_fd
    //send/recv
    //recv first then send
    char *msg = "Beej was here!";
    int len, bytes_sent;
    len = strlen(msg);
    bytes_sent = send(sockfd, msg, len, 0);
    //close
    int yes = 1;

    //lose the "Address already in use" error message
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1)
    {
        perror("setsockopt");
        exit(1);
    }
    freeaddrinfo(res);
}



