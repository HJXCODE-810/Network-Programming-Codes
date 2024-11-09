#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 23456
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(server_addr);

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }
    printf("UDP client socket created.\n");

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1) {
        // Get input from user
        printf("Enter message (or 'exit' to quit): ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        // Exit if the user types 'exit'
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // Send data to the server
        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, addr_len) < 0) {
            perror("sendto");
            break;
        }

        // Receive data from the server
        memset(buffer, 0, BUFFER_SIZE);
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&server_addr, &addr_len);
        if (n < 0) {
            perror("recvfrom");
            break;
        }
        buffer[n] = '\0'; // Null-terminate the string
        printf("Server response: %s\n", buffer);
    }

    // Close the socket
    close(sockfd);

    return 0;
}

