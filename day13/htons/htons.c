#include<headFile.h>
int main()
{
	short port = 0x1234;
	short nport = 0;
	nport = htons(port);//主机字节序转为网络字节序
	printf("%x\n",nport);
	port = 0;
	port = ntohs(nport);//网络字节序转为主机字节序
	printf("%x\n",port);
}
