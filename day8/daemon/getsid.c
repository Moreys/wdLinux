#include <headFile.h>
int main()
{
	pid_t pid;
	pid = fork();
	if(!pid)
	{
		//getsid 得到设置的sid
		printf("child pid = %d,ppid = %d,pgid = %d,sid = %d\n",getpid(),getppid(),getpgid(0),getsid(0));//getpgid需要跟一个参数
		while(1);
	}
	else
	{
		printf("parent pid =%d,ppid = %d,pgid = %d,sid = %d\n",getpid(),getppid(),getpgid(0),getsid(0));
		while(1);
	}
}
