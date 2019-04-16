#include <headFile.h>
#include<sys/wait.h>

int main()
{
	if(!fork())
	{
		printf("I am child process,pid = %d,ppid = %d\n",getpid(),getppid());
		int num = 1/0;
		printf("num = %d\n",num);
		return 5;
	}
	else 
	{
		printf("I am parent\n");
		pid_t childPid;	
		int status;//接收到等待的子进程
		childPid = wait(&status);//等待子进程退出，并并进行清理
		if(WIFEXITED(status))
		{
			printf("child exit normal %d\n",WEXITSTATUS(status));
		}
		else
		{
			printf("child crash\n");
		}

		printf("childPid is %d\n",childPid);
		return 0;
	}
}

