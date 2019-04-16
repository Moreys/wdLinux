#include <headFile.h>

int main()
{
	/*
	   无名管道 
	   1只能在亲缘关系下进程通信
	   2半双工
	   3有特殊的文件，只能在内存中进行
	 */
	//在程序中用文件描述符进行表示 一个可读一个可写
	//fds[0]读  fds[1]写
	//定义管道 int型数组
	//开启管道 使用pipe函数
	//开始子进程
	//子进程
	//关闭写管道
	//定义字符数组 初始化为0
	//通过管道读数据
	//打印读到的信息
	//父亲进程
	//关闭读管道
	//写文件
	//等待子进程结束
	//返回
	int fds[2];
	pipe(fds);
	if(fork() == 0)
	{
		close(fds[0]);//关闭读端
		write(fds[1],"hello",5);
	}
	else
	{
		sleep(1);
		close(fds[1]);
		char buf[128] = {0};
		read(fds[0],buf,sizeof(buf));
		printf("parent gets %s\n",buf);
		wait(NULL);
		return 0;	
	}
}

