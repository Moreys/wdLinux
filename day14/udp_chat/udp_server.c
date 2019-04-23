#include<headFile.h>
int main(int argc,char **argv)
{
	ARGC_CHECK(argc,3);
	int socketFd;
	socketFd = socket(AF_INET,SOCK_DGRAM,0);
	ERROR_CHECK(socketFd,-1,"socket");
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_port = htons(atoi(argv[2]));
	ser.sin_addr.s_addr = inet_addr(argv[1]);
	int ret;
	ret = bind(socketFd,(struct sockaddr*)&ser,sizeof(ser));//bind以后端口就已经激活了	
	ERROR_CHECK(ret,-1,"bind");
	char buf[128] = {0};//最大只能填65535
	struct sockaddr_in client;
	int addrlen = sizeof(client);
	ret =  recvfrom(socketFd,buf,1,0,(struct sockaddr*)&client,&addrlen);
	ERROR_CHECK(ret,-1,"recvfrom");
	printf("client ip = %s,port = %d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
	fd_set rdset;
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(socketFd,&rdset);
		ret = select(socketFd+1,&rdset,NULL,NULL,NULL);
		if(FD_ISSET(socketFd,&rdset))
		{
			memset(buf,0,sizeof(buf));
			ret =  recvfrom(socketFd,buf,sizeof(buf),0,(struct sockaddr*)&client,&addrlen);
			ERROR_CHECK(ret,-1,"recvfrom");
			printf("%s\n",buf);
		}
		if(FD_ISSET(STDIN_FILENO,&rdset))
		{

			memset(buf,0,sizeof(buf));
			ret = read(STDIN_FILENO,buf,sizeof(buf));
			if(0 == ret)
			{
				printf("再见\n");
				break;
			}
			ret = sendto(socketFd,buf,strlen(buf)-1,0,(struct sockaddr*)&client,sizeof(client));
			ERROR_CHECK(ret,-1,"sendto");
		}
	}
	close(socketFd);
}


