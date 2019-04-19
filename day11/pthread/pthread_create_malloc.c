#include<headFile.h>
void *threadFunc(void *p)
{
	strcpy((char*)p,"hello word!");//每次使用的时候都要将void类型强转为其他要使用的类型
	printf("I am child thread\n");
	return NULL;
}

int main()
{
	pthread_t thread;
    int ret;
	char *pMain = (char*)malloc(sizeof(char)*20);
	ret = pthread_create(&thread,NULL,threadFunc,pMain);
	if(ret != 0)
	{
		printf("pthread_create:%s\n",strerror(ret));
		return -1;
	}
	ret = pthread_join(thread,NULL);
	printf("I am main thread%s\n",pMain);
	return 0;
}
