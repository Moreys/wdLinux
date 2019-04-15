#include <headFile.h>

int main()
{
	pid_t pid;
	int num = 10;
	pid = fork();
	if(0 == pid)
	{
		printf("I am child proces,pid = %d,ppid = %d\n",getpid(),getppid());
		printf("child num = %d,%p\n",num,&num);
	}
	else
	{
		printf("I am praent process,child pid = %d,self pid = %d\n",pid,getpid());
		num = 5;
		printf("parent num = %d,%p\n",num,&num);
		sleep(1);
	}
}	
