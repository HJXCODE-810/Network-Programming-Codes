#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>

int main() {
    int listen_fd;
    char str[100], ec[100];
    struct sockaddr_in servaddr, clientaddr;
    
    // Create a UDP socket
    listen_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (listen_fd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address family, port, and IP address
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13500);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket with the server address
    if (bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        close(listen_fd);
        exit(EXIT_FAILURE);
    }

    socklen_t len = sizeof(clientaddr);
    while (1) {
        bzero(str, 100);
        
        // Receive message from client
        int n = recvfrom(listen_fd, str, 100, 0, (struct sockaddr *)&clientaddr, &len);
        if (n < 0) {
            perror("recvfrom failed");
            continue;  // Handle failure gracefully
        }
        
        str[n] = '\0';  // Null-terminate the received string
        printf("received from client: %s\n", str);

        bzero(str,100);
        fgets(str,100,stdin);
        sendto(listen_fd,str,strlen(str),0, (struct sockaddr *)&clientaddr, len);

    }

    // Close the socket
    close(listen_fd);
    return 0;
}
