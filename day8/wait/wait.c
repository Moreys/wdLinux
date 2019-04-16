#include <headFile.h>
#include<sys/wait.h>

int main()
{
	if(!fork())
	{
		printf("I am child process,pid = %d,ppid = %d\n",getpid(),getppid());
		return 0;
	}
	else 
	{
		printf("I am parent\n");
		pid_t childPid;
		childPid = wait(NULL);//等待子进程结束后将其回收
		printf("childPid id %d\n",childPid);
		return 0;
	}
}

