#include<headFile.h>

typedef struct
{
	int tickets;//票
	pthread_mutex_t mutex;//锁
}Train;

void *saleWin1(void *args)
{
	Train *pSale = (Train*)args;
	int count = 0;
	while(1)
	{
		pthread_mutex_lock(&pSale->mutex);
		if(pSale->tickets>0)
		{
			pSale->tickets--;
			count++;
			pthread_mutex_unlock(&pSale->mutex);
		}
		else
		{
			pthread_mutex_unlock(&pSale->mutex);
			printf("I am wind1 sale %d\n",count);
			break;
		}
	}
	return NULL;
}
void *saleWin2(void *args)
{
	Train *pSale = (Train*)args;
	int count = 0;
	while(1)
	{
		pthread_mutex_lock(&pSale->mutex);
		if(pSale->tickets>0)
		{
			pSale->tickets--;
			count++;
			pthread_mutex_unlock(&pSale->mutex);
		}
		else
		{
			pthread_mutex_unlock(&pSale->mutex);
			printf("I am win2 sale %d\n",count);
			break;
		}
	}
	return NULL;
}
typedef void* (*threadFunc)(void*);
int main()
{
	Train t;
	pthread_t pthId[2];
	int i;
	t.tickets = 20000000;
	threadFunc pthreadFunc[2] = {saleWin1,saleWin2};
	pthread_mutex_init(&t.mutex,NULL);
	for(i = 0; i < 2;i++)
	{
		pthread_create(pthId +i ,NULL,pthreadFunc[i],&t);
	}
	for(i = 0;i<2;++i)
	{
		pthread_join(pthId[i],NULL);
	}
	printf("sale over\n");
}
