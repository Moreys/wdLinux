#include "studentlink.h"

void system_init( char* config_file_name, pUSR_ACCOUNT  *pUsr_Acount, pUSR_INFOR *pUsr_Infor)
{
	//��ȡ�����ļ�
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
	//ת��
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


/*�������Ա��Ϣ
 * �ɹ�����1��ʧ�ܷ���0
 * ����1������Ľṹ�壬����2��������Դ
 */
int insertAccount(pUSR_ACCOUNT* ppHead, pUSR_ACCOUNT* ppTail, pUSR_ACCOUNT link)
{
	pUSR_ACCOUNT newNode = (pUSR_ACCOUNT)malloc(sizeof(USR_ACCOUNT));//�ṹ���������ַ����������·����ʱ���ܸ���ʼֵ����Ȼ�����ַ���ֵ��ʱ��ط��ʳ�����
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
	printf("����ʧ�ܣ�");
	return 0;
}


/*����ѧ����Ϣ
  * �ɹ�����1��ʧ�ܷ���0
  * ����1������Ľṹ�壬����2��������Դ
  */
void insertStudent(pUSR_INFOR* ppHead, pUSR_INFOR *ppTail, pUSR_INFOR link)
{
	pUSR_INFOR newNode = (pUSR_INFOR)calloc(1, sizeof(USR_INFOR));//�ṹ���������ַ����������·����ʱ���ܸ���ʼֵ����Ȼ�����ַ���ֵ��ʱ��ط��ʳ�����
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


//�˵���ӡ
int menuAcc()
{
	int num;
	printf("***************************************\n");
	printf("***************************************\n");
	printf("          ѧ������ϵͳ������ʦ��           \n");
	printf("****************************************\n");
	printf("*            1����ѯѧ����Ϣ           *\n");
	printf("*            2������ѧ����Ϣ           *\n");
	printf("*            3������ѧ����Ϣ           *\n");
	printf("*            4��ɾ��ѧ����Ϣ           *\n");
	printf("*            5�������û���Ϣ           *\n");
	printf("*            6�������û���Ϣ           *\n");
	printf("*            7��ɾ���û���Ϣ           *\n");
	printf("*            8����ѯ�û���Ϣ           *\n");
	printf("*            9���˳�ϵͳ               *\n");
	printf("****************************************\n");
	printf("************��������Ҫ���ҵ�����********\n");
	scanf("%d", &num);
	while (rewind(stdin), num > 10 || num < 0)
	{
		printf("����������ѯ����:\n");
		scanf("%d", &num);
	}
	return num;
}

int menuStu()
{
	int num;
	printf("*************************************************\n");
	printf("*************************************************\n");
	printf("             ѧ������ϵͳ����ѧ����               \n");
	printf("*************************************************\n");
	printf("*            1������ѧ�Ų�ѯѧ����Ϣ            *\n");
	printf("*            2������������ѯѧ����Ϣ            *\n");
	printf("*            3���˳�ϵͳ                        *\n");
	printf("*************************************************\n");
	printf("****************��������Ҫ���ҵ�����*************\n");
	scanf("%d", &num);
	while (rewind(stdin), num > 4 || num < 0)
	{
		printf("����������ѯ����:\n");
		scanf("%d", &num);
	}
	return num;
}

//��ʾѧ���ļ�
int showStudent(pUSR_INFOR link)
{
	int num;
	if (NULL == link)
	{
		printf("link is empty");
		return -1;
	}
	printf("ѧ����Ϣ��ʾ����\n");
	while (link)
	{
		printf("%4d  %6s %2d %-6.2f \n", link->usr_id, link->usr_name, link->usr_course_id, link->usr_course_score);
		link = link->pNext_Usr_Infor;
	}

	printf("��ʾ��ɣ�����3����:");
	scanf("%d", &num);
	while (rewind(stdin), num != 3)
	{
		printf("�������!���ѯ����:");
		scanf("%d", &num);
	}
	return num;
}
//��ʾһ��ѧ��
int showStudentOne(pUSR_INFOR link)
{
	int num;
	if (NULL == link)
	{
		printf("link is empty");
		return -1;
	}
	printf("ѧ����Ϣ��ʾ����\n");
	while (link)
	{
		printf("%4d  %6s %2d %-6.2f \n", link->usr_id, link->usr_name, link->usr_course_id, link->usr_course_score);
		break;
	}
	printf("��ʾ��ɣ�����3����:");
	scanf("%d", &num);
	while (rewind(stdin), num != 3)
	{
		printf("�������!���ѯ����:");
		scanf("%d", &num);
	}
	return num;
}

//��ʾ�û���Ϣ
int showAvvount(pUSR_ACCOUNT link)
{
	int num;
	if (NULL == link)
	{
		printf("link is empty");
		return -1;
	}
	printf("�û���ʾ����\n");
	while (link)
	{
		printf("%4s  %4s %2d\n", link->usr_name, link->usr_pwd, link->usr_role);
		link = link->pNext_Usr_Account;
		/*fprintf(fp, "%4d %2s %6s %-6.2f %-6.2f %-6.2f \n", link->ID, link->six, link->name, link->chinese, link->math, link->english);
		link = link->pNext;*/
	}
	printf("��ʾ��ɣ�����3����:");
	scanf("%d", &num);
	while (rewind(stdin), num != 3)
	{
		printf("�������!���ѯ����:");
		scanf("%d", &num);
	}
	return num;
}
int showAccountOne(pUSR_ACCOUNT link)
{
	if (link == NULL)
	{
		printf("�û���ϢΪ�գ���");
		return  -1;
	}
	int number;
	while (link)
	{
		printf("%4s  %4s %2d\n", link->usr_name, link->usr_pwd, link->usr_role);
		break;
	}
	printf("��ʾ��ɣ�����3����:");
	scanf("%d", &number);
	while (rewind(stdin), number != 3)
	{
		printf("�������!���ѯ����:");
		scanf("%d", &number);
	}
	return number;
}


//�ָ��ַ����飬���뵽��ά�ַ�������
void split(char *src, const char *separator, char **dest) {
	/*
		src Դ�ַ������׵�ַ(buf�ĵ�ַ)
		separator ָ���ķָ��ַ�
		dest �������ַ���������
		num �ָ�����ַ����ĸ���
	*/
	char *pNext;
	if (src == NULL || strlen(src) == 0) //�������ĵ�ַΪ�ջ򳤶�Ϊ0��ֱ����ֹ 
		return;
	if (separator == NULL || strlen(separator) == 0) //��δָ���ָ���ַ�����ֱ����ֹ 
		return;
	/*����ԭ�ͣ�char *strtok( char *str1, const char *str2 );
		���ܣ����ر�ǣ������ַ���str1�н��ӡ���ǡ��Ĳ��ֵ�ָ�룬�ַ���str2����Ϊ��ǵķָ���������ָ���û���ҵ�����������NULL Ϊ���ַ�����ǣ���һ�ε���str1ָ����Ϊ��ǵķָ�����֮�����еĵ���str1��ӦΪNULL
	 *
	 */
	pNext = (char *)strtok(src, separator); //����ʹ��(char *)����ǿ������ת��(��Ȼ��д�еı������в������ָ�����)
	while (pNext != NULL) {
		*dest++ = pNext;
		pNext = (char *)strtok(NULL, separator);  //����ʹ��(char *)����ǿ������ת��
	}
}
//�ַ�����תΪ�ṹ��
void charToAcc(char **str, pUSR_ACCOUNT s1)
{
	strcpy(s1->usr_name, str[0]);
	strcpy(s1->usr_pwd, str[1]);
	s1->usr_role = atoi(str[2]);
}


//����ѧ����Ϣ
pUSR_INFOR add_usr_infor(pUSR_INFOR *ppUsr_Infor_List)
{
	pUSR_INFOR stu1 = *ppUsr_Infor_List;
	pUSR_INFOR pPrve = *ppUsr_Infor_List;  //��¼ǰһ���ڵ�
	pUSR_INFOR pCurrent = stu1->pNext_Usr_Infor;//��¼��һ���ڵ�	
	int number;
	char name[USR_NAME_LEN];
	int usr_course_id;
	float usr_score;
	printf("          ����ѧ����Ϣ          \n");
	printf("ѧ�Ų�����6λ���γ̲������Ų�����20������������200\n");
	printf("����������ѧ�ţ��������γ̺ţ��γ̷���\n");
	scanf("%d%s%d%f", &number, &name, &usr_course_id, &usr_score);
	if(number>1000000||strlen(name)>20||usr_course_id>20||usr_score>200)
	{
		printf("���벻���Ϲ淶�����������룡");
		return NULL;
	}
	while (stu1)//
	{
		if (stu1->usr_id == number)
		{
			printf("ѧ���ظ������������!\n");
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
	//�������д���ļ�	
	return newNode;
}

//����ѧ����Ϣ
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
	printf("ѧ����Ϣ������ϣ�\n");
	system("pause");
}

//�����û���Ϣ
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
	printf("�û���Ϣ������ϣ�\n");
	system("pause");
}

//���������ѧ�Ž����޸�
pUSR_INFOR update_usr_infor(pUSR_INFOR pUsr_Infor_List, int search_id)
{
	if (pUsr_Infor_List == NULL)
	{
		printf("ѧ����ϢΪ�գ�");
		return NULL;
	}

	while (pUsr_Infor_List)
	{
		if (pUsr_Infor_List->usr_id == search_id)
		{
			char name[USR_NAME_LEN];
			int usr_course_id;
			float usr_score;
			printf("ѧ�Ų�����6λ���γ̲������Ų�����20������������200\n");
			printf("������������Ҫ�޸ĵ��������γ̺ţ��γ̷���\n");			
			scanf("%s%d%f", &name, &usr_course_id, &usr_score);
			if (strlen(name) > 20 || usr_course_id > 20 || usr_score > 200)
			{
				printf("���벻���Ϲ淶�����������룡");
				return NULL;
			}
			strcpy(pUsr_Infor_List->usr_name, name);
			pUsr_Infor_List->usr_course_id = usr_course_id;
			pUsr_Infor_List->usr_course_score = usr_score;
			return pUsr_Infor_List;
		}
		pUsr_Infor_List = pUsr_Infor_List->pNext_Usr_Infor;
	}
	printf("û���ҵ�Ҫ�޸ĵ�ѧ�ţ����������룺");
	return  NULL;
}

//����ѧ��ɾ����Ϣ
/*���ҵ���Ϣ  ��Ҫ����ָ��������洢Ҫɾ������Ϣ
 */
pUSR_INFOR delete_usr_infor(pUSR_INFOR* ppUsr_Infor_List, int search_id)
{
	if (*ppUsr_Infor_List == NULL)
	{
		printf("ѧ����ϢΪ�գ�");
		return NULL;
	}
	pUSR_INFOR pPre, pCurr;
	pPre = pCurr = *ppUsr_Infor_List;
	//USR_INFOR Stu;
	printf("          ɾ��ѧ����Ϣ          \n");
	if (pCurr->usr_id == search_id)
	{
		*ppUsr_Infor_List = pCurr->pNext_Usr_Infor;
		if (pCurr != NULL)
		{
			free(pCurr);
			pCurr = NULL;
		}
		//return pPre;
		printf("     ɾ���ɹ���������һ��ѧ����Ϣ     \n");
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
				printf("     ɾ���ɹ���������һ��ѧ����Ϣ     \n");
				return pPre->pNext_Usr_Infor;
			}
			pPre = pCurr;
			pCurr = pCurr->pNext_Usr_Infor;
		}

		if (pCurr == NULL)
		{
			printf("û���ҵ�Ҫɾ����ѧ�������������룺");
			return  NULL;
		}
	}
	printf("û���ҵ�Ҫɾ����ѧ�������������룺");
	return  NULL;
}



