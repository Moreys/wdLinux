#include <headFile.h>
#include<sys/wait.h>

int main()
{
	pid_t pid;
	pid = fork();
	if(!pid)
	{
		printf("I am child process,pid = %d,ppid = %d\n",getpid(),getppid());
		sleep(1);
		return 0;
	}
	else 
	{
		printf("I am parent\n");
		pid_t childPid;	
		int status = 0;//接收到等待的子进程
		childPid = waitpid(pid,&status,WNOHANG);//等待指定的子进程
		if(childPid >0 )
		{
			if(WIFEXITED(status))
			{
				printf("child exit normal %d\n",WEXITSTATUS(status));
			}
			else
			{
				printf("child crash\n");
			}
		}
			printf("childPid is %d\n",childPid);
		return 0;
	}
}

