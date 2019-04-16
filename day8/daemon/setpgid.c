#include <headFile.h>
int main()
{
	pid_t pid;
	pid = fork();
	if(!pid)
	{
		printf("child pid = %d,ppid = %d,pgid = %d\n",getpid(),getppid(),getpgid(0));//getpgid需要跟一个参数
		//给子进程设置了新的进程组以后 跟父进程组的id不一样
		setpgid(0,0);//设置进程组
		printf("child pid = %d,ppid = %d,pgid = %d\n",getpid(),getppid(),getpgid(0));//getpgid需要跟一个参数
		while(1);
	}
	else
	{
		printf("parent pid =%d,ppid = %d,pgid = %d\n",getpid(),getppid(),getpgid(0));
		while(1);
	}
}
