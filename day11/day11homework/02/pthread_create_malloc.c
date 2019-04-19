//创建一个子线程，子线程申请内存，通过清理函数进行free，子线程停留在read标准输入，主线程cancel子线程，子线程能够通过清理函数free对应的malloc的内存
#include <headFile.h>
void pthclear(void *p)
{
	char *pcl = (char*)p;
	printf("我的清理函数\n");
	if(NULL != pcl)
	{
		free(pcl);
		pcl = NULL;
	    printf("内存被清理\n");
	}
}
void *pthreadFunc(void *p)
{
	printf("I am child\n");
	char *pbuf = (char*)malloc(sizeof(char)*20);
	strcpy(pbuf,"hello world");
	printf("我是子线程我申请了%ld个空间，其内容为%s\n",sizeof(pbuf),pbuf);
	pthread_cleanup_push(pthclear,pbuf);
	pthread_exit(NULL);
	pthread_cleanup_pop(0);
}
int main()
{
	pthread_t pthId;
	int ret = pthread_create(&pthId,NULL,pthreadFunc,NULL);
	if(0 != ret)
	{
		fprintf(stderr,"pthread_create:%s\n",strerror(ret));
		return -2;
	}
	int exitNum = 0;
	ret = pthread_cancel(pthId);
	ret = pthread_join(pthId,(void**)&exitNum);
	if(0 != ret)
	{
		fprintf(stderr,"pthread_create:%s\n",strerror(ret));
		return -2;
	}
	printf("ret = %d,exitNum = %d\n",ret,exitNum);
	return 0;
}
