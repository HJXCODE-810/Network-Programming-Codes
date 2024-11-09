#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<netdb.h>
#include<unistd.h>
int main()
{
int sockid;
char data[100],rcvdata[100];
struct sockaddr_in serveraddr;
sockid=socket(AF_INET,SOCK_STREAM,0);
serveraddr.sin_family =AF_INET;
serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
serveraddr.sin_port=htons(23456);
connect(sockid,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
fgets(data,100,stdin);
stdin=0;
send(sockid,data,strlen(data),0);
recv(sockid,rcvdata,100,0);
printf("\ndata from server : %s",rcvdata);
}
