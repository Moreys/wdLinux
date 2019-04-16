#include<headFile.h>
#define N 10000000

int main()
{
	int shmid;
	shmid = shmget(1000,4096,0600|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmget");
	int *pShm;
	pShm = (int*)shmat(shmid,NULL,0);
	ERROR_CHECK(pShm,-1,"shmat");	
	*pShm = 0;
	if(!fork())
	{
		for(int i = 0; i < N;++i)
		{
			pShm[0] += 1;
		}
		return 0;
	}
	else
	{
		for(int i = 0;i < N; ++i)
		{
			pShm[0] += 1;
		}
		wait(NULL);
		printf("sum = %d\n",*pShm);
		return 0;
	}
}
