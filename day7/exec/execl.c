#include <headFile.h>
int main()
{
	const char *envp[] = {"PATH=/usr/bin",NULL};
	int ret = execle("./chang_env","change_env","first","second",NULL,envp);
	printf("you can't see me\n");
}
