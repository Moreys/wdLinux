#include "studentlink.h"

void system_init( char* config_file_name, pUSR_ACCOUNT  *pUsr_Acount, pUSR_INFOR *pUsr_Infor)
{
	//读取到的文件
	 char *name = config_file_name;
	pUSR_ACCOUNT paHead = *pUsr_Acount;
	pUSR_ACCOUNT paTail = *pUsr_Acount;
	pUSR_INFOR psHead = *pUsr_Infor;
	pUSR_INFOR psTail = *pUsr_Infor;
	char buf[128] = {0};
	char *buf2[3] = { 0 };
	split(name, ",", buf2);
	FILE *fps;
	FILE *fpa;
	char *str1 = buf2[0];
	char *str2 = buf2[1];
	fpa = fopen(str1, "r+");
	fps = fopen(str2, "r+");
	//转换
	USR_INFOR ps;
	USR_ACCOUNT pa;
	while (fscanf(fpa, "%s%s%d", pa.usr_name, pa.usr_pwd, &pa.usr_role) != EOF)
	{
		insertAccount(&paHead, &paTail, &pa);
	}
	while (fscanf(fps, "%d%s%d%f", &ps.usr_id, ps.usr_name, &ps.usr_course_id, &ps.usr_course_score) != EOF)
	{
		insertStudent(&psHead, &psTail, &ps);
	}
	*pUsr_Acount = paHead;
	*pUsr_Infor = psHead;
}


/*插入管理员信息
 * 成功返回1，失败返回0
 * 参数1：插入的结构体，参数2：数据来源
 */
int insertAccount(pUSR_ACCOUNT* ppHead, pUSR_ACCOUNT* ppTail, pUSR_ACCOUNT link)
{
	pUSR_ACCOUNT newNode = (pUSR_ACCOUNT)malloc(sizeof(USR_ACCOUNT));//结构体里面有字符，所有重新分配的时候不能赋初始值，不然后面字符赋值的时候回访问常量区
	strcpy(newNode->usr_name, link->usr_name);
	strcpy(newNode->usr_pwd, link->usr_pwd);
	newNode->usr_role = link->usr_role;
	pUSR_ACCOUNT pTemp = *ppTail;
	if (NULL == *ppHead)
	{
		*ppHead = newNode;
		*ppTail = newNode;
		return 1;
	}
	else
	{
		pTemp->pNext_Usr_Account = newNode;
		*ppTail = newNode;
		newNode->pNext_Usr_Account = NULL;
		return 1;
	}
	printf("插入失败！");
	return 0;
}


/*插入学生信息
  * 成功返回1，失败返回0
  * 参数1：插入的结构体，参数2：数据来源
  */
void insertStudent(pUSR_INFOR* ppHead, pUSR_INFOR *ppTail, pUSR_INFOR link)
{
	pUSR_INFOR newNode = (pUSR_INFOR)calloc(1, sizeof(USR_INFOR));//结构体里面有字符，所有重新分配的时候不能赋初始值，不然后面字符赋值的时候回访问常量区
	newNode->usr_id = link->usr_id;
	strcpy(newNode->usr_name, link->usr_name);
	newNode->usr_course_id = link->usr_course_id;
	newNode->usr_course_score = link->usr_course_score;
	pUSR_INFOR pPre, pCurr;

	pPre = pCurr = *ppHead;

	if (NULL == *ppHead)
	{
		*ppHead = newNode;
		*ppTail = newNode;
		return;
	}
	else if (link->usr_id < pCurr->usr_id)
	{
		newNode->pNext_Usr_Infor = *ppHead;
		*ppHead = newNode;
		return;
	}
	else
	{
 		while (pCurr)//&& //link->usr_id != pCurr->usr_id
		{
			if (link->usr_id < pCurr->usr_id) //
			{
				pPre->pNext_Usr_Infor = newNode;
				newNode->pNext_Usr_Infor = pCurr;
				return;
			}
			pPre = pCurr;
			pCurr = pCurr->pNext_Usr_Infor;
		}
		if (pCurr == NULL)
		{
			pPre->pNext_Usr_Infor = newNode;
			*ppTail = newNode;
		}
		return;
	}
}


