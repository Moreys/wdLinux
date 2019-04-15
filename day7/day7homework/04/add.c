#include <headFile.h>
int main(int argc,char **argv)
{
	int number1 = atoi(argv[1]);
	int number2 = atoi(argv[2]);
	printf("%d + %d = %d\n",number1,number2,number1+number2);
	return 0;
}
