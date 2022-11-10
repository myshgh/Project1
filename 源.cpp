#include<sdkddkver.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <regex>
#include <iostream>
#include <string>
using namespace std;



struct student
{
	char name[20];
	char num[20];
	int age;
	char sex[5];
	char telephone[20];
	int math;
	int Linear;
	int C;
	int total;
	double grade;

};


char nam[20], number[20], s[5], tele[20];
int ag;

struct users
{
	char ac[30];
	char pw[30];
};
struct users use[50];
struct Node
{
	struct student data;
	struct Node* next;
};
struct Node* list;

struct Node* createList();
struct Node* createNode(struct student data);
struct Node* sortStudentListByTotal(struct Node* head);
void Hello();
void registeruser();
void registeruser1();
void login();
void login1();
void help();
void insertNodeByHead(struct Node* headNode);
void deleteNode(struct Node* headNode);
void change(struct Node* headNode);
struct Node* searchInfoByData(struct Node* headNode);
void printList1(struct Node* headNode);
void printList(struct Node* headNode);
void readInfoToFile(struct Node* headNode, char* fileName);
void writeInfoToFile(struct Node* headNode, char* fileName);
void menu();
void menu1();
void interaction();
void interaction1();

//������Ϣ��
struct Node* createList()
{
	//�ṹ�������ʾ��ͷ
	//ָ���ɱ���  �ö�̬�ڴ�����
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	headNode->next = NULL;
	return headNode;
};

