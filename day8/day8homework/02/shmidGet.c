#include<headFile.h>

int main()
{
	int shmid;
	shmid = shmget(2000,4096,0666|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmget");
	char *pShm;
	pShm = (char*)shmat(shmid,NULL,0);
	ERROR_CHECK(pShm,(char*)-1,"shmat");
	printf("%s\n",pShm);
	return 0;
}
	
