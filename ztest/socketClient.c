#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 80

int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "GET / HTTP/1.1\r\nHost: 216.58.194.174\r\n\r\n";
    char buffer[1024] = {0};
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "216.58.194.174", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    // Send the HTTP request
    send(sock , hello , strlen(hello) , 0 );
    printf("HTTP request sent\n");
    
    // Receive the HTTP response in chunks
    int total_bytes_read = 0;
    while ((valread = read(sock , buffer, 1024)) > 0)
    {
        total_bytes_read += valread;
        printf("%.*s", valread, buffer); // Print only the received data
    }
    
    printf("\n\nTotal bytes received: %d\n", total_bytes_read);
    
    return 0;
}
