#include <headFile.h>

int main()
{
	//定义接收值
	//创建共享内存
	//判断是否有错误
	//判断返回值
	//定义字符指针
	//开启映射
	//将内容拷贝进去
	//返回

	//同上5
	//打印内容
	
	//同上3
	//定义接收删除的返回承接变量
	//进行删除
	//判断是否有错误
	//返回

	int shmid;
	shmid = shmget(2000,4096,0666|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmget");
	char *pShm;
	pShm =(char*)shmat(shmid,NULL,0);
	ERROR_CHECK(pShm,(char*)-1,"shmat");
	strcpy(pShm,"How are you");
	return 0;
}
