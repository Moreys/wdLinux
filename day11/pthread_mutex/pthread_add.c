#include<headFile.h>
#define N 100000

typedef struct
{
	int num;
	pthread_mutex_t mutex;
}Data;
void *threadFunc(void *p)
{
	Data *pThreadInfo = (Data*)p;
	for(int i = 0; i < N; ++i)
	{
		pthread_mutex_lock(&pThreadInfo->mutex);
		pThreadInfo->num +=1;
		pthread_mutex_unlock(&pThreadInfo->mutex);
	}
	return NULL;
}
int main()
{
	pthread_t pthID;
	int num = 0;
	int ret;
	Data threadInfo;
	threadInfo.num = 0;
	ret = pthread_mutex_init(&threadInfo.mutex,NULL);
	//统计时间
	struct timeval start,end;
	gettimeofday(&start,NULL);
	ret = pthread_create(&pthID,NULL,threadFunc,&threadInfo);
	if(ret != 0)
	{
		fprintf(stderr,"pthread_create:%s\n",strerror(ret));
		return -1;
	}
	int i;
	for(i = 0;i<N;i++)
	{
		pthread_mutex_lock(&threadInfo.mutex);
		threadInfo.num += 1;
		pthread_mutex_unlock(&threadInfo.mutex);
	}
	pthread_join(pthID,NULL);
	gettimeofday(&end,NULL);//结束时间统计
	ret = pthread_mutex_destroy(&threadInfo.mutex);
	printf("I am main thread,%d,use time = %ld\n",threadInfo.num,(end.tv_sec-start.tv_sec)*100000+end.tv_usec-start.tv_usec);
	return 0;
}

