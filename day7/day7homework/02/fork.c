#include <headFile.h>

int main()
{
	pid_t iRet = fork();
	if(iRet < 0 )
	{
		printf("error");
	}
	else if(iRet == 0)
	{
		printf("I am is child,the pid= %d\n",getpid());
		while(1);
	}
	else
	{
		printf("I am is parent pid = %d\n",getpid());
	while(1);	
	}
}
