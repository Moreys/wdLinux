#include<headFile.h>

int main()
{
	int shmid = shmget(1000,4096,0600|IPC_CREAT);
	int ret = shmctl(shmid,IPC_RMID,NULL);
	int semid = semget(1000,0,0600|IPC_CREAT);
	int ret1 = semctl(semid,0,IPC_RMID);
	printf("ret = %d,ret1 = %d\n",ret,ret1);
}
