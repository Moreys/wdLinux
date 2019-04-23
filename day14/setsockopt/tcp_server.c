#include<headFile.h>
int main(int argc,char **argv)
{
	ARGC_CHECK(argc,3);
	int socketFd;//定义socket返回类型 为接口描述符
	socketFd = socket(AF_INET,SOCK_STREAM,0);
	ERROR_CHECK(socketFd,-1,"socket");
	struct sockaddr_in ser;//bind函数需要一个结构体
	bzero(&ser,sizeof(ser));
	ser.sin_family = AF_INET;//设置ip类型  ip4  ip6
	ser.sin_port = htons(atoi(argv[2]));//设置端口号，需要转为int类型
	ser.sin_addr.s_addr = inet_addr(argv[1]);//点分十进制转为32为ip字节序
	int ret;
	ret = bind(socketFd,(struct sockaddr*)&ser,sizeof(ser));	
	ERROR_CHECK(ret,-1,"bind");
	listen(socketFd,10);//缓冲区的大小，最大能够同时连接的客户端个数
	int new_fd;//用来接受accpet的返回值
	struct sockaddr_in client;
	bzero(&client,sizeof(client));
	int addrlen = sizeof(client);
	char buf[128] = {0};
	fd_set rdset;
	fd_set needMS;
	FD_ZERO(&needMS);
	FD_SET(STDIN_FILENO,&needMS);
	FD_SET(socketFd,&needMS);
	int rcvLowAt = 10;

	while(1)
	{
		memcpy(&rdset,&needMS,sizeof(fd_set));
		ret = select(11,&rdset,NULL,NULL,NULL);
		ERROR_CHECK(ret,-1,"select");
		if(FD_ISSET(socketFd,&rdset))
		{
        	new_fd = accept(socketFd,(struct sockaddr*)&client,&addrlen);
	ret = setsockopt(new_fd,SOL_SOCKET,SO_RCVLOWAT,&rcvLowAt,sizeof(int));
	ERROR_CHECK(ret,-1,"setsockopt");
         	ERROR_CHECK(new_fd,-1,"accept");
        	printf("client ip = %s,port = %d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));//打印一下连接进来的ip
	    	FD_SET(new_fd,&needMS);
		}

		if(FD_ISSET(new_fd,&rdset))//判断是否准备
		{
			memset(buf,0,sizeof(buf));
			ret = recv(new_fd,buf,sizeof(buf),0);
			ERROR_CHECK(ret,-1,"recv");
			if(0 == ret)
			{
				printf("再见\n");
				FD_CLR(new_fd,&needMS);
				close(new_fd);
				continue;
			}
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
			ret = send(new_fd,buf,strlen(buf)-1,0);
			ERROR_CHECK(ret,-1,"send");
		}
	}
	close(socketFd);
	return 0;
}
