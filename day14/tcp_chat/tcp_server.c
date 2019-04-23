#include<headFile.h>
/*tcp服务器端开发
  开发步骤
  socket
  bind
  listen
  accept
  recv/recvform
  send/sendto
  close
  整个通信过程需要两个套接字来参与  一个为接收端的套接字   一个为发送的套接字   
  可以理解为接收缓冲区和发送缓冲区 中间是处理部分，
  拿到数据 然后进行处理  最后发送     拿数据和发送数据 需要两个不同的套接字来进行参与
 */
int main(int argc,char **argv)
{
	ARGC_CHECK(argc,3);
	int socketFd;//定义socket返回类型 为接口描述符
	//参数1 IP类型4  6  参数2 协议 tcp udp 参数3传输协议编号
	//成功返回接口描述符  失败返回-1j
	socketFd = socket(AF_INET,SOCK_STREAM,0);
	ERROR_CHECK(socketFd,-1,"socket");
	struct sockaddr_in ser;//bind函数需要一个结构体
	bzero(&ser,sizeof(ser));
	ser.sin_family = AF_INET;//设置ip类型  ip4  ip6
	ser.sin_port = htons(atoi(argv[2]));//设置端口号，需要转为int类型
	ser.sin_addr.s_addr = inet_addr(argv[1]);//点分十进制转为32为ip字节序
	int ret;
	//函数bind，绑定一个端口号和ip地址
	//参数1 为socket返回值  参数2 结构体指针，为了兼容必须强转  参数3 结构体长度
	ret = bind(socketFd,(struct sockaddr*)&ser,sizeof(ser));	
	ERROR_CHECK(ret,-1,"bind");
	listen(socketFd,10);//缓冲区的大小，最大能够同时连接的客户端个数
	//开始阻塞等待客户端接入
	int new_fd;//用来接受accpet的返回值
	struct sockaddr_in client;
	bzero(&client,sizeof(client));
	int addrlen = sizeof(client);
	//接收客户端的链接请求建立通信
	//参数1 socket返回值  参数2  结构体指针，需要强转  参数3 结构体长度为整型指针
	//成功返回socket处理代码new_fd，失败返回-1
	new_fd = accept(socketFd,(struct sockaddr*)&client,&addrlen);
	ERROR_CHECK(new_fd,-1,"accept");
	printf("client ip = %s,port = %d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));//打印一下连接进来的ip
	char buf[128] = {0};
	fd_set rdset;
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(new_fd,&rdset);
		ret = select(new_fd + 1,&rdset,NULL,NULL,NULL);
		ERROR_CHECK(ret,-1,"select");
		//recv 新的套接字来接收客户端传来的数据，并将数据保存到buf指向的内存空间
		//参数1 accept的返回值 new_fd 新的套接字  
		//参数2 表示缓冲区  参数3  表示缓冲区长度  参数4 通常为0
		if(FD_ISSET(new_fd,&rdset))//判断是否准备
		{
			memset(buf,0,sizeof(buf));
			ret = recv(new_fd,buf,sizeof(buf),0);
			ERROR_CHECK(ret,-1,"recv");
			if(0 == ret)
			{
				printf("再见\n");
				break;
			}
			printf("I am server,gets %s\n",buf);
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
			//send   用新的套接字发送数据给客户机
			//参数1  accept的返回值  new_fd
			//参数2  常量字符串 void* msg
			//参数3  长度
			//参数4  通常为0   unsigned int flags
			//成功返回实际发送出去的字符数，可能会小于指定大小，失败返回-1
			ret = send(new_fd,buf,strlen(buf)-1,0);
			ERROR_CHECK(ret,-1,"send");
		}
	}
	close(new_fd);
	close(socketFd);
	return 0;
}