//�������
struct Node* createNode(struct student data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

//��¼���� 
void Hello()
{
	int se;
	printf("********************************************\n");
	printf("**********ѧ����Ϣ����ϵͳ��¼����**********\n");
	printf("********************************************\n\n");
	printf("\t\t1.-��ʦ��¼�˺�-\n");
	printf("\t\t2.-ѧ����¼�˺�-\n");
	printf("\t\t3.-��ʦע���˺�-\n");
	printf("\t\t4.-ѧ��ע���˺�-\n");
	printf("\t\t5.-�˳�����-\n\n");
	printf("******************��ӭʹ��******************\n");
	printf("��ѡ��");
	scanf("%d", &se);
	switch (se)
	{
	case 1:
		login();
		break;
	case 2:
		login1();
		break;
	case 3:
		registeruser();
		break;
	case 4:
		registeruser1();
		break;
	case 5:
		printf("\n\t\t���ɹ��˳���\n");
		exit(0);
		system("pause");
		break;
	default:
		printf("\nû�����ѡ�������ѡ��\n");
		break;
	}
}

// ע���˺Ź��� 
void registeruser()
{
	char ac[30];
	char pw[6], pd[6];
	int	i, a = 0;

	printf("\t\t��ע���ʺš�\n");
	FILE* fp = fopen("�˺���Ϣ����.txt", "ab");
	printf("�������û��˺ź�����(�˺š��������Ϊ����,������ĸ,Ӣ����ĸ,����,�������6λ)\n\n\n");
	printf("\t���������˺ţ�");

	scanf("%s", &ac);
	int flag = 0;
	fp = fopen("�˺���Ϣ����.txt", "r");//��ȡ�ļ�����
	while (!feof(fp))
	{
		fscanf(fp, "%s", &use[a].ac);
		if (strcmp(ac, use[a].ac) == 0)
		{
			flag = 1;
			fclose(fp);
			break;
		}
		a++;
	}

	if (flag == 1)
	{
		printf("���û��Ѵ���");
	}
	else
	{
		strcpy(use[a].ac, ac);
		printf("\n\t�����������룺");
		for (i = 0; i < 6; i++)
		{
			pw[i] = _getch();
			printf("*");
			use[a].pw[i] = pw[i];
			if (pw[i] == '\r')
			{
				printf("ע��ʧ�ܣ�������ע���˺�\n");
				return;
			}
		}
		
			printf("\n\n\t�ٴ�ȷ�����룺");
			for (i = 0; i < 6; i++)
			{

				pd[i] = _getch();
				printf("*");
				if (use[a].pw[i] != pd[i])
				{
					printf("\n���벻�ԣ�������ע���˺�\n");
					return;
				}
			}
			fprintf(fp, "�˺�\t����\n");
			fprintf(fp, "%s\t%s\n", use[a].ac, use[a].pw);
			printf("\nע��ɹ�!!!\n");
			fclose(fp);
	    system("pause");
		system("cls");
	}
}
	

void registeruser1()
{
	char ac[30];
	char pw[6], pd[6];
	int	i, a = 0;

	printf("\t\t��ע���ʺš�\n");
	FILE* fp = fopen("ѧ���˺���Ϣ����.txt", "ab");
	printf("�������û��˺ź�����(�˺š��������Ϊ����,������ĸ,Ӣ����ĸ,����,�������6λ)\n\n\n");
	printf("\t���������˺ţ�");
	scanf("%s", &ac);
	int flag = 0;
	fp = fopen("ѧ���˺���Ϣ����.txt", "r");//��ȡ�ļ�����
	while (!feof(fp))
	{
		fscanf(fp, "%s", &use[a].ac);
		if (strcmp(ac, use[a].ac) == 0)
		{
			flag = 1;
			fclose(fp);
			break;
		}
		a++;
	}

	if (flag == 1)
	{
		printf("���û��Ѵ���");
	}
	else
	{
		strcpy(use[a].ac, ac);
	    printf("\n\t�����������룺");
	    for (i = 0; i < 6; i++)
		{
			pw[i] = _getch();
			printf("*");
			use[a].pw[i] = pw[i];
			if (pw[i] == '\r')
			{
				printf("ע��ʧ�ܣ�������ע���˺�\n");
				return;
			}
		}
		printf("\n\n\t�ٴ�ȷ�����룺");
		for (i = 0; i < 6; i++)
		{

			pd[i] = _getch();
			printf("*");
			if (use[a].pw[i] != pd[i])
			{
				printf("\n���벻�ԣ�������ע���˺�\n");
				return;
			}
		}
		fprintf(fp, "�˺�\t����\n");
		fprintf(fp, "%s\t%s\n", use[a].ac, use[a].pw);
		printf("\nע��ɹ�!!!\n");
		fclose(fp);
	}
	system("pause");
	system("cls");
	}
	

//��¼

void login()
{
	char ac[30];
	char ad[20], pw;
	int	i, j, a = 0;
	int	flag = 0;

	printf("--------����¼�˺š�--------\n");
	for (i = 0; i < 3; i++)
	{
		
			printf("�������ʺ�:");
			scanf("%s", ac);
			printf("����������:");
			int index = 0;
		while (index < 6)
		{
			pw = _getch();
			string pattern("^\\w+$");
			regex r(pattern);
			smatch results;
			ad[index] = pw;
			ad[index + 1] = '\0';
			string inputChar = ad;
			if (regex_match(inputChar, results, r))
			{
				printf("*");
				ad[index++] = pw;
			}
			else
			{
				if (index > 0 && pw == VK_BACK)
				{
					printf("\b\b");
					ad[index--] = '\0';
				}
			}
			
		}
		ad[6] = '\0';
		FILE* fp;
		fp = fopen("�˺���Ϣ����.txt", "r");//��ȡ�ļ�����
		while (!feof(fp))
		{
			fscanf(fp, "%s%s", &use[a].ac, &use[a].pw);
			if ((strcmp(ac, use[a].ac) == 0) && (strcmp(ad, use[a].pw) == 0))
			{
				flag = 1;
				fclose(fp);
				break;
			}
			a++;
		}

		if (flag == 1)
		{
			printf("\n��¼�ɹ�!");
			printf("�����������ѧ����Ϣ����ϵͳ!\n");
			system("pause");
			system("cls");
			while (1)
			{
				menu();
				interaction();
				system("pause");
				system("cls");
			}
		}
		else {
			printf("\n�˺Ż���������������㻹��%d�λ��ᣬ���������룺\n", 2 - i);
		}
	}
	if (i == 3)
	{
		printf("��¼ʧ��\n");
		return;
	}

}
void login1()
{
	char ac[30];
	char ad[20], pw;
	int	i, j, a = 0;
	int	flag = 0;

	printf("--------����¼�˺š�--------\n");
	for (i = 0; i < 3; i++)
	{
		printf("�������ʺ�:");
		scanf("%s", ac);
		printf("����������:");
		for (j = 0; j < 6; j++)
		{
			pw = _getch();
			printf("*");
			ad[j] = pw;
		}
		ad[6] = '\0';
		FILE* fp;
		fp = fopen("ѧ���˺���Ϣ����.txt", "r");//��ȡ�ļ�����
		while (!feof(fp))
		{
			fscanf(fp, "%s%s", &use[a].ac, &use[a].pw);
			if ((strcmp(ac, use[a].ac) == 0) && (strcmp(ad, use[a].pw) == 0))
			{
				flag = 1;
				fclose(fp);
				break;
			}
			a++;
		}

		if (flag == 1)
		{
			printf("\n��¼�ɹ�!");
			printf("�����������ѧ����Ϣ����ϵͳ!\n");
			system("pause");
			system("cls");
			while (1)
			{
				menu1();
				interaction1();
				system("pause");
				system("cls");
			}
		}
		else {
			printf("\n�˺Ż���������������㻹��%d�λ��ᣬ���������룺\n", 2 - i);
		}
	}
	if (i == 3)
	{
		printf("��¼ʧ��\n");
		return;
	}

}

//ϵͳ˵������ 
void help()
{
	printf("\n\t��ӭʹ��ѧ��ϵͳ������\n");
	printf("\n1�����ν���ϵͳ��,����ѡ��¼��ѧ����Ϣ;\n");
	printf("\n2�����ղ˵���ʾ���������ִ���ѡ����;\n");
	printf("\n3������ѧ����Ϣ��,��Ϣ�ᱻ�����ڸó������ڵ��ļ����еġ�ѧ����Ϣ�������ļ���;\n");
	printf("\n4������ѧ����Ϣʱ��ע�ⲻҪ�ظ����ѧ����ͬ����Ϣ;\n");
	printf("\n5�����ϵͳ��ס����رճ������µ�¼;\n");
	printf("\n6��ע�⣡����������һ�в����󣬼ǵ��˳�ϵͳ���������ֶιرճ�����Ϣ���޷����棡;\n");
	printf("\n\tлл���Ĺۿ����ټ�\n");
}

//¼�빦�� 
void insertNodeByHead(struct Node* headNode)
{
	struct student data;
	struct Node* pMove = headNode->next;
	printf("������ѧ��������ѧ�ţ����䣬�Ա𣬵绰�������ɼ����ߴ��ɼ���������Ƴɼ���\n");
	scanf("%s%s%d%s%s", &data.name, &data.num, &data.age, &data.sex, &data.telephone);
	string pattern("^(?: (?: \\+|00)86)?1[3-9]\\d{9}$");
	string numbers=data.telephone;
	regex r(pattern);
	smatch results;
	if (regex_match(numbers, results, r))
	{
		scanf("%d%d%d", &data.math, &data.Linear, &data.C);
		data.total = data.C + data.math + data.Linear;
		data.grade = ((data.math / 10.0 - 5) * 5 + (data.Linear / 10.0 - 5) * 5 + (data.C / 10.0 - 5) * 3) / 13.0;
	}
	else 
	{
	        printf("��������ȷ�ĵ绰��");
			return;
	}

	while (pMove != NULL)
	{
		if(strcmp(pMove->data.num, data.num) == 0)
		{
			printf("¼����Ϣѧ���ظ���������¼����Ϣ\n");
			break;
		}
		pMove = pMove->next;
	}
	struct Node* newNode = createNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
}

//ɾ������ 
void deleteNode(struct Node* headNode)
{
	printf("������ɾ����ѧ��ѧ��:\n");
	scanf("%s", &number);
	struct Node* posNode = headNode->next;
	struct Node* posFrontNode = headNode;

	if (posNode == NULL)
	{
		printf("����Ϊ�գ��޷�ɾ����\n");
		return;
	}
	//�������ַ������ַ�����strcmp
	while (strcmp(posNode->data.num, number))
	{
		posFrontNode = posNode;
		posNode = posFrontNode->next;
		if (posNode == NULL)
		{
			printf("δ�ҵ�ָ��λ�ã��޷�ɾ����\n");
			return;
		}
	}
	posFrontNode->next = posNode->next;
	free(posNode);
	printf("ѧ��Ϊ % sѧ������Ϣ�Ѿ�ɾ����\n", number);
}

//�޸Ĺ���
void change(struct Node* headNode)
{
	printf("������Ҫ�޸���Ϣ��ѧ��ѧ�ţ�\n");
	scanf("%s", &number);

	struct Node* changeheadNode = headNode;
	struct Node*changeNode= headNode->next;
	
	if (changeNode == NULL)
	{
		printf("����Ϊ�գ��޷��ı䣡\n");
	}
	else
	{
		while ( strcmp(changeNode->data.num, number))
		{
			changeheadNode = changeNode;
			changeNode = changeheadNode->next;
			if (changeNode == NULL)
			{
				printf("δ�ҵ�ָ��λ�ã��޷�ɾ����\n");
				return;
			}
		
		}	
		if (0 == strcmp(changeNode->data.num, number))
		{
			printf("�������ѧ��Ҫ�ı����Ϣѡ�1������ 2���绰����  3������\n");
			int choose;
			scanf("%d", &choose);
			switch (choose)
			{
			case 1:
				printf("��������Ҫ�޸ĵ����֣�");
				scanf("%s", nam);
				printf("�޸ĵ�����Ϊ��%s\n", nam);
				strcpy(changeNode->data.name, nam);
				printf("�޸����ֳɹ���\n");
				break;

			case 2:
				printf("��������Ҫ�޸ĵĵ绰����");
				scanf("%s", &tele);
				printf("�޸ĵĵ绰����Ϊ��%s\n", tele);
				strcpy(changeNode->data.telephone, tele);
				printf("�޸ĵ绰����ɹ���\n");
				break;

			case 3:
				printf("��������Ҫ�޸ĵ����䣺");
				scanf("%d", &ag);
				printf("�޸ĵ�����Ϊ��%d\n", ag);
				changeNode->data.age = ag;
				printf("�޸�����ɹ���\n");
				break;

			default:
				printf("��������ȷ��ѡ��\n");
				break;
			}
		}
	}
		
	
}

//���ҹ���
struct Node* searchInfoByData(struct Node* headNode)
{
	printf("������Ҫ���ҵ�ѧ��ѧ��:\n");
	scanf("%s", &number);
	struct Node* pMove = headNode->next;
	if (pMove == NULL)
	{
		printf("δ�ҵ������Ϣ!\n");
		return NULL;
	}
	while (strcmp(pMove->data.num, number))
	{
		pMove = pMove->next;
	}
	printf("����\tѧ��\t����\t�Ա�\t�绰\t\t�����ɼ�\t�ߴ��ɼ�\t����ɼ�\t�ܳɼ�\t����\n");
	printf("%s\t%s\t%d\t%s\t%s\t%d\t\t%d\t\t%d\t\t%d\t%.2lf\n", pMove->data.name, pMove->data.num, pMove->data.age, pMove->data.sex, pMove->data.telephone, pMove->data.math, pMove->data.Linear, pMove->data.C, pMove->data.total , pMove->data.grade );
	return NULL;
}

//������� 
void printList(struct Node* headNode)
{
	struct Node* pMove = headNode->next;
	printf("����\tѧ��\t����\t�Ա�\t�绰\t\t�����ɼ�\t�ߴ��ɼ�\t����ɼ�\t�ܳɼ�\t����\n");
	while (pMove)
	{
		printf("%s\t%s\t%d\t%s\t%s\t%d\t\t%d\t\t%d\t\t%d\t%.2lf\n", pMove->data.name, pMove->data.num, pMove->data.age, pMove->data.sex, pMove->data.telephone, pMove->data.math, pMove->data.Linear, pMove->data.C, pMove->data.total, pMove->data.grade); 
		pMove = pMove->next;
	}
	printf("\n");
}
void printList1(struct Node* headNode)
{
	struct Node* pMove = headNode->next;
	printf("����\t�����ɼ�\t�ߴ��ɼ�\t����ɼ�\t�ܳɼ�\t����\n");
	while (pMove)
	{
		printf("%s\t%s\t%d\t%s\t%s\t%d\t\t%d\t\t%d\t\t%d\t%.2lf\n", pMove->data.name, pMove->data.num, pMove->data.age, pMove->data.sex, pMove->data.telephone, pMove->data.math, pMove->data.Linear, pMove->data.C, pMove->data.total, pMove->data.grade);
		pMove = pMove->next;
	}
	printf("\n");
}
//�ܳɼ�����
struct Node* sortStudentListByTotal(struct Node* head)
{
	if (head != NULL)
	{
		struct Node* p1, * p2, * max;
		struct student s;

		p1 = head;
// ��ѡ������
		while ((p1 = p1->next) != NULL)
		{
			max = p1;
			p2 = p1;
			while ((p2 = p2->next) != NULL)
			{
				if ((p2->data).total > (max->data).total)
					max = p2;
			}

			if (max != p1)
			{
				s = p1->data;
				p1->data = max->data;
				max->data = s;
			}
		}
	}
	return head;
}



//�ļ��Ķ�ȡ
void readInfoToFile(struct Node* headNode,const char* fileName)
{
	//1�����ļ�
	FILE* fp;//�ļ�ָ���� 
	struct student data;
	fp = fopen(fileName, "rt");
	if (fp == NULL)
	{
		fopen(fileName, "wt+");
		memset(&data, 0, sizeof(student));
	}
	else
	{
		memset(&data, 0, sizeof(student));
		//2�����ļ� 
	    while (fscanf(fp,"%s\t%s\t%d\t%s\t%s\t%d\t%d\t%d\t%d\t%lf", &data.name,&data.num, &data.age, &data.sex, &data.telephone,&data.math,&data.Linear,&data.C,&data.total,&data.grade)!= EOF)
		{
			struct Node* newNode = createNode(data);
			newNode->next = headNode->next;
			 headNode->next=newNode ;
		}
	}

	//3���ر��ļ�
	fclose(fp);
}

//�ļ��Ĵ洢
void writeInfoToFile(struct Node* headNode, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "wt+");
	if (fp == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
	}
	struct Node* pMove = headNode->next;
	while (pMove)
	{
		fprintf(fp, "%s\t%s\t%d\t%s\t%s\t%d\t%d\t%d\t%d\t%.2lf\n", pMove->data.name, pMove->data.num, pMove->data.age, pMove->data.sex, pMove->data.telephone, pMove->data.math, pMove->data.Linear, pMove->data.C, pMove->data.total, pMove->data.grade );
		pMove = pMove->next;
	}
	//�ر��ļ� 
	fclose(fp);
}

