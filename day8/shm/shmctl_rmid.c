#include <headFile.h>
//删除共享函数
int main()
{
   	int shmid;
   	shmid = shmget(1000,4096,0600|IPC_CREAT);
   	ERROR_CHECK(shmid,-1,"shmget");
   	int ret;
   	//shmctl功能：删除共享内存
	/*
	   参数1 共享内存段标识 shmget的返回值
	   参数2 对共享内存段的操作方式 通常使用IPC_RMID
	   参数3 信息结构体数据 一般用NULL */
	ret = shmctl(shmid,IPC_RMID,NULL);
	ERROR_CHECK(ret,-1,"shmctl");
	return 0;
}
