#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server;
    struct hostent *host;
    char request[1024], response[4096];

    // Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket() failed");
        exit(EXIT_FAILURE);
    }

    // Get the IP address of the web server
    host = gethostbyname("www.youtube.com");
    if (host == NULL) {
        perror("gethostbyname() failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address structure
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    server.sin_addr.s_addr = *((unsigned long*)host->h_addr_list[0]);

    // Connect to the web server
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("connect() failed");
        exit(EXIT_FAILURE);
    }

    // Send an HTTP request
    sprintf(request, "GET / HTTP/1.1\r\nHost: www.youtube.com\r\n\r\n");
    if (send(sock, request, strlen(request), 0) < 0) {
        perror("send() failed");
        exit(EXIT_FAILURE);
    }

    // Receive the response
    memset(response, 0, sizeof(response));
    if (recv(sock, response, sizeof(response), 0) < 0) {
        perror("recv() failed");
        exit(EXIT_FAILURE);
    }

    // Print the response
    printf("%s", response);

    // Close the socket
    close(sock);

    return 0;
}