//ϵͳ�˵� 
void menu()
{
	//���в�����ͬ�����ļ�
	printf("*********************************************\n");
	printf("------------��ѧ����Ϣ����ϵͳ��-------------\n");
	printf("*********************************************\n\n");
	printf("****************ϵͳ���ܲ˵�*****************\n");
	printf("*                                           *\n");
	printf("*\t\t������������������������\t\t    *\n");
	printf("*\t\t��0.ϵͳ˵����\t\t    *\n");
	printf("*\t\t��1.¼����Ϣ��\t\t    *\n");
	printf("*\t\t��2.�����Ϣ��\t\t    *\n");
	printf("*\t\t��3.�޸���Ϣ��\t\t    *\n");
	printf("*\t\t��4.ɾ����Ϣ��\t\t    *\n");
	printf("*\t\t��5.������Ϣ��\t\t    *\n");
	printf("*\t\t��6.�鿴������\t\t    *\n");
	printf("*\t\t��7.�˳�ϵͳ��\t\t    *\n");
	printf("*\t\t������������������������\t\t    *\n");
	printf("*                                           *\n");
	printf("******************��ӭʹ��*******************\n\n");
}
void menu1()
{
	//���в�����ͬ�����ļ�
	printf("*********************************************\n");
	printf("------------��ѧ����Ϣ����ϵͳ��-------------\n");
	printf("*********************************************\n\n");
	printf("****************ϵͳ���ܲ˵�*****************\n");
	printf("*                                           *\n");
	printf("*\t\t������������������������\t\t    *\n");
	printf("*\t\t��0.ϵͳ˵����\t\t    *\n");
	printf("*\t\t��1.�鿴��Ϣ��\t\t    *\n");
	printf("*\t\t��2.�鿴������\t\t    *\n");
	printf("*\t\t��3.�˳�ϵͳ��\t\t    *\n");
	printf("*\t\t������������������������\t\t    *\n");
	printf("*                                           *\n");
	printf("******************��ӭʹ��*******************\n\n");
}

