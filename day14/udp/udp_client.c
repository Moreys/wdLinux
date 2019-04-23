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
	ret = sendto(socketFd,"hello world",12,0,(struct sockaddr*)&ser,sizeof(ser));
	ERROR_CHECK(ret,-1,"sendto");
	char buf[128] = {0};
	ret = recvfrom(socketFd,buf,sizeof(buf),0,NULL,NULL);
	ERROR_CHECK(ret,-1,"recvform");
	printf("udp client gets %s\n",buf);
	close(socketFd);
}
