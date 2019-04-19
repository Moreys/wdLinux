//子线程，主线程，同时对一个全局变量加2千万，通过加锁，实现最终效果是4千万。
#include<headFile.h>
#define N 20000000
typedef struct
{
	pthread_mutex_t mutex;
}Num;

int number = 0;
void *pthAdd(void *args)
{
	Num *pN = (Num*)args;//接收的时候使用结构体指针进行接收
	for(int i = 0; i < N; ++i)
	{
		pthread_mutex_lock(&pN->mutex);
		number += 1;
		pthread_mutex_unlock(&pN->mutex);
	}
	printf("I am child over\n");
	pthread_exit(NULL);
}
int main()
{
	pthread_t pthId;
	Num n;
	int ret = pthread_create(&pthId,NULL,pthAdd,&n);//传入的是整个结构体
	if(0 != ret)
	{
		fprintf(stderr,"pthread_create:%s\n",strerror(ret));
		return -2;
	}
	ret = pthread_mutex_init(&n.mutex,NULL);
	for(int i = 0;i < N; ++i)
	{
		pthread_mutex_lock(&n.mutex);
		number += 1;
		pthread_mutex_unlock(&n.mutex);
	}
	ret = pthread_join(pthId,NULL);
	ret = pthread_mutex_destroy(&n.mutex);
	printf("全局变量的值为%d\n",number);
	return 0;
}

	
