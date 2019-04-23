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
	ret = sendto(socketFd,"h",1,0,(struct sockaddr*)&ser,sizeof(ser));//默认要先发一个过去确认一下
	ERROR_CHECK(ret,-1,"sendto");
	char buf[128] = {0};
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
			ret = recvfrom(socketFd,buf,sizeof(buf),0,NULL,NULL);
			ERROR_CHECK(ret,-1,"recvform");
			printf("%s\n",buf);
		}
		if(FD_ISSET(STDIN_FILENO,&rdset))
		{
			memset(buf,0,sizeof(buf));
			ret = read(STDIN_FILENO,buf,sizeof(buf));
			if(0==ret)
			{
				printf("再见\n");
				break;
			}
			ret = sendto(socketFd,buf,strlen(buf)-1,0,(struct sockaddr*)&ser,sizeof(ser));
			ERROR_CHECK(ret,-1,"sendto");
		}
	}
	close(socketFd);
}
