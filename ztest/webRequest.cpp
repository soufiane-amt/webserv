#include <iostream>
#include <string>
#include <sstream>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main() {
    std::string hostname = "www.bogotobogo.com";
    std::string path = "/cplusplus/dynamic_cast.php";
    int port = 80;

    // Get server address
    struct addrinfo hints, *server_info;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(hostname.c_str(), "80", &hints, &server_info);

    // Create socket
    int sockfd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

    // Connect to server
    connect(sockfd, server_info->ai_addr, server_info->ai_addrlen);

    // Send request
    std::stringstream request;
    request << "GET " << path << " HTTP/1.1\r\n";
    request << "Host: " << hostname << "\r\n";
    request << "Connection: close\r\n\r\n";
    std::string request_str = request.str();
    send(sockfd, request_str.c_str(), request_str.size(), 0);

    // Receive response
    std::string response;
    char buffer[1024];
    int bytes_received;
    while ((bytes_received = recv(sockfd, buffer, 1024, 0)) > 0) {
        response.append(buffer, bytes_received);
    }

    // Print response
    std::cout << response << std::endl;

    // Clean up
    freeaddrinfo(server_info);
    close(sockfd);

    return 0;
}
