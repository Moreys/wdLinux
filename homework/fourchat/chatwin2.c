#include<headFile.h>
#define N 1023
struct content
{
	long mtype;
	char buf[N +1];
};
int main()
{
	int msgid = msgget((key_t)1000,0666|IPC_CREAT);
	ERROR_CHECK(msgid,-1,"msgget");
	struct content Nt;
	memset(&Nt,0,sizeof(struct content));
	while(1)
	{
		if(0 == msgid)
		{
			exit(0);
			return 0;
		}
		memset(Nt.buf,0,sizeof(Nt));
		msgrcv(msgid,&Nt,sizeof(Nt.buf),0,0);
		if(Nt.mtype == 1)
		{
		fprintf(stdout,"%s\n",Nt.buf);
		Nt.mtype = 0;
		}
		if(2 == Nt.mtype)
		{
		fprintf(stdout,"%40s\n",Nt.buf);
		Nt.mtype = 0;
		}
	}
	exit(0);
}

