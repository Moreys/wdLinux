#include<headFile.h>
#include<pthread.h>
#define N 100000

void *threadFunc(void *p)
{
	int *num = (int*)p;
	for(int i = 0; i < N; ++i)
	{
		*num += 1;
	}
	return NULL;
}
int main()
{
	pthread_t pthID;
	int num = 0;
	int ret;
	ret = pthread_create(&pthID,NULL,threadFunc,&num);

	if(ret != 0)
	{
		fprintf(stderr,"pthread_create:%s\n",strerror(ret));
		return -1;
	}
	int i;
	for(i = 0;i<N;i++)
	{
		num +=1;
	}
	pthread_join(pthID,NULL);
	printf("I am main thread,%d\n",num);
	return 0;
}

