#include<headFile.h>
/*
   客户端实现
   socket
   connect
   send/sendto
   recv/recvfrom
   close

   客户端前面也需要定义套接字进行存储要发送的数据
   */
int main(int argc,char **argv)
{
	ARGC_CHECK(argc,3);
	int socketFd;//定义套接字返回值
	socketFd = socket(AF_INET,SOCK_STREAM,0);//生成一个套接口描述符
	ERROR_CHECK(socketFd,-1,"socket");
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_port = htons(atoi(argv[2]));//服务器的端口
	ser.sin_addr.s_addr = inet_addr(argv[1]);//服务器的ip
	int ret;
	  //函数原型 int connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
	//参数1 socket的返回值  
	//参数2 socket结构体   存储服务器的ip与端口
	//参数3 结构体长度
	//成功返回0 失败返回-1
	ret = connect(socketFd,(struct sockaddr*)&ser,sizeof(ser));//请求连接远程服务器 
	ERROR_CHECK(ret,-1,"connect");
	printf("connect success\n");
	ret = send(socketFd,"hello",5,0);
	ERROR_CHECK(ret,-1,"send");
	char buf[128] = {0};
	ret = recv(socketFd,buf,sizeof(buf),0);
	ERROR_CHECK(ret,-1,"recv");
	printf("I am client,gets %s\n",buf);
	close(socketFd);
}
