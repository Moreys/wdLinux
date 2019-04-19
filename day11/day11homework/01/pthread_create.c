//1、创建一个子线程，传入数值1，在子线程中能够获取并打印，子线程退出，返回数值2，主线程通过pthread_join获取等待子线程结束并获取子线程的退出值并打印
#include<headFile.h>
void* pthreadFunc(void *p)
{
	printf("I am child,my number is%d\n",*(int*)p);
	pthread_exit((void*)3);
}
int main()
{
	pthread_t pthID;
	int number = 1;
	int ret = pthread_create(&pthID,NULL,pthreadFunc,&number);
	if(ret !=0)
	{
		fprintf(stderr,"pthread_create:%s\n",strerror(ret));
		return -2;
	}
	int number2 = 0;
	ret = pthread_join(pthID,(void**)&number2);
	printf("I am praent,子函数返回值为%d\n",number2);
	return 0;
}
