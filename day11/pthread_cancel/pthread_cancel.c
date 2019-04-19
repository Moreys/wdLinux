#include<headFile.h>

void *threadFunc(void *p)
{
	printf("I am child thread\n");
	pthread_exit((void*)0);
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
