#include<headFile.h>
//打印结构体内容和设置内容
int main()
{
	int semid = semget(1000,2,IPC_CREAT|0600);
	struct semid_ds buf;
	int ret = semctl(semid,0,IPC_STAT,&buf);
	//打印内容
	printf("mode = %o,sem_nsems = %ld,\n",buf.sem_perm.mode,buf.sem_nsems);
	//从新设置mode的权限
	buf.sem_perm.mode = 0666;
	semctl(semid,0,IPC_SET,&buf);
	return 0;
}

