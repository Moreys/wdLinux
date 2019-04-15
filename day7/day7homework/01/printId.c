#include <headFile.h>

int main()
{
	printf("pid = %d,ppid =%d,uid = %d,gid = %d,euid = %d,egid = %d",getpid(),getppid(),getuid(),getgid(),geteuid(),getegid());
	return 0;
}
