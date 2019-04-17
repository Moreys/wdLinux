#include<headFile.h>
#define N 2000000
int main()
{
	int shmid = shmget(1000,4096,0600|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmid");
	int *pShm;
	pShm =(int*) shmat(shmid,NULL,0);
	ERROR_CHECK(pShm,-1,"shmat");
	int semid = semget(1000,1,0600|IPC_CREAT);
	ERROR_CHECK(semid,-1,"semget");
	int ret = semctl(semid,0,SETVAL,1);
	ERROR_CHECK(ret,-1,"semctl");
	struct sembuf popp,popv;
	popp.sem_num = 0;
	popp.sem_op = -1;
	popp.sem_flg = SEM_UNDO;
	popv.sem_num = 0;
	popv.sem_op = 1;
	popv.sem_flg = SEM_UNDO;
	*pShm = N;
	int number =0,number1 = 0;
	if(fork()== 0)
	{
		while(1)
		{
			semop(semid,&popp,1);//加锁
			if(0 == *pShm)
			{
		printf("number = %d\n",number);
				break;
			}
			pShm[0]--;
			number++;
			semop(semid,&popv,1);
		}
	}
	else
	{
		while(1)
		{
			semop(semid,&popp,1);
			if(0 == *pShm)
			{
		printf("number1 = %d\n",number1);
				break;
			}
			pShm[0]--;
			number1++;
			semop(semid,&popv,1);
		}
	}
}

