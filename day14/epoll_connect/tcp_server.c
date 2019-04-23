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
	int addrlen;
	char buf[128] = {0};
	int epfd = epoll_create(1);
	ERROR_CHECK(epfd,-1,"epoll_create");
	struct epoll_event event,evs[3];
	event.events = EPOLLIN;
	event.data.fd = STDIN_FILENO;
	ret = epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);//监听标准输入是否可读
	ERROR_CHECK(ret,-1,"epoll_ctl");
	event.data.fd = socketFd;
	epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
	int i;
	int readyFdNum;
	while(1)
	{
		memset(evs,0,sizeof(evs));
		readyFdNum = epoll_wait(epfd,evs,3,-1);
		for(i = 0;i < readyFdNum;++i)
		{
			if(evs[i].data.fd == socketFd)
			{
				addrlen = sizeof(client);
				new_fd = accept(socketFd,(struct sockaddr*)&client,&addrlen);
				ERROR_CHECK(new_fd,-1,"accept");
				printf("client ip = %s,port = %d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));//打印一下连接进来的ip
				event.data.fd = new_fd;
				ret = epoll_ctl(epfd,EPOLLIN,new_fd,&event);
				ERROR_CHECK(ret,-1,"epoll_ctl");
			}
			if(evs[i].data.fd == new_fd)
				//判断new_fd是否就绪,如果就绪就读取内容并打印
			{
				memset(buf,0,sizeof(buf));
				ret = recv(new_fd,buf,sizeof(buf),0);
				ERROR_CHECK(ret,-1,"recv");
				if(0 == ret)
				{
					printf("再见\n");
					event.events = EPOLLIN;
					event.data.fd = new_fd;
					ret = epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&event);
					printf("line = %d\n",__LINE__);
					ERROR_CHECK(ret,-1,"epoll_ctl");
					continue;
				}
				printf("%s\n",buf);
			}
			if(0==evs[i].data.fd)//判断标准输入是否可读，读取标准输入并发送给对端
			{
				memset(buf,0,sizeof(buf));
				ret = read(STDIN_FILENO,buf,sizeof(buf));
				if(0 == ret)
				{
					printf("再见\n");
					goto chatOver;
				}
				ret = send(new_fd,buf,strlen(buf)-1,0);
				ERROR_CHECK(ret,-1,"send");
			}
		}
	}
chatOver:
	close(new_fd);
	close(socketFd);
	return 0;
}
