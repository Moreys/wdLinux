#include<headFile.h>
//使用子线程读取文件里面的内容
void *threadFunc(void *p)
{
	//int fd =*p;//接收文件先将void* 强转int* 在进行解引用取得里面的值
	close(p);
	printf("I am child thread\n");
	return NULL;
}

int main()
{
	pthread_t thread;
    int ret;
	int fd = open("file",O_RDWR);
	ret = pthread_create(&thread,NULL,threadFunc,&fd);
	if(ret != 0)
	{
		printf("pthread_create:%s\n",strerror(ret));
		return -1;
	}
	ret = pthread_join(thread,NULL);
	char buf[128] = {0};
	ret = read(fd,buf,sizeof(buf));
	printf("I am main thread%d,%s\n",ret,buf);
	return 0;
}
