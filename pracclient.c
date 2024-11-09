#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>

int main()
{
    int send_fd;
    char send_str[100],recv_str[100];
    struct sockaddr_in servaddr;

    send_fd = socket(AF_INET,SOCK_STREAM,0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port=htons(15000);
    servaddr.sin_addr.s_addr = inet_addr("172.16.132.160");

    connect(send_fd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    while(1)
    {
        bzero(send_str,100);
        fgets(send_str,100,stdin);
        send(send_fd,send_str,strlen(send_str),0);
        
        bzero(recv_str,100);
        recv(send_fd,recv_str,100,0);
        printf("received from server:%s",recv_str);

    }
    close(send_fd);
}