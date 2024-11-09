#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 23456
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;
    char buffer[BUFFER_SIZE];
    int n;

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }
    printf("UDP server socket created.\n");

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(sockfd);
        exit(1);
    }
    printf("Bind to port %d\n", PORT);

    while (1) {
        addr_len = sizeof(client_addr);
        memset(buffer, 0, BUFFER_SIZE);
        
        // Receive data from the client
        n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&client_addr, &addr_len);
        if (n < 0) {
            perror("recvfrom");
            continue;
        }
        buffer[n] = '\0'; // Null-terminate the string
        printf("Received from client: %s\n", buffer);

        // Send the received data back to the client
        if (sendto(sockfd, buffer, n, 0, (struct sockaddr*)&client_addr, addr_len) < 0) {
            perror("sendto");
        }
    }

    // Close the socket
    close(sockfd);

    return 0;
}

