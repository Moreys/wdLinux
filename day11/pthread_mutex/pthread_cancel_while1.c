#include<headFile.h>
void *threadFunc(void *p)
{
	while(1);
}
int main()
{
	pthread_t pthID;
	pthread_create(&pthID,NULL,threadFunc,NULL);
	int ret = pthread_cancel(pthID);
	pthread_join(pthID,NULL);
	return 0;
}