//菜单打印
int menuAcc()
{
	int num;
	printf("***************************************\n");
	printf("***************************************\n");
	printf("          学生管理系统——教师端           \n");
	printf("****************************************\n");
	printf("*            1、查询学生信息           *\n");
	printf("*            2、增加学生信息           *\n");
	printf("*            3、更新学生信息           *\n");
	printf("*            4、删除学生信息           *\n");
	printf("*            5、增加用户信息           *\n");
	printf("*            6、更新用户信息           *\n");
	printf("*            7、删除用户信息           *\n");
	printf("*            8、查询用户信息           *\n");
	printf("*            9、退出系统               *\n");
	printf("****************************************\n");
	printf("************请输入需要查找的命令********\n");
	scanf("%d", &num);
	while (rewind(stdin), num > 10 || num < 0)
	{
		printf("输入错误请查询输入:\n");
		scanf("%d", &num);
	}
	return num;
}

int menuStu()
{
	int num;
	printf("*************************************************\n");
	printf("*************************************************\n");
	printf("             学生管理系统——学生端               \n");
	printf("*************************************************\n");
	printf("*            1、输入学号查询学生信息            *\n");
	printf("*            2、输入姓名查询学生信息            *\n");
	printf("*            3、退出系统                        *\n");
	printf("*************************************************\n");
	printf("****************请输入需要查找的命令*************\n");
	scanf("%d", &num);
	while (rewind(stdin), num > 4 || num < 0)
	{
		printf("输入错误请查询输入:\n");
		scanf("%d", &num);
	}
	return num;
}

//显示学生文件
int showStudent(pUSR_INFOR link)
{
	int num;
	if (NULL == link)
	{
		printf("link is empty");
		return -1;
	}
	printf("学生信息显示如下\n");
	while (link)
	{
		printf("%4d  %6s %2d %-6.2f \n", link->usr_id, link->usr_name, link->usr_course_id, link->usr_course_score);
		link = link->pNext_Usr_Infor;
	}

	printf("显示完成！！按3返回:");
	scanf("%d", &num);
	while (rewind(stdin), num != 3)
	{
		printf("输入错误!请查询输入:");
		scanf("%d", &num);
	}
	return num;
}
//显示一个学生
int showStudentOne(pUSR_INFOR link)
{
	int num;
	if (NULL == link)
	{
		printf("link is empty");
		return -1;
	}
	printf("学生信息显示如下\n");
	while (link)
	{
		printf("%4d  %6s %2d %-6.2f \n", link->usr_id, link->usr_name, link->usr_course_id, link->usr_course_score);
		break;
	}
	printf("显示完成！！按3返回:");
	scanf("%d", &num);
	while (rewind(stdin), num != 3)
	{
		printf("输入错误!请查询输入:");
		scanf("%d", &num);
	}
	return num;
}

//显示用户信息
int showAvvount(pUSR_ACCOUNT link)
{
	int num;
	if (NULL == link)
	{
		printf("link is empty");
		return -1;
	}
	printf("用户显示如下\n");
	while (link)
	{
		printf("%4s  %4s %2d\n", link->usr_name, link->usr_pwd, link->usr_role);
		link = link->pNext_Usr_Account;
		/*fprintf(fp, "%4d %2s %6s %-6.2f %-6.2f %-6.2f \n", link->ID, link->six, link->name, link->chinese, link->math, link->english);
		link = link->pNext;*/
	}
	printf("显示完成！！按3返回:");
	scanf("%d", &num);
	while (rewind(stdin), num != 3)
	{
		printf("输入错误!请查询输入:");
		scanf("%d", &num);
	}
	return num;
}
int showAccountOne(pUSR_ACCOUNT link)
{
	if (link == NULL)
	{
		printf("用户信息为空！！");
		return  -1;
	}
	int number;
	while (link)
	{
		printf("%4s  %4s %2d\n", link->usr_name, link->usr_pwd, link->usr_role);
		break;
	}
	printf("显示完成！！按3返回:");
	scanf("%d", &number);
	while (rewind(stdin), number != 3)
	{
		printf("输入错误!请查询输入:");
		scanf("%d", &number);
	}
	return number;
}


