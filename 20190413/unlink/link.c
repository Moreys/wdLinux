#include <headFile.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,3);
	int ret;
	//建立连接，传入的地址必须是完成的，不能只写一个...
	ret = link(argv[1],argv[2]);
	ERROR_CHECK(ret,-1,"link");
	return 0;
}
