#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<netdb.h>
#include<unistd.h>
int main()
{
	int sock;//filedescripter
	char ex[]="exit";
	char sendline[100],recvline[100];

	struct sockaddr_in servaddr;//server address
	sock=socket(AF_INET,SOCK_STREAM,0);

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(12345);
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	connect(sock,(struct sockaddr *)&servaddr,sizeof(servaddr));
	while(1)
	{
		bzero(sendline,100);
		fgets(sendline,100,stdin);
		send(sock,sendline,strlen(sendline),0);
		if(strncmp(sendline,ex,4)==0)
		break;
		
		bzero(recvline,100);
		recv(sock,recvline,100,0);
		printf("The text received from server is:%s",recvline);
		if(strncmp(recvline,ex,4)==0)
		break;
	}
	close(sock);	
}