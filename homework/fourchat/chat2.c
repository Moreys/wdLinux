#include<headFile.h>
#define N 1023
struct content
{
	long mtype;
	char buf[N +1];
};
int main(int argc,char **argv)
{
	int fdr,fdw;
	ARGC_CHECK(argc,3);
	fdw = open(argv[1],O_WRONLY);
	ERROR_CHECK(fdw,-1,"open");
	fdr = open(argv[2],O_RDONLY);
	ERROR_CHECK(fdr,-1,"open");
	printf("fdw = %d,fdr = %d\n",fdw,fdr);
	int msgid = msgget((key_t)1000,0666|IPC_CREAT);
	ERROR_CHECK(msgid,-1,"msgget");
	struct content Nt;
	memset(&Nt,0,sizeof(struct content));

	char buf[128] = {0};
	int ret;
	fd_set readfds;
	while(1)
	{
		FD_ZERO(&readfds);
		FD_SET(STDIN_FILENO,&readfds);
		FD_SET(fdr,&readfds);
		ret = select(fdr+1,&readfds,NULL,NULL,NULL);
		if(ret >0 )
		{
			if(FD_ISSET(fdr,&readfds))
			{
				memset(buf,0,sizeof(buf));
				ret = read(fdr,buf,sizeof(buf));
				memset(Nt.buf,0,sizeof(Nt.buf));
				Nt.mtype = 1;
				strncpy(Nt.buf,buf,N);
				msgsnd(msgid,&Nt,strlen(Nt.buf),0);	
				if(0 == ret)
				{
					printf("再见！！\n");
					msgctl(msgid,IPC_RMID,NULL);
					break;
				}
				//				printf("%s\n",buf);
			}
			if(FD_ISSET(0,&readfds))
			{
				memset(buf,0,sizeof(buf));
				ret = read(0,buf,sizeof(buf));
				if(0==ret)
				{
					printf("退出\n");
					msgctl(msgid,IPC_RMID,NULL);
					break;
				}
				write(fdw,buf,strlen(buf)-1);
				memset(Nt.buf,0,sizeof(Nt.buf));
				Nt.mtype = 2;
				strncpy(Nt.buf,buf,N);
				msgsnd(msgid,&Nt,strlen(Nt.buf),0);
			}
		}
	}
	close(fdr);
	close(fdw);
	return 0;
}
