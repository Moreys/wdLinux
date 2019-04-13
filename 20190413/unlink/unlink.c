#include <headFile.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	int ret;
	ret = unlink(argv[1]);
	return 0;
}
