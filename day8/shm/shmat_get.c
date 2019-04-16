#include<headFile.h>
int main()
{
	int shmid;
	shmid = shmget(1000,4096,0600|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmget");
	char *pShm;
	pShm = (char*)shmat(shmid,NULL,0);
	ERROR_CHECK(pShm,(char*)-1,"shmat");
	//读取共享内存的时候跟写和创建一样，只不过将写内容变成读内容
	printf("%s\n",pShm);
	return 0;
}
