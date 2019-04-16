#include <headFile.h>
int main()
{
	pid_t pid;
	pid = fork();
	if(!pid)
	{
		//pgid获得进程组的id 一般父进程启动子子进程的时候回话组会给其重新分配一个进程组
		printf("child pid = %d,ppid = %d,pgid = %d\n",getpid(),getppid(),getpgid(0));//getpgid需要跟一个参数
		while(1);
	}
	else
	{
		printf("parent pid =%d,ppid = %d,pgid = %d\n",getpid(),getppid(),getpgid(0));
		while(1);
	}
}
