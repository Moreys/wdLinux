/***********************************************************
*
* outhar:morey
************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include  "studentlink.h"
int main(int argc, char **argv)
{
	int ret;
	char buf[128] = { 0 };
	pUSR_INFOR psHead = NULL;
	pUSR_ACCOUNT paHead = NULL;
	FILE *fpas;
	fpas = fopen(argv[1], "r+");//打开文件	
	fgets(buf, 127, fpas);
	system_init(buf, &paHead, &psHead);
	ret = role_confirm(paHead);

	if (ret == 1)
	{
		
		for (;;)
		{
			system("cls");
			ret = menuAcc();
			switch (ret)
			{				
			case 1:
				system("cls");
				showStudent(psHead);
				system("cls");
				break;
			case 2://添加学生信息，主要有名字		
				system("cls");
				showStudentOne(add_usr_infor(&psHead));
				saveStuFILE(psHead);
				system("cls");
				break;
			case 3://修改
				system("cls");
				printf("请输入需要修改的学号!\n");
				int num;
				scanf("%d", &num);
				showStudentOne(update_usr_infor(psHead, num));
				saveStuFILE(psHead);
				num = 0;
				system("cls");
				break;
			case 4://删除学生信息
				system("cls");
				printf("请输入需要删除学生的学号!\n");
				int num1;
				scanf("%d", &num1);
				if(num1>1000000)
				{
					printf("输入学号有误!\n");
					break;
				}
				showStudentOne(delete_usr_infor(&psHead, num1));
				saveStuFILE(psHead);
				system("cls");
				break;
			case 5://增加用户
				system("cls");
				showAccountOne(add_usr_account(&paHead));
				saveAccFILE(paHead);
				system("cls");
				break;
			case 6://修改用户信息		
				system("cls");
				printf("请输入需要修改的用户名:");
				char usName[20];
				scanf("%s", &usName);
				if (strlen(usName) > 20)
				{
					printf("输入的名字大于20个字符请重新输入\n");
					break;
				}
				showAccountOne(update_usr_account(paHead, usName));
				saveAccFILE(paHead);
				system("cls");
				break;
			case 7:  //删除
				system("cls");
				printf("请输入需要删除的用户:");
				char usName1[20];
				scanf("%s", &usName1);
				if (strlen(usName1) > 20)
				{
					printf("输入的名字大于20个字符请重新输入\n");
					break;
				}
				showAccountOne(delete_usr_account(&paHead, usName1));
				saveAccFILE(paHead);
				system("cls");
				break;
			case 8:	//查询	
				system("cls");
				showAvvount(paHead);
				system("cls");
				break;
			case 9:
				system("cls");
				goto over;
			default:
				goto over;
			}
		}
	}
	else if (ret ==2)
	{
		//system("cls");
		for (;;)
		{
			system("cls");
			ret = menuStu();			
			switch (ret)
			{
			case 1:
				system("cls");
				printf("请输入查询的学生的学号!\n");
				int num;
				scanf("%d", &num);
				if(num > 100000)
				{
					printf("学号输入错误，请重新输入！");
					break;
				}
				search_usr_infor_by_id(psHead, num);
				num = 0;
				break;
			case 2:
				system("cls");
				printf("请输入查询学生的名字!\n");
				char userName[20];
				scanf("%s", &userName);
				if(strlen(userName) > 20)
				{
					printf("输入的名字过长，请重新输入！\n");
					break;
				}
				search_usr_infor_by_name(psHead, userName);
				system("cls");
				break;
			case 3:
				system("cls");
				goto over;
			default:
				goto over;
			}
		}
	}

over:
	printf("成功退出系统！！\n");
	system("pause");
	return EXIT_SUCCESS;
}