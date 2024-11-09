#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>

int main() {
    int sock_fd;
    char str_send[100], str_recv[100];
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);  // Define this once outside the loop

    // Create socket
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13500);
    servaddr.sin_addr.s_addr = inet_addr("172.16.132.160");

    // Communication loop
    while (1) {
        // Clear send buffer and get user input
        bzero(str_send, 100);
        fgets(str_send, 100, stdin);
        str_send[strcspn(str_send, "\n")] = 0;  // Remove newline character

        // Send data to server
        sendto(sock_fd, str_send, strlen(str_send), 0, (struct sockaddr *)&servaddr, len);

        // Optionally, receive response from server
        bzero(str_recv, 100);
        recvfrom(sock_fd, str_recv, 100, 0, (struct sockaddr *)&servaddr, &len);
        printf("Received from server: %s\n", str_recv);

        // Exit condition if "exit" is typed
        if (strncmp(str_send, "exit", 4) == 0) {
            break;
        }
    }

    // Close socket
    close(sock_fd);
    return 0;
}
