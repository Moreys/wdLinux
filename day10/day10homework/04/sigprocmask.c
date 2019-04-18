#include<headFile.h>
int main()
{
	//定义一个接收的sigset
	/*
	初始化信号集合 sigemptyset
	增加需要阻塞的信号
	定义接收阻塞函数的接收值
	开始阻塞信号  使用SIG_BLOCK
	sigprocmask 是全程阻塞  设置了阻塞集合，被阻塞的信号将不能再被信号处理函数捕获，直到重新设置阻塞信号集合
	判断对错
	开始定义接收信号函数
	睡五秒
	打印
	定义挂起变量
	初始化挂起变量
	开始挂起
	判断是否被挂起
	解除挂起
	   */
	sigset_t procMask;
	sigemptyset(&procMask);
	sigaddset(&procMask,SIGINT);
	//sigprockmask 全程阻塞
	//参数1类型，三种SIG_BLOCK 添加 SIG_UNBLOCK释放  SIG_SETMASK重新设置
	int ret = sigprocmask(SIG_BLOCK,&procMask,NULL);
	ERROR_CHECK(ret,-1,"sigprocmask");
	signal(SIGINT,SIG_DFL);
	sleep(5);
	printf("这是重要的代码\n");
	sigset_t pending;
	sigemptyset(&pending);
	sigpending(&pending);
	if(sigismember(&pending,SIGINT))
	{
		printf("SIGINT 被挂起\n");
	}
	else
	{
		printf("SIGINT 没有被挂起\n");
	}
	sigprocmask(SIG_UNBLOCK,&pending,NULL);
	return 0;
}
