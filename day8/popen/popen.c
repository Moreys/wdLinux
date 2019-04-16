#include <headFile.h>
int main()
{
	FILE *fp;
	fp = popen("./print","r");//打开print可执行文件
	char buf[128] = {0};
	fgets(buf,sizeof(buf),fp);
	printf("buf = %s\n",buf);
	pclose(fp);
	return 0;
}
