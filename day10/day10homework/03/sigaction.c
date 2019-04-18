//sigaction实现2号信号，屏蔽3号信号的执行效果，同时在2号信号的信号处理流程中，判断3号信号是否被挂起
#include<headFile.h>
//sigaction信号的处理函数 在函数捕捉信号的时候必须传入的为该函数的指针 是根据结构体函数来确定需要传入的参数的值的
void sigFun(int signum,siginfo_t *p,void *p1)
{
	printf("%d 开始阻塞\n",signum);
	sleep(10);
	sigset_t pending;//定义接收要挂起的参数
	sigpending(&pending);//将信号挂起
	if(sigismember(&pending,SIGQUIT))//sigismember 判断set里面是否有某个信号
	{
		printf("%d被阻塞\n",SIGQUIT);
	}
	else
	{
		printf("%d没有被阻塞\n",SIGQUIT);
	}
	printf("%d 阻塞结束\n",signum);
}
int main()
{
	int ret;//用于承接sigaction的返回值
	struct sigaction act;//参数2所使用的sigaction结构体
	
	bzero(&act,sizeof(act));//初始化结构体
	act.sa_sigaction = sigFun;//新类型的信号处理函数指针
	act.sa_flags =SA_SIGINFO;//阻塞某个系统函数调用
	//往set里面添加信号
	sigaddset(&act.sa_mask,SIGQUIT);//添加要阻塞的信号
	/*
		sigaction 接收信号并处理
		参数1 需要接收的信号
		参数2 结构体  
			老类型的函数处理指针
			新类型的函数处理指针
			将要被阻塞的信号集合
			信号处理方式掩码

		参数3 传出参数  参数2 的处理函数成功以后 包含以前处理函数的信息， 一般不用 直接用NULL
		函数返回  成功返回0 失败返回-1
	   */
	ret = sigaction(SIGINT,&act,NULL);//接收二号信号
	ERROR_CHECK(ret,-1,"sigaction");
	ret = sigaction(SIGQUIT,&act,NULL);//接收三号信号  也是在同一的处理函数里面判断是否被挂起，只不过都是利用sigaction进行调用
	ERROR_CHECK(ret,-1,"sigaction");
	while(1);
}
                       
