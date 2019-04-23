#include<headFile.h>
//使用的时候必须有网：
//域名转ip  ip转域名
int main(int argc,char **argv)
{
	ARGC_CHECK(argc,2);
	struct hostent *p;
	p = gethostbyname(argv[1]);
	printf("%s\n",p->h_name);
	int i ;
	//将域名转换为ip
	/*
	   将域名转为ip
	   struct hostent *gethostbyname(const char *name);
		将ip转为域名或者主机名
	   struct hostent *gethostbyaddr(const void *addr,socklen_t len, int type);
	   struct hostent {
	   char  *h_name;            主机名字
	   char **h_aliases;      主机别名 
	   int    h_addrtype;  主机ip类型 
	   int    h_length;     主机ip地址字节长度 
	   char **h_addr_list;    主机ip地址
	   }

	 */
	for(i = 0 ;p->h_aliases[i] != NULL;i++)
	{
		printf("%s\n",p->h_aliases[i]);
	}
	printf("%d\n",p->h_addrtype);
	printf("%d\n",p->h_length);
	char ip[16] = {0};
	for(i = 0; p->h_addr_list[i] != NULL;++i)
	{
		memset(ip,0,sizeof(ip));
		inet_ntop(p->h_addrtype,p->h_addr_list[i],ip,sizeof(ip));//从 ip 转为点分时进制
		printf("%s\n",ip);
	}
	return 0;
}