//分割字符数组，存入到二维字符数组中
void split(char *src, const char *separator, char **dest) {
	/*
		src 源字符串的首地址(buf的地址)
		separator 指定的分割字符
		dest 接收子字符串的数组
		num 分割后子字符串的个数
	*/
	char *pNext;
	if (src == NULL || strlen(src) == 0) //如果传入的地址为空或长度为0，直接终止 
		return;
	if (separator == NULL || strlen(separator) == 0) //如未指定分割的字符串，直接终止 
		return;
	/*函数原型：char *strtok( char *str1, const char *str2 );
		功能：返回标记，返回字符串str1中紧接“标记”的部分的指针，字符串str2是作为标记的分隔符，如果分隔符没有找到，函数返回NULL 为了字符串标记，第一次调用str1指向作为标记的分隔符，之后所有的调用str1都应为NULL
	 *
	 */
	pNext = (char *)strtok(src, separator); //必须使用(char *)进行强制类型转换(虽然不写有的编译器中不会出现指针错误)
	while (pNext != NULL) {
		*dest++ = pNext;
		pNext = (char *)strtok(NULL, separator);  //必须使用(char *)进行强制类型转换
	}
}
//字符数组转为结构体
void charToAcc(char **str, pUSR_ACCOUNT s1)
{
	strcpy(s1->usr_name, str[0]);
	strcpy(s1->usr_pwd, str[1]);
	s1->usr_role = atoi(str[2]);
}


//增加学生信息
pUSR_INFOR add_usr_infor(pUSR_INFOR *ppUsr_Infor_List)
{
	pUSR_INFOR stu1 = *ppUsr_Infor_List;
	pUSR_INFOR pPrve = *ppUsr_Infor_List;  //记录前一个节点
	pUSR_INFOR pCurrent = stu1->pNext_Usr_Infor;//记录后一个节点	
	int number;
	char name[USR_NAME_LEN];
	int usr_course_id;
	float usr_score;
	printf("          增加学生信息          \n");
	printf("学号不超过6位，课程不超过号不超过20，分数不超过200\n");
	printf("请依次输入学号，姓名，课程号，课程分数\n");
	scanf("%d%s%d%f", &number, &name, &usr_course_id, &usr_score);
	if(number>1000000||strlen(name)>20||usr_course_id>20||usr_score>200)
	{
		printf("输入不符合规范，请重新输入！");
		return NULL;
	}
	while (stu1)//
	{
		if (stu1->usr_id == number)
		{
			printf("学号重复，请出现输入!\n");
			return NULL;
		}
		stu1 = stu1->pNext_Usr_Infor;
	}
	pUSR_INFOR newNode = (pUSR_INFOR)calloc(1, sizeof(USR_INFOR));
	newNode->usr_id = number;
	strcpy(newNode->usr_name, name);
	newNode->usr_course_id = usr_course_id;
	newNode->usr_course_score = usr_score;
	if (pPrve->usr_id < pCurrent->usr_id)
	{
		newNode->pNext_Usr_Infor = pPrve;
		*ppUsr_Infor_List = newNode;
		return  *ppUsr_Infor_List;
	}
	else
	{
		while (pCurrent)//&& //
		{
			if (newNode->usr_id < pCurrent->usr_id) //
			{
				pPrve->pNext_Usr_Infor = newNode;
				newNode->pNext_Usr_Infor = pCurrent;
				break;
			}
			pPrve = pCurrent;
			pCurrent = pCurrent->pNext_Usr_Infor;
		}
		if (pCurrent == NULL)
		{
			pPrve->pNext_Usr_Infor = newNode;
			pCurrent = newNode;
		}
	}
	//插入完毕写入文件	
	return newNode;
}

//保存学生信息
void  saveStuFILE(pUSR_INFOR link)
{
	FILE *fp;
	fp = fopen("Usr_infor.txt", "r+");
	fseek(fp, 0, SEEK_SET);
	if (NULL == link)
	{
		printf("link is empty");
		return;
	}
	while (link)
	{
		fprintf(fp, "%4d  %6s %2d %-6.2f \n", link->usr_id, link->usr_name, link->usr_course_id, link->usr_course_score);
		link = link->pNext_Usr_Infor;
	}
	fclose(fp);
	printf("学生信息保存完毕！\n");
	system("pause");
}

