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

//初始化老师信息
int insertAccount(pUSR_ACCOUNT* ppHead, pUSR_ACCOUNT* ppTail, pUSR_ACCOUNT link);

//初始化
void system_init(char* config_file_name, pUSR_ACCOUNT  *pUsr_Acount, pUSR_INFOR *pUsr_Infor);

//初始化管理员信息
void insertStudent(pUSR_INFOR* ppHead, pUSR_INFOR *ppTail, pUSR_INFOR link);
//分割字符数组
void split(char *src, const char *separator, char **dest);

//显示用户信息
int showAvvount(pUSR_ACCOUNT link);
int showAccountOne(pUSR_ACCOUNT link);

//字符数组转为结构体
void charToAcc(char **str, pUSR_ACCOUNT s1);


//显示菜单  管理员
int menuAcc();
int menuStu();

//显示学生文件
int showStudent(pUSR_INFOR link);
//显示一个学生信息
int showStudentOne(pUSR_INFOR link);

//增加学生信息
pUSR_INFOR add_usr_infor(pUSR_INFOR *ppUsr_Infor_List);

//写入文件,保存学生信息
void  saveStuFILE(pUSR_INFOR ppHead);
void  saveAccFILE(pUSR_ACCOUNT link);
//修改学生信息
pUSR_INFOR update_usr_infor(pUSR_INFOR pUsr_Infor_List, int search_id);
//删除学生信息
pUSR_INFOR delete_usr_infor(pUSR_INFOR *ppUsr_Infor_List,int search_id);


//登录模块
USR_ROLE role_confirm(pUSR_ACCOUNT pUsr_Account);
//增加用户信息
pUSR_ACCOUNT add_usr_account(pUSR_ACCOUNT* ppUsr_Account_List);
//修改用户信息
pUSR_ACCOUNT update_usr_account(pUSR_ACCOUNT pUsr_Account_List, char* search_name);

pUSR_ACCOUNT delete_usr_account(pUSR_ACCOUNT *ppUsr_Account_List, char* search_name);


//根据学号查询一个学生的信息
int search_usr_infor_by_id(pUSR_INFOR pUsr_Infor_List, SEARCH_ID search_id);

int search_usr_infor_by_name(pUSR_INFOR pUsr_Infor_List, char* search_name);

int show_system_menu(USR_ROLE role);

int show_search_menu(USR_ROLE role);
