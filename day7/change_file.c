#include <headFile.h>

int main(int argc,char **argv)
{
	printf("uid = %d,gid = %d,euid = %d,egid = %d\n",getuid(),getgid(),geteuid(),getegid());
	int fd = open("file",O_RDWR);
	write(fd,"hello",5);
	return 0;
	
}