//保存用户信息
void  saveAccFILE(pUSR_ACCOUNT link)
{
	if (link == NULL)
	{
		printf("link is empty");
		return;
	}
	FILE *fp;
	fp = fopen("Usr_account.txt", "r+");
	fseek(fp, 0, SEEK_SET);
	while (link)
	{
		fprintf(fp, "%4s  %4s %2d\n", link->usr_name, link->usr_pwd, link->usr_role);
		link = link->pNext_Usr_Account;
	}
	fclose(fp);
	printf("用户信息保存完毕！\n");
	system("pause");
}

//根据输入的学号进行修改
pUSR_INFOR update_usr_infor(pUSR_INFOR pUsr_Infor_List, int search_id)
{
	if (pUsr_Infor_List == NULL)
	{
		printf("学生信息为空！");
		return NULL;
	}

	while (pUsr_Infor_List)
	{
		if (pUsr_Infor_List->usr_id == search_id)
		{
			char name[USR_NAME_LEN];
			int usr_course_id;
			float usr_score;
			printf("学号不超过6位，课程不超过号不超过20，分数不超过200\n");
			printf("请依次输入需要修改的姓名，课程号，课程分数\n");			
			scanf("%s%d%f", &name, &usr_course_id, &usr_score);
			if (strlen(name) > 20 || usr_course_id > 20 || usr_score > 200)
			{
				printf("输入不符合规范，请重新输入！");
				return NULL;
			}
			strcpy(pUsr_Infor_List->usr_name, name);
			pUsr_Infor_List->usr_course_id = usr_course_id;
			pUsr_Infor_List->usr_course_score = usr_score;
			return pUsr_Infor_List;
		}
		pUsr_Infor_List = pUsr_Infor_List->pNext_Usr_Infor;
	}
	printf("没有找到要修改的学号，请重新输入：");
	return  NULL;
}

//根据学号删除信息
/*先找到信息  需要辅助指针变量来存储要删除的信息
 */
pUSR_INFOR delete_usr_infor(pUSR_INFOR* ppUsr_Infor_List, int search_id)
{
	if (*ppUsr_Infor_List == NULL)
	{
		printf("学生信息为空！");
		return NULL;
	}
	pUSR_INFOR pPre, pCurr;
	pPre = pCurr = *ppUsr_Infor_List;
	//USR_INFOR Stu;
	printf("          删除学生信息          \n");
	if (pCurr->usr_id == search_id)
	{
		*ppUsr_Infor_List = pCurr->pNext_Usr_Infor;
		if (pCurr != NULL)
		{
			free(pCurr);
			pCurr = NULL;
		}
		//return pPre;
		printf("     删除成功，返回下一个学生信息     \n");
		return *ppUsr_Infor_List;
	}
	else
	{
		while (pCurr)
		{
			if (pCurr->usr_id == search_id)
			{
				pPre->pNext_Usr_Infor = pCurr->pNext_Usr_Infor;
				if (pCurr != NULL)
				{
					free(pCurr);
					pCurr = NULL;
				}
				printf("     删除成功，返回下一个学生信息     \n");
				return pPre->pNext_Usr_Infor;
			}
			pPre = pCurr;
			pCurr = pCurr->pNext_Usr_Infor;
		}

		if (pCurr == NULL)
		{
			printf("没有找到要删除的学生，请重新输入：");
			return  NULL;
		}
	}
	printf("没有找到要删除的学生，请重新输入：");
	return  NULL;
}



