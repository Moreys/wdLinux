#include<headFile.h>
#include<signal.h>

void sigFunc(int signum)
{
	printf("before sleep %d is coming\n",signum);
	sleep(3);
	printf("after sleep %d is coming\n",signum);
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
	signal(SIGQUIT,sigFunc);//捕获三号信号，
	//如果在二号信号的处理函数内按三号信号处理机制会马上执行三号信号处理机制，但是如果在继续按二号信号处理机制，不会从新执行二号处理机制，因为其本身就在二号处理函数里面，会继续执行刚才的命令
	while(1);
}

