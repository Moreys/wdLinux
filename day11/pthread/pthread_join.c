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
	ret = pthread_join(thread,NULL);
	if(ret != 0)
	{
		fprintf(stderr,"pthread_join:%s\n",strerror(ret));
		return -1;
	}
	return 0;
}
