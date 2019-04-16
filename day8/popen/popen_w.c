#include <headFile.h>

//popen计算两个数和
int main()
{
	FILE *fp;
	/*  popen 用于管道工作
		参数1 一般为有输出结果，或者输入的程序
		参数2 两种模式 读 写
		写：参数1输出结果 作为当前进程输入结果
		读：参数2 输出结果  作为参数1的输入结果

		r  文件流  新进程   标准输出
		w 文件流  新进程   标准输入
	 */
	fp = popen("./scanf","w");
	ERROR_CHECK(fp,NULL,"popen");
	char buf[128] = "3 4";
	fputs(buf,fp);
	pclose(fp);
	return 0;
}

