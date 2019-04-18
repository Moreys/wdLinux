#include<headFile.h>
void sigFunc(int signum)
{
	printf("%d is coming\n",signum);
}
int main()
{
	//接收信号量 并且触发sigFunc函数进行处理事件，
	if(signal(SIGINT,sigFunc) == SIG_ERR)
	{
		perror("signal");
		return -1;
	}
	char buf[128] = {0};
	//读取0号位的信息量，看看是哪个信号发送的
	//去读当前位置输入的其他信息
	read(STDIN_FILENO,buf,sizeof(buf));
	printf("buf = %s\n",buf);
}
