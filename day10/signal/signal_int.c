#include<headFile.h>
#include<signal.h>

void sigFunc(int signum)
{
	printf("%d is coming\n",signum);
}

int main()
{
	//signal函数作用 注册一个信号捕捉函数
	//参数1 signum 要捕捉的信号  参数2 函数指针  表示要捕捉的函数 
	//返回成功 返回以前该信号的处理函数的地址，否则返回SIG_ERR
	if(signal(SIGINT,sigFunc) == SIG_ERR)
	{
		perror("signal");
		return -1;
	}
	while(1);
}