//增加用户信息
pUSR_ACCOUNT add_usr_account(pUSR_ACCOUNT* ppUsr_Account_List)
{
	pUSR_ACCOUNT acc = *ppUsr_Account_List;
	pUSR_ACCOUNT pPre = *ppUsr_Account_List;
	pUSR_ACCOUNT pCurr = pPre->pNext_Usr_Account;
	int number;
	char name[USR_NAME_LEN];
	char pwd[USR_PWD_LEN];
	printf("          增加用户信息          \n");
	printf("温馨提示：管理员类型不能超过2，用户名和密码不能超过20个字符\n");
	printf("请依次输入用户类型（1为管理员，2为普通用户），用户名，密码\n");
	scanf("%d%s%s", &number, &name, &pwd);
	if(number > 20 || strlen(name) > 20|| strlen(pwd) > 20)
	{
		printf("输入信息有误，请检查后再重新输入！\n");
		return NULL;
	}
	while (acc)
	{
		if (strcmp(acc->usr_name, name) == 0)
		{
			printf("用户名相同，请重新输入！");
			return NULL;
		}
		acc = acc->pNext_Usr_Account;
	}
	pUSR_ACCOUNT newNode = (pUSR_ACCOUNT)calloc(1, sizeof(USR_ACCOUNT));
	newNode->usr_role = number;
	strcpy(newNode->usr_name, name);
	strcpy(newNode->usr_pwd, pwd);
	if (0 > strcmp(pCurr->usr_name, newNode->usr_name) && strcmp(acc->usr_name, name) != 0)
	{
		pPre = newNode->pNext_Usr_Account;
		*ppUsr_Account_List = newNode;
		return  *ppUsr_Account_List;
	}
	else
	{
		while (pCurr)
		{
			if (strcmp(pCurr->usr_name, newNode->usr_name) > 0)
			{
				newNode->pNext_Usr_Account = pCurr;
				pPre->pNext_Usr_Account = newNode;
				return newNode;
			}
			pPre = pCurr;
			pCurr = pCurr->pNext_Usr_Account;
		}
		if (pCurr == NULL)
		{
			pPre->pNext_Usr_Account = newNode;
		}
	}
	return  newNode;
}

//修改用户信息
/*
 * 成功返回修改好的信息，
 * 失败返回空
 *
 */
pUSR_ACCOUNT update_usr_account(pUSR_ACCOUNT pUsr_Account_List, char* search_name)
{
	if (pUsr_Account_List == NULL || search_name == NULL)
	{
		printf("链表为空或用户名为空！！！请重新输入\n");
		return  NULL;
	}
	while (pUsr_Account_List)
	{
		if (strcmp(pUsr_Account_List->usr_name, search_name) == 0)
		{
			char name[USR_NAME_LEN];
			char pwd[USR_PWD_LEN];
			int idNumber;
			printf("         用户信息修改\n");
			printf("温馨提示：管理员类型不能超过2，用户名和密码不能超过20个字符\n");
			printf("请依次输入:1用户名  2密码  3用户类型（1为管理员，2为普通用户），\n");
			scanf("%s%s%d", &name, &pwd, &idNumber);
			if (idNumber > 20 || strlen(name) > 20 || strlen(pwd) > 20)
			{
				printf("输入信息有误，请检查后再重新输入！\n");
				return NULL;
			}
			strcpy(pUsr_Account_List->usr_name, name);
			strcpy(pUsr_Account_List->usr_pwd, pwd);
			pUsr_Account_List->usr_role = idNumber;
			return pUsr_Account_List;
		}
		pUsr_Account_List = pUsr_Account_List->pNext_Usr_Account;
	}
	printf("     没有找到需要修改的用户名！\n");
	printf("     请重新输入\n");
	return  NULL;
}

//删除用户信息
pUSR_ACCOUNT delete_usr_account(pUSR_ACCOUNT* ppUsr_Account_List, char* search_name)
{
	if (*ppUsr_Account_List == NULL || search_name == NULL)
	{
		printf("用户表为空或者用户名为空,请重新输入\n");
		return  NULL;
	}
	pUSR_ACCOUNT pPrev, pCurr;
	pPrev = pCurr = *ppUsr_Account_List;
	printf("          删除用户信息          \n");
	if (strcmp(pPrev->usr_name, search_name) == 0)
	{
		*ppUsr_Account_List = pCurr->pNext_Usr_Account;
		if (pCurr != NULL)
		{
			free(pCurr);
			pCurr = NULL;
		}
		printf("     删除成功，返回下一个用户信息     \n");
		return *ppUsr_Account_List;
	}
	else
	{
		while (pCurr)
		{
			if (strcmp(pPrev->usr_name, search_name) == 0)
			{
				pPrev->pNext_Usr_Account = pCurr->pNext_Usr_Account;
				if (pCurr != NULL)
				{
					free(pCurr);
					pCurr = NULL;
				}
				printf("删除一个用户信息成功，返回下一个用户信息\n");
				return  pPrev->pNext_Usr_Account;
			}
			pPrev = pCurr;
			pCurr = pCurr->pNext_Usr_Account;
		}
		if (NULL == pCurr)
		{
			printf("没有找到要删除的信息，请重新输入！\n");
			return  NULL;
		}
	}
	printf("没有找到要删除的信息，请重新输入！\n");
	return  NULL;
}

