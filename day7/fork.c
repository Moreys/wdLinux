#include <headFile.h>

int main()
{
	int n = 5,i;
//	pid_t iRet = fork();
	for( i = 0; i < n;++i)//出口1 父进程专用出口
	{
		if(fork()== 0)//出口2  子进程出口，i不用自增
			break;
	}
	if(n == i)//每次都先打印一下i
	{
		sleep(n);//最后才打印 跟随i的变化来决定睡几秒 
		printf("I am parent,pid = %d\n",getpid());
	}
	else
	{
		sleep(i);//出来一次打印一次，第一次出来的是子1 进程
		printf("I am %dth child,pid = %d\n",i+1,getpid());
	}
	return 0;
}

