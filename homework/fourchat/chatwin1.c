#include<headFile.h>
struct content
{
	char buf[1024];
	char buf2[1024];
};
int main()
{
	int shmid = shmget(1000,4096,0600|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmget");
	struct content *pNt = (struct content*)shmat(shmid,NULL,0);
	while(1)
	{
		if(0 ==shmid)
		{
			exit(0);
			return 0;
		}
		while(strlen(pNt->buf)>0||strlen(pNt->buf2)>0)
		{
			if(0 ==shmid)
			{
				exit(0);
				return 0;
			}
			printf("%s\n",pNt->buf);
			memset(pNt->buf,0,sizeof(pNt->buf));
			printf("%40s\n",pNt->buf2);
			memset(pNt->buf2,0,sizeof(pNt->buf2));
		}
	}
}
