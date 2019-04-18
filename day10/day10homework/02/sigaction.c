//igaction实现信号不断重入的执行效果
#include<headFile.h>
//sigaction信号的处理函数 在函数捕捉信号的时候必须传入的为该函数的指针 是根据结构体函数来确定需要传入的参数的值的
void sigFun(int signum,siginfo_t *p,void *p1)
{
	printf("%d 开始执行\n",signum);
	sleep(10);
	printf("%d执行结束\n",signum);
}
void sigFun1(int signum)
{
	printf("%d信号进入\n",signum);
}

int main()
{
	int ret;//用于承接sigaction的返回值
	struct sigaction act;//参数2所使用的sigaction结构体
	bzero(&act,sizeof(act));//初始化结构体
	act.sa_sigaction = sigFun;//新类型的信号处理函数指针
	act.sa_flags = SA_NODEFER;//在处理信号的时候，如果发生了其他的信号，则立即进入其他信号的处理，其他处理完毕再处理自己的，不断重入，次数不丢失
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
	ret = sigaction(SIGINT,&act,NULL);
	ERROR_CHECK(ret,-1,"sigaction");
	signal(SIGQUIT,sigFun1);
	while(1);
	return 0;
}
                       