//�����û���Ϣ
pUSR_ACCOUNT add_usr_account(pUSR_ACCOUNT* ppUsr_Account_List)
{
	pUSR_ACCOUNT acc = *ppUsr_Account_List;
	pUSR_ACCOUNT pPre = *ppUsr_Account_List;
	pUSR_ACCOUNT pCurr = pPre->pNext_Usr_Account;
	int number;
	char name[USR_NAME_LEN];
	char pwd[USR_PWD_LEN];
	printf("          �����û���Ϣ          \n");
	printf("��ܰ��ʾ������Ա���Ͳ��ܳ���2���û��������벻�ܳ���20���ַ�\n");
	printf("�����������û����ͣ�1Ϊ����Ա��2Ϊ��ͨ�û������û���������\n");
	scanf("%d%s%s", &number, &name, &pwd);
	if(number > 20 || strlen(name) > 20|| strlen(pwd) > 20)
	{
		printf("������Ϣ������������������룡\n");
		return NULL;
	}
	while (acc)
	{
		if (strcmp(acc->usr_name, name) == 0)
		{
			printf("�û�����ͬ�����������룡");
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

//�޸��û���Ϣ
/*
 * �ɹ������޸ĺõ���Ϣ��
 * ʧ�ܷ��ؿ�
 *
 */
pUSR_ACCOUNT update_usr_account(pUSR_ACCOUNT pUsr_Account_List, char* search_name)
{
	if (pUsr_Account_List == NULL || search_name == NULL)
	{
		printf("����Ϊ�ջ��û���Ϊ�գ���������������\n");
		return  NULL;
	}
	while (pUsr_Account_List)
	{
		if (strcmp(pUsr_Account_List->usr_name, search_name) == 0)
		{
			char name[USR_NAME_LEN];
			char pwd[USR_PWD_LEN];
			int idNumber;
			printf("         �û���Ϣ�޸�\n");
			printf("��ܰ��ʾ������Ա���Ͳ��ܳ���2���û��������벻�ܳ���20���ַ�\n");
			printf("����������:1�û���  2����  3�û����ͣ�1Ϊ����Ա��2Ϊ��ͨ�û�����\n");
			scanf("%s%s%d", &name, &pwd, &idNumber);
			if (idNumber > 20 || strlen(name) > 20 || strlen(pwd) > 20)
			{
				printf("������Ϣ������������������룡\n");
				return NULL;
			}
			strcpy(pUsr_Account_List->usr_name, name);
			strcpy(pUsr_Account_List->usr_pwd, pwd);
			pUsr_Account_List->usr_role = idNumber;
			return pUsr_Account_List;
		}
		pUsr_Account_List = pUsr_Account_List->pNext_Usr_Account;
	}
	printf("     û���ҵ���Ҫ�޸ĵ��û�����\n");
	printf("     ����������\n");
	return  NULL;
}

//ɾ���û���Ϣ
pUSR_ACCOUNT delete_usr_account(pUSR_ACCOUNT* ppUsr_Account_List, char* search_name)
{
	if (*ppUsr_Account_List == NULL || search_name == NULL)
	{
		printf("�û���Ϊ�ջ����û���Ϊ��,����������\n");
		return  NULL;
	}
	pUSR_ACCOUNT pPrev, pCurr;
	pPrev = pCurr = *ppUsr_Account_List;
	printf("          ɾ���û���Ϣ          \n");
	if (strcmp(pPrev->usr_name, search_name) == 0)
	{
		*ppUsr_Account_List = pCurr->pNext_Usr_Account;
		if (pCurr != NULL)
		{
			free(pCurr);
			pCurr = NULL;
		}
		printf("     ɾ���ɹ���������һ���û���Ϣ     \n");
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
				printf("ɾ��һ���û���Ϣ�ɹ���������һ���û���Ϣ\n");
				return  pPrev->pNext_Usr_Account;
			}
			pPrev = pCurr;
			pCurr = pCurr->pNext_Usr_Account;
		}
		if (NULL == pCurr)
		{
			printf("û���ҵ�Ҫɾ������Ϣ�����������룡\n");
			return  NULL;
		}
	}
	printf("û���ҵ�Ҫɾ������Ϣ�����������룡\n");
	return  NULL;
}

//����ѧ�Ų�ѯ��Ϣ
int search_usr_infor_by_id(pUSR_INFOR pUsr_Infor_List, SEARCH_ID search_id)
{
	if (pUsr_Infor_List == NULL && search_id > 10000)
	{
		printf("ѧ����ϢΪ�գ���ѧ�Ŵ������������룡\n");
		return -1;
	}
	int number;
	while (pUsr_Infor_List)
	{
		if (pUsr_Infor_List->usr_id == search_id)
		{
			printf("%4d  %6s %2d %-6.2f \n", pUsr_Infor_List->usr_id, pUsr_Infor_List->usr_name, pUsr_Infor_List->usr_course_id, pUsr_Infor_List->usr_course_score);
			printf("��ʾ��ɣ�����3����:");
			break;
		}
		pUsr_Infor_List = pUsr_Infor_List->pNext_Usr_Infor;
	}
	if (pUsr_Infor_List == NULL)
	{
		printf("û���ҵ���3���أ�\n");
	}
	scanf("%d", &number);
	while (rewind(stdin), number != 3)
	{
		printf("�������!���ѯ����:\n");
		scanf("%d", &number);
		fflush(stdin);
	}
	return number;
}
//�������ֲ�ѯѧ����Ϣ
int search_usr_infor_by_name(pUSR_INFOR pUsr_Infor_List, char* search_name)
{
	if (pUsr_Infor_List == NULL || search_name==NULL)
	{
		printf("ѧ����ϢΪ�գ�������Ϊ�գ�\n");
		return -1;
	}
	int number;
	while (pUsr_Infor_List)
	{
		if (strcmp(pUsr_Infor_List->usr_name, search_name) == 0)
		{
			printf("%4d  %6s %2d %-6.2f \n", pUsr_Infor_List->usr_id, pUsr_Infor_List->usr_name, pUsr_Infor_List->usr_course_id, pUsr_Infor_List->usr_course_score);
			printf("��ʾ��ɣ�����3����:");
			break;
		}
		pUsr_Infor_List = pUsr_Infor_List->pNext_Usr_Infor;
	}
	if (pUsr_Infor_List == NULL)
	{
		printf("û���ҵ���3���أ�\n");
	}
	scanf("%d", &number);
	while (rewind(stdin), number != 3)
	{
		printf("�������!���ѯ����:");
		scanf("%d", &number);
	}
	return number;
}

//��¼ģ��
USR_ROLE role_confirm(pUSR_ACCOUNT pUsr_Account)
{
	if (NULL == pUsr_Account)
	{
		printf("�û��б�Ϊ�գ����������룺\n");
		return -1;
	}
	char userName[USR_NAME_LEN];
	char passWord[USR_PWD_LEN];
usname:
	printf("�������û�����");	
	scanf("%s", &userName);
	if(strlen(userName) > 20)
	{
		printf("������Χ");
		return -1;
	}
	fflush(stdout);
	while (pUsr_Account)
	{
		if (strcmp(pUsr_Account->usr_name, userName) == 0)
		{
		uspwd:
			printf("���������룺");			
			scanf("%s", &passWord);
			if (strlen(userName) > 20)
			{
				printf("������Χ");
				return -1;
			}
			fflush(stdout);
			if (strcmp(pUsr_Account->usr_pwd, passWord) == 0)
			{
				return  pUsr_Account->usr_role == 1 ? 1 : 2;
				
			}
			else
			{
				printf("�����������\n");
				goto  uspwd;
			}
		}
		pUsr_Account = pUsr_Account->pNext_Usr_Account;
		fflush(stdout);
	}
	printf("������û��д�����������\n");
	goto usname;
	return -1;
}
