#include <headFile.h>
int main()
{
	//SIGINT 信号2  SIG_IGN表示忽略该信号不做操作
	signal(SIGINT,SIG_IGN);
	sleep(5);
	//定义长整型 将需要
	sigset_t pending;
	//清空信号集合set
	//
	sigemptyset(&pending);
	//将被阻塞的信号集合由参数set指针返回（挂起信号）
	sigpending(&pending);
	//sigismember 判断某个信号是否在信号集中，在 返回1 不在返回-1
	if(sigismember(&pending,SIGINT))
	{
		printf("SIGINT is pending\n");
	}
	else
	{
		printf("SIGINT not is pending\n");
	}
	printf("this is important code\n");
	//SIG_DFL 由系统缺省处理  相当于白注册了
	signal(SIGINT,SIG_DFL);
	return 0;
}
