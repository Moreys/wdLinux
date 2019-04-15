#include<headFile.h>

int main(int argc,char **argv)
{
	pid_t pid;
	pid = fork();
	int ret;
	if(0 == pid)
	{
	int fd = open(argv[1],O_RDWR);
		printf("I am child,pid = %d,parent pid = %d\n",getpid(),getppid());
		ret = write(fd,"hello",5);
	}
	else
	{
	int fd = open(argv[1],O_RDWR);
		printf("I am parent,child pid = %d,self pid = %d\n",pid,getpid());
		ret = write(fd,"world",5);
		sleep(1);
	}
}
