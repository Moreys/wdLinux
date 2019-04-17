#include<headFile.h>
int main()
{
	int semid = semget(1000,2,IPC_CREAT|0600);
	int ret;
	unsigned short arr[2] = {20,0};//信号量代表仓库位置个数，1号信号量代表产品数目
	ret = semctl(semid,0,SETALL,arr);
	struct sembuf sopp,sopv;
	if(fork()==0)
	{
		//消费
		sopp.sem_num = 0;
		sopp.sem_op = -1;
		sopp.sem_flg = 0;
		sopv.sem_num = 1;
		sopv.sem_op = 1;
		sopv.sem_flg = 0;
		while(1)
		{
			printf("I am customer1 productor = %d,space = %d\n",semctl(semid,1,GETVAL),semctl(semid,0,GETVAL));
			semop(semid,&sopp,1);
			printf("I will consume\n");
			semop(semid,&sopv,1);
			printf("I am custormer,productor =%d,space = %d\n",semctl(semid,1,GETVAL),semctl(semid,0,GETVAL));
			sleep(1);
		}
	}
	else
	{
		sopp.sem_num = 1;
		sopp.sem_op = -1;
		sopp.sem_flg = 0;
		sopv.sem_num = 0;
		sopv.sem_op = 1;
		sopv.sem_flg = 0;
		while(1)
		{
			printf("I am customer2 productor = %d,space = %d\n",semctl(semid,1,GETVAL),semctl(semid,0,GETVAL));
			semop(semid,&sopp,1);
			printf("I will consume\n");
			semop(semid,&sopv,1);
			printf("I am custormer,productor =%d,space = %d\n",semctl(semid,1,GETVAL),semctl(semid,0,GETVAL));
			sleep(2);
		}
	}
	return 0;
}
