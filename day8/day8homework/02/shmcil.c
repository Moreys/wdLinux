#include <headFile.h>
int main()
{
	int shmid;
	shmid = shmget(2000,4096,0666|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmget");
	int ret;
	ret = shmctl(shmid,IPC_RMID,NULL);
	ERROR_CHECK(ret,-1,"shmctl");
	return 0;
}
