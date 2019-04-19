//创建两个子线程卖票，第三个子线程放票，两个子线程卖完20张票后，第三个子线程把票重新设置为20，然后两个子线程继续卖票，把票卖光
#include<headFile.h>
#define N 20
typedef struct
{
	int num;
	pthread_cond_t cond;
	pthread_mutex_t mutex;
}Num;
void *winTicket(void *args)
{
	Num *pN = (Num*)args;//接收的时候使用结构体指针进行接收
	int count = 0;
	while(1)
	{
		pthread_mutex_lock(&pN->mutex);
		if(pN->num > 0)
		{
			printf("窗口1开始卖票，卖了%d\n",pN->num);
			pN->num--;
			if(0 == pN->num)
			{
				pthread_cond_signal(&pN->cond);
			}
			count++;
			printf("窗口1卖票结束，剩余%d\n",pN->num);
			pthread_mutex_unlock(&pN->mutex);
		}
		else
		{
			pthread_mutex_unlock(&pN->mutex);
			printf("窗口1卖了%d张票\n",count);
			break;
		}
		sleep(1);
	}
	pthread_exit(NULL);
}
void *winTicket1(void *args)
{
	Num *pN = (Num*)args;
	int count = 0;
	while(1)
	{
		pthread_mutex_lock(&pN->mutex);
		if(pN->num > 0)
		{
			printf("窗口2开始卖票，卖了%d\n",pN->num);
			pN->num--;
			if(0 == pN->num)
			{
				pthread_cond_signal(&pN->cond);
			}
			count++;
			printf("窗口2卖票结束，剩余%d\n",pN->num);
			pthread_mutex_unlock(&pN->mutex);
		}
		else
		{
			pthread_mutex_unlock(&pN->mutex);
			printf("窗口2卖了%d张票\n",count);
			break;
		}
		sleep(1);
	}
	pthread_exit(NULL);
}
void *setTicket(void *args)
{
	Num *pN = (Num*)args;
	pthread_mutex_lock(&pN->mutex);
	if(pN->num > 0)
	{
		pthread_cond_wait(&pN->cond,&pN->mutex);
	}
	pN->num = 20;

	pthread_mutex_unlock(&pN->mutex);
	sleep(1);
	pthread_exit(NULL);
}

typedef void* (*threadFunc)(void*);
int main()
{
	pthread_t pthId[3];
	Num n;
	n.num = 20;
	threadFunc pthreadFunc[3] = {winTicket,winTicket1,setTicket};
	pthread_mutex_init(&n.mutex,NULL);
	pthread_cond_init(&n.cond,NULL);
	for(int i = 0; i< 3;++i)
	{
		pthread_create(pthId +i,NULL,pthreadFunc[i],&n);
	}
	for(int i = 0; i < 3; ++i)
	{
		pthread_join(pthId[i],NULL);
	}
	printf("sale voer\n");
	return 0;
}


