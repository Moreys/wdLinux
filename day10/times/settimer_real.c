//5、使用真实计时器，实用计时器，虚拟计时器，统计程序执行时间，在实用计时器及虚拟计时器设定计时后，先睡眠，再让程序处于while（1）
#include <headFile.h>
#include <sys/time.h>
void sigFunc(int signum)
{
	time_t now;
	now = time(NULL);
	printf("%s\n",ctime(&now));
}

int main()
{
	signal(SIGALRM,sigFunc);//定时器超时
	struct itimerval t;
	bzero(&t,sizeof(t));
	t.it_value.tv_sec = 3;
	t.it_interval.tv_sec = 2;
	int ret;
	sigFunc(0);
	ret = setitimer(ITIMER_REAL,&t,NULL);
	ERROR_CHECK(ret,-1,"setitimer");
	char buf[128] = {0};
	read(STDIN_FILENO,buf,sizeof(buf));
	printf("buf = %s\n",buf);
	sleep(5);
	while(1);
}
