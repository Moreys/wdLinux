#include <headFile.h>

int main()
{
	char *p =(char*) malloc(sizeof(20));
	strcpy(p,"hello");
	pid_t pid;
	pid = fork();
	if(0 == pid)
	{
		printf("I am child = %d\n",getpid());
		strcpy(p,"world");
		printf("child%s,%p\n",p,p);
	}
	else
	{
		printf("I am parent = %d\n",getpid());
		printf("parent=%s,%p\n",p,p);
		printf("parent=%s,%p\n",p,p);
		sleep(1);
	}
}

