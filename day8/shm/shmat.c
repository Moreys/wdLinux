#include<headFile.h>
#include<sys/ipc.h>
#include<sys/shm.h>
int main()
{
	int shmid;
	/*
	shmget功能：创建或打开一段共享内存j
	参数1 共享内存相关联的关键字
	参数2 共享内存大小  最小4k的大小 常用4k的倍数
	参数3 权限 后面跟IPC_CRET不存在就创建 IPC_EXCL存在则返回失败结果 -1
	返回值：成功返回内存标识段
			否则返回-1
	   */
	shmid = shmget(1000,4096,0600|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmget");
	char *pShm;
	/*
	shmat功能：将共享内存映射到进程空间的某一地址
	参数1 共享内存标识
	参数2 映射的地址  一般填NULL
	参数3 一组标识符   通常使用0
	返回值：成功返回进程空间首地址，否则返回-1
	   */
	pShm = (char*)shmat(shmid,NULL,0);
	ERROR_CHECK(pShm,(char*)-1,"shmat");
	strcpy(pShm,"hello");
	return 0;
}
