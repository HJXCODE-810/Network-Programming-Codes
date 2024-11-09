// broadcast_receiver.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 22000

int main() {
    int sockfd;
    struct sockaddr_in recv_addr, sender_addr;
    char buffer[1024];
    socklen_t addr_len = sizeof(sender_addr);

    // Step a: Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Step b: Fill the receiving information structure
    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(PORT);
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // Listen on all interfaces

    // Step c: Bind the socket to the address and port
    if (bind(sockfd, (struct sockaddr*)&recv_addr, sizeof(recv_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Broadcast receiver listening on port %d...\n", PORT);

    // Receiving loop
    while (1) {
        memset(buffer, 0, sizeof(buffer));

        // Step d: Receive broadcast message
        int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&sender_addr, &addr_len);
        if (n < 0) {
            perror("Receive failed");
            continue;
        }

        buffer[n] = '\0';  // Null-terminate the received string

        printf("Received from [%s:%d]: %s\n", inet_ntoa(sender_addr.sin_addr), ntohs(sender_addr.sin_port), buffer);

        // Exit if the received message is "exit"
        if (strcmp(buffer, "exit") == 0) {
            printf("Exiting broadcast receiver...\n");
            break;
        }
    }

    // Close the socket
    close(sockfd);
    return 0;
}