//根据学号查询信息
int search_usr_infor_by_id(pUSR_INFOR pUsr_Infor_List, SEARCH_ID search_id)
{
	if (pUsr_Infor_List == NULL && search_id > 10000)
	{
		printf("学生信息为空，或学号错误，请重新输入！\n");
		return -1;
	}
	int number;
	while (pUsr_Infor_List)
	{
		if (pUsr_Infor_List->usr_id == search_id)
		{
			printf("%4d  %6s %2d %-6.2f \n", pUsr_Infor_List->usr_id, pUsr_Infor_List->usr_name, pUsr_Infor_List->usr_course_id, pUsr_Infor_List->usr_course_score);
			printf("显示完成！！按3返回:");
			break;
		}
		pUsr_Infor_List = pUsr_Infor_List->pNext_Usr_Infor;
	}
	if (pUsr_Infor_List == NULL)
	{
		printf("没有找到按3返回！\n");
	}
	scanf("%d", &number);
	while (rewind(stdin), number != 3)
	{
		printf("输入错误!请查询输入:\n");
		scanf("%d", &number);
		fflush(stdin);
	}
	return number;
}
//根据名字查询学生信息
int search_usr_infor_by_name(pUSR_INFOR pUsr_Infor_List, char* search_name)
{
	if (pUsr_Infor_List == NULL || search_name==NULL)
	{
		printf("学生信息为空，或名字为空！\n");
		return -1;
	}
	int number;
	while (pUsr_Infor_List)
	{
		if (strcmp(pUsr_Infor_List->usr_name, search_name) == 0)
		{
			printf("%4d  %6s %2d %-6.2f \n", pUsr_Infor_List->usr_id, pUsr_Infor_List->usr_name, pUsr_Infor_List->usr_course_id, pUsr_Infor_List->usr_course_score);
			printf("显示完成！！按3返回:");
			break;
		}
		pUsr_Infor_List = pUsr_Infor_List->pNext_Usr_Infor;
	}
	if (pUsr_Infor_List == NULL)
	{
		printf("没有找到按3返回！\n");
	}
	scanf("%d", &number);
	while (rewind(stdin), number != 3)
	{
		printf("输入错误!请查询输入:");
		scanf("%d", &number);
	}
	return number;
}

//登录模块
USR_ROLE role_confirm(pUSR_ACCOUNT pUsr_Account)
{
	if (NULL == pUsr_Account)
	{
		printf("用户列表为空，请重新输入：\n");
		return -1;
	}
	char userName[USR_NAME_LEN];
	char passWord[USR_PWD_LEN];
usname:
	printf("请输入用户名：");	
	scanf("%s", &userName);
	if(strlen(userName) > 20)
	{
		printf("超出范围");
		return -1;
	}
	fflush(stdout);
	while (pUsr_Account)
	{
		if (strcmp(pUsr_Account->usr_name, userName) == 0)
		{
		uspwd:
			printf("请输入密码：");			
			scanf("%s", &passWord);
			if (strlen(userName) > 20)
			{
				printf("超出范围");
				return -1;
			}
			fflush(stdout);
			if (strcmp(pUsr_Account->usr_pwd, passWord) == 0)
			{
				return  pUsr_Account->usr_role == 1 ? 1 : 2;
				
			}
			else
			{
				printf("密码输入错误！\n");
				goto  uspwd;
			}
		}
		pUsr_Account = pUsr_Account->pNext_Usr_Account;
		fflush(stdout);
	}
	printf("输入的用户有错，请重新输入\n");
	goto usname;
	return -1;
}
