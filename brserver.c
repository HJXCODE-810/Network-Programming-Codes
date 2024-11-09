// broadcast_sender.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 22000
#define BROADCAST_IP "10.0.2.255"  // Use the broadcast address for the network

int main() {
    int sockfd;
    struct sockaddr_in broadcast_addr;
    char message[1024];
    int broadcast_enable = 1;

    // Step a: Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Step c: Set socket options to allow broadcast
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable)) < 0) {
        perror("Error setting socket options");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Step b: Fill the broadcast information structure
    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(PORT);
    broadcast_addr.sin_addr.s_addr = inet_addr(BROADCAST_IP);

    // Broadcast loop
    while (1) {
        printf("Enter message to broadcast (type 'exit' to quit): ");
        fgets(message, sizeof(message), stdin);

        // Remove newline character from fgets
        message[strcspn(message, "\n")] = '\0';

        // Step d: Send broadcast message
        if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr)) < 0) {
            perror("Broadcast send failed");
            continue;
        }

        printf("Broadcast message sent: %s\n", message);

        // Exit if the message is "exit"
        if (strcmp(message, "exit") == 0) {
            printf("Exiting broadcast sender...\n");
            break;
        }
    }

    // Close the socket
    close(sockfd);
    return 0;
}
