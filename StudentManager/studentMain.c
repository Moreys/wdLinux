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
	fpas = fopen(argv[1], "r+");//���ļ�	
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
			case 2://���ѧ����Ϣ����Ҫ������		
				system("cls");
				showStudentOne(add_usr_infor(&psHead));
				saveStuFILE(psHead);
				system("cls");
				break;
			case 3://�޸�
				system("cls");
				printf("��������Ҫ�޸ĵ�ѧ��!\n");
				int num;
				scanf("%d", &num);
				showStudentOne(update_usr_infor(psHead, num));
				saveStuFILE(psHead);
				num = 0;
				system("cls");
				break;
			case 4://ɾ��ѧ����Ϣ
				system("cls");
				printf("��������Ҫɾ��ѧ����ѧ��!\n");
				int num1;
				scanf("%d", &num1);
				if(num1>1000000)
				{
					printf("����ѧ������!\n");
					break;
				}
				showStudentOne(delete_usr_infor(&psHead, num1));
				saveStuFILE(psHead);
				system("cls");
				break;
			case 5://�����û�
				system("cls");
				showAccountOne(add_usr_account(&paHead));
				saveAccFILE(paHead);
				system("cls");
				break;
			case 6://�޸��û���Ϣ		
				system("cls");
				printf("��������Ҫ�޸ĵ��û���:");
				char usName[20];
				scanf("%s", &usName);
				if (strlen(usName) > 20)
				{
					printf("��������ִ���20���ַ�����������\n");
					break;
				}
				showAccountOne(update_usr_account(paHead, usName));
				saveAccFILE(paHead);
				system("cls");
				break;
			case 7:  //ɾ��
				system("cls");
				printf("��������Ҫɾ�����û�:");
				char usName1[20];
				scanf("%s", &usName1);
				if (strlen(usName1) > 20)
				{
					printf("��������ִ���20���ַ�����������\n");
					break;
				}
				showAccountOne(delete_usr_account(&paHead, usName1));
				saveAccFILE(paHead);
				system("cls");
				break;
			case 8:	//��ѯ	
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
				printf("�������ѯ��ѧ����ѧ��!\n");
				int num;
				scanf("%d", &num);
				if(num > 100000)
				{
					printf("ѧ������������������룡");
					break;
				}
				search_usr_infor_by_id(psHead, num);
				num = 0;
				break;
			case 2:
				system("cls");
				printf("�������ѯѧ��������!\n");
				char userName[20];
				scanf("%s", &userName);
				if(strlen(userName) > 20)
				{
					printf("��������ֹ��������������룡\n");
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
	printf("�ɹ��˳�ϵͳ����\n");
	system("pause");
	return EXIT_SUCCESS;
}