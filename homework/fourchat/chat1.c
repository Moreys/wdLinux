#include <headFile.h>
struct content
{
	char buf[1024];
	char buf2[1024];
};
int main(int argc,char **argv)
{
	int fdr,fdw;
	ARGC_CHECK(argc,3);
	fdr = open(argv[1],O_RDONLY);
	ERROR_CHECK(fdr,-1,"open");
	fdw = open(argv[2],O_WRONLY);
	ERROR_CHECK(fdw,-1,"open");
	printf("fdw = %d,fdr = %d\n",fdw,fdr);
	int shmid = shmget(1000,4096,0600|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmget");
	struct content *pTn = (struct content *)shmat(shmid,NULL,0);
	char buf[128] = {0};
	//	使用select接口int select(int maxfdp, fd_set *readset, fd_set *writeset, fd_set *exceptset,struct timeval *timeout);
	fd_set readset;
	int ret;
	struct timeval time;
	while(1)
	{
		FD_ZERO(&readset);
		FD_SET(STDIN_FILENO,&readset);
		FD_SET(fdr,&readset);
		memset(&time,0,sizeof(time));
		time.tv_sec = 3;
		ret = select(fdr+1,&readset,NULL,NULL,&time);
		
		if(ret>0)
		{
			if(FD_ISSET(fdr,&readset))
			{
				memset(buf,0,sizeof(buf));
				ret = read(fdr,buf,sizeof(buf));
				memset(pTn->buf,0,strlen(pTn->buf));
				//读到以后直接放到共享内存
				strncpy(pTn->buf,buf,strlen(buf));
				if(0 == ret)
				{
					printf("再见！！\n");
					shmctl(shmid,IPC_RMID,NULL);
					break;
				}
//				printf("%s\n",buf);
			}
			if(FD_ISSET(0,&readset))
			{
				memset(buf,0,sizeof(buf));
				ret = read(0,buf,sizeof(buf));
				//memset(pTn->buf,0,strlen(pTn->buf));
				//读到以后直接放到共享内存
				//strncpy(pTn->buf,buf,strlen(buf));
				if(0 == ret)
				{
					printf("退出再见\n");
					shmctl(shmid,IPC_RMID,NULL);
					break;
				}
			 write(fdw,buf,strlen(buf)-1);
				memset(pTn->buf2,0,strlen(pTn->buf2));
			 strncpy(pTn->buf2,buf,strlen(buf)-1);
			}
		}
	}
	close(fdw);
	close(fdr);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}	