//�û��Ľ���
void interaction()
{
	int choice;
	printf("��ѡ������ʹ�õĹ��ܣ�");
	scanf("%d", &choice);
	switch (choice)
	{
	case 0:
		printf("\n--------��ϵͳ˵����--------");
		help();
		break;
	case 1:
		printf("\n--------��¼����Ϣ��--------\n");
		insertNodeByHead(list);
		writeInfoToFile(list, "ѧ����Ϣ����.txt");
		break;
	case 2:
		printf("\n--------�������Ϣ��--------\n");
		printList(list);
		break;
	case 3:
		printf("\n--------���޸���Ϣ��--------\n");
		change(list);
		writeInfoToFile(list, "ѧ����Ϣ����.txt");
		break;
	case 4:
		printf("\n--------��ɾ����Ϣ��--------\n");
		deleteNode(list);
		writeInfoToFile(list, "ѧ����Ϣ����.txt");
		break;
	case 5:
		printf("\n--------��������Ϣ��--------\n");
		searchInfoByData(list);
		break;
	case 6:
		printf("\n--------���鿴������--------\n");
		sortStudentListByTotal(list);
		printList(list);
		break;
	case 7:
		printf("\n--------��ϵͳ���˳���-------\n");
		writeInfoToFile(list, "ѧ����Ϣ����.txt");
		system("pause");
		exit(0);
		break;
	default:
		printf("ѡ���������������\n");
		break;
	}
}
void interaction1()
{
	int choice;
	printf("��ѡ������ʹ�õĹ��ܣ�");
	scanf("%d", &choice);
	switch (choice)
	{
	case 0:
		printf("\n--------��ϵͳ˵����--------");
		help();
		break;
	case 1:
		printf("\n--------���鿴��Ϣ��--------\n");
		searchInfoByData(list);
		break;
	case 2:
		printf("\n--------���鿴������--------\n");
		sortStudentListByTotal(list);
		printList1(list);
		break;
	case 3:
		printf("\n--------��ϵͳ���˳���-------\n");
		system("pause");
		writeInfoToFile(list, "ѧ����Ϣ����.txt");
		exit(0);
		break;
	default:
		printf("ѡ���������������\n");
		break;
	}
}

int main() {
	system("color 81");
	list = createList();
	readInfoToFile(list, "ѧ����Ϣ����.txt");

	while (1)
	{
		Hello();
		system("pause");
		system("cls"); 
		
	}
	return 0;
}