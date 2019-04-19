#include<headFile.h>
void *threadFunc(void *p)
{
	printf("I am child thread\n");
	return NULL;
}

int main()
{
	pthread_t thread;
	int ret;
	ret = pthread_create(&thread,NULL,threadFunc,NULL);
	if(ret != 0)
	{
		printf("pthread_create:%s\n",strerror(ret));
		return -1;
	}
	printf("I am main thread\n");
	usleep(1000);
	return 0;
}
