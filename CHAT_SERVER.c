#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
int main()
{
	int listen_fd,comm_fd;
	char str[100];
	char ex[]="exit";

	struct sockaddr_in servaddr;
	listen_fd=socket(AF_INET,SOCK_STREAM,0);

	servaddr.sin_port=htons(12345);
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=INADDR_ANY;

	bind(listen_fd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	listen(listen_fd,10);

	comm_fd=accept(listen_fd,(struct sockaddr *)NULL,NULL);
	while(1)
	{
		bzero(str,100);
		recv(comm_fd,str,100,0);
		printf("Received from cleint:%s",str);
		if(strncmp(str,ex,4)==0)
		break;
		
		bzero(str,100);
		fgets(str,100,stdin);
		send(comm_fd,str,strlen(str),0);
		if(strncmp(str,ex,4)==0)
		break;
	}
	close(comm_fd);
	close(listen_fd);
	
	
	
}