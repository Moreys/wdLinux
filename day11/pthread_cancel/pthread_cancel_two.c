#include<headFile.h>

void cleanup(void *p)
{
	pritnf("I am clean %ld\n",(long)p);
}

void *threadFunc(void *p)
{
	pthread_cleanup_push(cleanup,(void*)1);
	pthread_cleanup_push(cleanup,(void*)2);

	printf("I am child thread\n");

	pthread_exit(NULL);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
}
int main()
{
	pthread_t pthID;//线程ID
	int ret = pthread_create(&pthID,NULL,threadFunc,NULL);
	ret = pthread_cancel(pthID);
	long threadRet;
	ret = pthread_join(pthID,(void**)&threadRet);
	printf("I am thread %ld\n",threadRet);
	return 0;
}
