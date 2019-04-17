#include<headFile.h>

void Daemon()
{
const int MAXFD = 64;
	int i = 0;
	if(fork()!=0)//父进程关闭
		exit(0);
	setsid();//成为新进程组组长和新会话领导，脱离终端
	chdir("/");//设置工作目录为根目录
	umask(0);
	//for(;i < MAXFD;++i)
	//	close(i);
}
int main(int argc,char **argv)
{
	Daemon();
	int fd = open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	while(1)
	{
		sleep(5);	
//		char buf[] = "I have run 5s";
		int ret = write(fd,"I have run 5s\n",15);
		ERROR_CHECK(ret,-1,"write");
	}
	return 0;
}
