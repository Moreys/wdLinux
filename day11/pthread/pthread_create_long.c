#include<headFile.h>
void *threadFunc(void *p)
{
	printf("I am child thread%ld\n",(long)p);//在打印的时候必须将void型指针强转 long
	return NULL;
}

int main()
{
	//需要区分是不同的子进程进行的调用
	pthread_t thread,thread1;
	int ret;
	long threadNum =1;

	ret = pthread_create(&thread,NULL,threadFunc,(void*)threadNum);//将整型的地址传入到子函数当中进行确定
	if(ret != 0)
	{
		printf("pthread_create:%s\n",strerror(ret));
		return -1;
	}
	threadNum = 2;
	//创建另一个子线程
	pthread_create(&thread1,NULL,threadFunc,(void*)threadNum);//因为函数接收的是void指针，所有传入需要强制为void*
	pthread_join(thread,NULL);
	pthread_join(thread1,NULL);
	printf("I am main thread\n");
	if(ret != 0)
	{
		fprintf(stderr,"pthread_join:%s\n",strerror(ret));
		return -1;
	}
	return 0;
}
