#include<headFile.h>
#define N 1000000
int main()
{
	int shmid = shmget(1000,4096,0600|IPC_CREAT);
	int *pShm;
	pShm =(int*) shmat(shmid,NULL,0);
	int semid = semget(1000,1,0600|IPC_CREAT);
	int ret = semctl(semid,0,GETVAL,1);
	struct sembuf popp,popv;
	popp.sem_num = 0;
	popp.sem_op = -1;
	popp.sem_flg = SEM_UNDO;
	popv.sem_num = 0;
	popv.sem_op = 1;
	popv.sem_flg = SEM_UNDO;
	*pShm = 0;
	if(!fork())
	{
		for(int i = 0; i < N; ++i)
		{
			semop(semid,&popp,1);//加锁
			pShm[0] += 1;
			semop(semid,&popv,1);
		}
		return 0;
	}
	else
	{
		for(int i = 0; i < N; ++i)
		{
			semop(semid,&popp,1);
			pShm[0] += 1;
			semop(semid,&popv,1);
		}
		wait(NULL);
		printf("sum = %d\n",*pShm);
		return 0;

	}
}

		

