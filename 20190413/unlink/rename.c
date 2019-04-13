#include <headFile.h>
//实现移动文件的操作，其实就是在外面建立一个硬链接，然后删除本文将的硬链接
int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,3);
	int ret;
	//接口作用 移动文件，其实就是先建立连接然后删除原来的连接
	//参数必须完整的地址
	ret = rename(argv[1],argv[2]);
	ERROR_CHECK(ret,-1,"rename");
	return 0;
}
