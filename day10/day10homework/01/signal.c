//1、signal设置信号处理行为，演示不同信号到来时，后来的信号会打断原有信号的信号处理函数效果
#include <headFile.h>
void signalFunc(int signum)
{
	printf("信号处理前被打印，%d\n",signum);
	sleep(10);
	printf("信号处理后被打印，%d\n",signum);
}

int main()
{
	if(signal(SIGINT,signalFunc) == SIG_ERR)
	{
		perror("signal");
		return -1;
	}
	signal(SIGQUIT,signalFunc);
	while(1);
}
