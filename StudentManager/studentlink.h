#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define USR_NAME_LEN 20
#define USR_PWD_LEN 20
typedef int USR_ROLE;
typedef  int USR_ACCOUNT_NUM;
typedef int SEARCH_ID;
typedef struct usr_account_tag
{
	char usr_name[USR_NAME_LEN];
	char usr_pwd[USR_PWD_LEN];
	int  usr_role;
	struct usr_account_tag *pNext_Usr_Account;
}USR_ACCOUNT, *pUSR_ACCOUNT;


typedef struct usr_infor_tag
{
	int usr_id;
	char usr_name[USR_NAME_LEN];
	int usr_course_id;
	float usr_course_score;
	struct usr_infor_tag *pNext_Usr_Infor;
}USR_INFOR, *pUSR_INFOR;


typedef  struct USR_MANAGER
{
	pUSR_ACCOUNT pusrAccount;
	pUSR_INFOR pusInfor;
}ITIN,*P_ITIN;


typedef struct Student
{
	int ID;
	char name[30];
	char six[2];
	float chinese;
	float math;
	float english;
	struct Student *pNext;
}Stu, *pStu;

//��ʼ����ʦ��Ϣ
int insertAccount(pUSR_ACCOUNT* ppHead, pUSR_ACCOUNT* ppTail, pUSR_ACCOUNT link);

//��ʼ��
void system_init(char* config_file_name, pUSR_ACCOUNT  *pUsr_Acount, pUSR_INFOR *pUsr_Infor);

//��ʼ������Ա��Ϣ
void insertStudent(pUSR_INFOR* ppHead, pUSR_INFOR *ppTail, pUSR_INFOR link);
//�ָ��ַ�����
void split(char *src, const char *separator, char **dest);

//��ʾ�û���Ϣ
int showAvvount(pUSR_ACCOUNT link);
int showAccountOne(pUSR_ACCOUNT link);

//�ַ�����תΪ�ṹ��
void charToAcc(char **str, pUSR_ACCOUNT s1);


//��ʾ�˵�  ����Ա
int menuAcc();
int menuStu();

//��ʾѧ���ļ�
int showStudent(pUSR_INFOR link);
//��ʾһ��ѧ����Ϣ
int showStudentOne(pUSR_INFOR link);

//����ѧ����Ϣ
pUSR_INFOR add_usr_infor(pUSR_INFOR *ppUsr_Infor_List);

//д���ļ�,����ѧ����Ϣ
void  saveStuFILE(pUSR_INFOR ppHead);
void  saveAccFILE(pUSR_ACCOUNT link);
//�޸�ѧ����Ϣ
pUSR_INFOR update_usr_infor(pUSR_INFOR pUsr_Infor_List, int search_id);
//ɾ��ѧ����Ϣ
pUSR_INFOR delete_usr_infor(pUSR_INFOR *ppUsr_Infor_List,int search_id);


//��¼ģ��
USR_ROLE role_confirm(pUSR_ACCOUNT pUsr_Account);
//�����û���Ϣ
pUSR_ACCOUNT add_usr_account(pUSR_ACCOUNT* ppUsr_Account_List);
//�޸��û���Ϣ
pUSR_ACCOUNT update_usr_account(pUSR_ACCOUNT pUsr_Account_List, char* search_name);

pUSR_ACCOUNT delete_usr_account(pUSR_ACCOUNT *ppUsr_Account_List, char* search_name);


//����ѧ�Ų�ѯһ��ѧ������Ϣ
int search_usr_infor_by_id(pUSR_INFOR pUsr_Infor_List, SEARCH_ID search_id);

int search_usr_infor_by_name(pUSR_INFOR pUsr_Infor_List, char* search_name);

int show_system_menu(USR_ROLE role);

int show_search_menu(USR_ROLE role);
