#include<headFile.h>

int main(int argc,char **argv)
{
	ARGC_CHECK(argc,2);
	//定义需要转换的结构体
	struct in_addr addr;
	int ret;
	//函数原型
	//int inet_aton(const char *cp, struct in_addr *inp);
	//函数功能 将点分十进制的，转为整型，
	//参数1 点分十进制
	//参数2 传出参数
	ret = inet_aton(argv[1],&addr);
	printf("%x\n",addr.s_addr);
	//inet——ntoa32为地址转为点分十进制，参数为结构体
	printf("ip = %s\n",inet_ntoa(addr));
	//点分十进制转为32为ip地址少一个参数，比较方便
	printf("%x\n",inet_addr(argv[1]));
	return 0;
}
