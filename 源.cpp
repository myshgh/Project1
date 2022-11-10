#include<sdkddkver.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>


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

//创建信息表
struct Node* createList()
{
	//结构体变量表示表头
	//指针变成变量  用动态内存申请
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	headNode->next = NULL;
	return headNode;
};

//创建结点
struct Node* createNode(struct student data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

//登录界面 
void Hello()
{
	int se;
	printf("********************************************\n");
	printf("**********学生信息管理系统登录界面**********\n");
	printf("********************************************\n\n");
	printf("\t\t1.-教师登录账号-\n");
	printf("\t\t2.-学生登录账号-\n");
	printf("\t\t3.-教师注册账号-\n");
	printf("\t\t4.-学生注册账号-\n");
	printf("\t\t5.-退出界面-\n\n");
	printf("******************欢迎使用******************\n");
	printf("请选择：");
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
		printf("\n\t\t【成功退出】\n");
		exit(0);
		system("pause");
		break;
	default:
		printf("\n没有这个选项，请重新选择！\n");
		break;
	}
}

// 注册账号功能 
void registeruser()
{
	char ac[30];
	char pw[6], pd[6];
	int	i, a = 0;

	printf("\t\t【注册帐号】\n");
	FILE* fp = fopen("账号信息档案.txt", "ab");
	printf("请输入用户账号和密码(账号、密码可以为数字,中文字母,英文字母,符号,密码必须6位)\n\n\n");
	printf("\t请你输入账号：");

	scanf("%s", &ac);
	int flag = 0;
	fp = fopen("账号信息档案.txt", "r");//读取文件操作
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
		printf("该用户已存在");
	}
	else
	{
		strcpy(use[a].ac, ac);
		printf("\n\t请你输入密码：");
		for (i = 0; i < 6; i++)
		{
			pw[i] = _getch();
			printf("*");
			use[a].pw[i] = pw[i];
			if (pw[i] == '\r')
			{
				printf("注册失败，请重新注册账号\n");
				return;
			}
		}
		
			printf("\n\n\t再次确认密码：");
			for (i = 0; i < 6; i++)
			{

				pd[i] = _getch();
				printf("*");
				if (use[a].pw[i] != pd[i])
				{
					printf("\n密码不对，请重新注册账号\n");
					return;
				}
			}
			fprintf(fp, "账号\t密码\n");
			fprintf(fp, "%s\t%s\n", use[a].ac, use[a].pw);
			printf("\n注册成功!!!\n");
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

	printf("\t\t【注册帐号】\n");
	FILE* fp = fopen("学生账号信息档案.txt", "ab");
	printf("请输入用户账号和密码(账号、密码可以为数字,中文字母,英文字母,符号,密码必须6位)\n\n\n");
	printf("\t请你输入账号：");
	scanf("%s", &ac);
	int flag = 0;
	fp = fopen("学生账号信息档案.txt", "r");//读取文件操作
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
		printf("该用户已存在");
	}
	else
	{
		strcpy(use[a].ac, ac);
	    printf("\n\t请你输入密码：");
	    for (i = 0; i < 6; i++)
		{
			pw[i] = _getch();
			printf("*");
			use[a].pw[i] = pw[i];
			if (pw[i] == '\r')
			{
				printf("注册失败，请重新注册账号\n");
				return;
			}
		}
		printf("\n\n\t再次确认密码：");
		for (i = 0; i < 6; i++)
		{

			pd[i] = _getch();
			printf("*");
			if (use[a].pw[i] != pd[i])
			{
				printf("\n密码不对，请重新注册账号\n");
				return;
			}
		}
		fprintf(fp, "账号\t密码\n");
		fprintf(fp, "%s\t%s\n", use[a].ac, use[a].pw);
		printf("\n注册成功!!!\n");
		fclose(fp);
	}
	system("pause");
	system("cls");
	}
	

//登录

void login()
{
	char ac[30];
	char ad[20], pw;
	int	i, j, a = 0;
	int	flag = 0;

	printf("--------【登录账号】--------\n");
	for (i = 0; i < 3; i++)
	{
		printf("请输入帐号:");
		scanf("%s", ac);
		printf("请输入密码:");
		for (j = 0; j < 6; j++)
		{
			pw = _getch();
			printf("*");
			ad[j] = pw;
		}
		ad[6] = '\0';
		FILE* fp;
		fp = fopen("账号信息档案.txt", "r");//读取文件操作
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
			printf("\n登录成功!");
			printf("按任意键进入学生信息管理系统!\n");
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
			printf("\n账号或者密码输入错误，你还有%d次机会，请重新输入：\n", 2 - i);
		}
	}
	if (i == 3)
	{
		printf("登录失败\n");
		return;
	}

}
void login1()
{
	char ac[30];
	char ad[20], pw;
	int	i, j, a = 0;
	int	flag = 0;

	printf("--------【登录账号】--------\n");
	for (i = 0; i < 3; i++)
	{
		printf("请输入帐号:");
		scanf("%s", ac);
		printf("请输入密码:");
		for (j = 0; j < 6; j++)
		{
			pw = _getch();
			printf("*");
			ad[j] = pw;
		}
		ad[6] = '\0';
		FILE* fp;
		fp = fopen("学生账号信息档案.txt", "r");//读取文件操作
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
			printf("\n登录成功!");
			printf("按任意键进入学生信息管理系统!\n");
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
			printf("\n账号或者密码输入错误，你还有%d次机会，请重新输入：\n", 2 - i);
		}
	}
	if (i == 3)
	{
		printf("登录失败\n");
		return;
	}

}

//系统说明功能 
void help()
{
	printf("\n\t欢迎使用学生系统帮助！\n");
	printf("\n1、初次进入系统后,请先选择录入学生信息;\n");
	printf("\n2、按照菜单提示键输入数字代号选择功能;\n");
	printf("\n3、增加学生信息后,信息会被保存在该程序所在的文件夹中的《学生信息档案》文件中;\n");
	printf("\n4、增加学生信息时，注意不要重复添加学号相同的信息;\n");
	printf("\n5、如果系统卡住，请关闭程序重新登录;\n");
	printf("\n6、注意！！！进行完一切操作后，记得退出系统，非正常手段关闭程序信息将无法保存！;\n");
	printf("\n\t谢谢您的观看！再见\n");
}

//录入功能 
void insertNodeByHead(struct Node* headNode)
{
	struct student data;
	struct Node* pMove = headNode->next;
	printf("请输入学生姓名，学号，年龄，性别，电话，高数成绩，线代成绩，程序设计成绩：\n");
	scanf("%s%s%d%s%s%d%d%d", &data.name, &data.num, &data.age, &data.sex, &data.telephone,&data.math,&data.Linear,&data.C);
	data.total = data.C + data.math + data.Linear;
	data.grade = ((data.math / 10.0 - 5) * 5 + (data.Linear / 10.0 - 5) * 5 + (data.C / 10.0 - 5) * 3) / 13.0;

	while (pMove != NULL)
	{
		if(strcmp(pMove->data.num, data.num) == 0)
		{
			printf("录入信息学号重复，请重新录入信息\n");
			break;
		}
		pMove = pMove->next;
	}
	struct Node* newNode = createNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
}

//删除功能 
void deleteNode(struct Node* headNode)
{
	printf("请输入删除的学生学号:\n");
	scanf("%s", &number);
	struct Node* posNode = headNode->next;
	struct Node* posFrontNode = headNode;

	if (posNode == NULL)
	{
		printf("数据为空，无法删除！\n");
		return;
	}
	//姓名是字符串，字符串：strcmp
	while (strcmp(posNode->data.num, number))
	{
		posFrontNode = posNode;
		posNode = posFrontNode->next;
		if (posNode == NULL)
		{
			printf("未找到指定位置，无法删除！\n");
			return;
		}
	}
	posFrontNode->next = posNode->next;
	free(posNode);
	printf("学号为 % s学生的信息已经删除！\n", number);
}

//修改功能
void change(struct Node* headNode)
{
	printf("请输入要修改信息的学生学号：\n");
	scanf("%s", &number);

	struct Node* changeNode = headNode->next;
	if (changeNode == NULL)
	{
		printf("数据为空，无法改变！\n");
	}
	else
	{
		if (0 == strcmp(changeNode->data.num, number))
		{
			printf("请输入该学生要改变的信息选项：1、姓名 2、电话号码  3、年龄\n");
			int choose;
			scanf("%d", &choose);
			switch (choose)
			{
			case 1:
				printf("请输入您要修改的名字：");
				scanf("%s", nam);
				printf("修改的名字为：%s\n", nam);
				strcpy(changeNode->data.name, nam);
				printf("修改名字成功！\n");
				break;

			case 2:
				printf("请输入您要修改的电话号码");
				scanf("%s", &tele);
				printf("修改的电话号码为：%s\n", tele);
				strcpy(changeNode->data.telephone, tele);
				printf("修改电话号码成功！\n");
				break;

			case 3:
				printf("请输入您要修改的年龄：");
				scanf("%d", &ag);
				printf("修改的年龄为：%d\n", ag);
				changeNode->data.age = ag;
				printf("修改年龄成功！\n");
				break;

			default:
				printf("请输入正确的选项\n");
				break;
			}
		}
	}
}

//查找功能
struct Node* searchInfoByData(struct Node* headNode)
{
	printf("请输入要查找的学生学号:\n");
	scanf("%s", &number);
	struct Node* pMove = headNode->next;
	if (pMove == NULL)
	{
		printf("未找到相关信息!\n");
		return NULL;
	}
	while (strcmp(pMove->data.num, number))
	{
		pMove = pMove->next;
	}
	printf("姓名\t学号\t年龄\t性别\t电话\t\t高数成绩\t线代成绩\t程序成绩\t总成绩\t绩点\n");
	printf("%s\t%s\t%d\t%s\t%s\t%d\t\t%d\t\t%d\t\t%d\t%.2lf\n", pMove->data.name, pMove->data.num, pMove->data.age, pMove->data.sex, pMove->data.telephone, pMove->data.math, pMove->data.Linear, pMove->data.C, pMove->data.total , pMove->data.grade );
	return NULL;
}

//浏览功能 
void printList(struct Node* headNode)
{
	struct Node* pMove = headNode->next;
	printf("姓名\t学号\t年龄\t性别\t电话\t\t高数成绩\t线代成绩\t程序成绩\t总成绩\t绩点\n");
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
	printf("姓名\t高数成绩\t线代成绩\t程序成绩\t总成绩\t绩点\n");
	while (pMove)
	{
		printf("%s\t%s\t%d\t%s\t%s\t%d\t\t%d\t\t%d\t\t%d\t%.2lf\n", pMove->data.name, pMove->data.num, pMove->data.age, pMove->data.sex, pMove->data.telephone, pMove->data.math, pMove->data.Linear, pMove->data.C, pMove->data.total, pMove->data.grade);
		pMove = pMove->next;
	}
	printf("\n");
}
//总成绩排名
struct Node* sortStudentListByTotal(struct Node* head)
{
	if (head != NULL)
	{
		struct Node* p1, * p2, * max;
		struct student s;

		p1 = head;
// 简单选择排序
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



//文件的读取
void readInfoToFile(struct Node* headNode,const char* fileName)
{
	//1、打开文件
	FILE* fp;//文件指针名 
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
		//2、读文件 
	    while (fscanf(fp,"%s\t%s\t%d\t%s\t%s\t%d\t%d\t%d\t%d\t%lf", &data.name,&data.num, &data.age, &data.sex, &data.telephone,&data.math,&data.Linear,&data.C,&data.total,&data.grade)!= EOF)
		{
			struct Node* newNode = createNode(data);
			newNode->next = headNode->next;
			 headNode->next=newNode ;
		}
	}

	//3、关闭文件
	fclose(fp);
}

//文件的存储
void writeInfoToFile(struct Node* headNode, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "wt+");
	if (fp == NULL)
	{
		printf("文件打开失败！\n");
	}
	struct Node* pMove = headNode->next;
	while (pMove)
	{
		fprintf(fp, "%s\t%s\t%d\t%s\t%s\t%d\t%d\t%d\t%d\t%.2lf\n", pMove->data.name, pMove->data.num, pMove->data.age, pMove->data.sex, pMove->data.telephone, pMove->data.math, pMove->data.Linear, pMove->data.C, pMove->data.total, pMove->data.grade );
		pMove = pMove->next;
	}
	//关闭文件 
	fclose(fp);
}

//系统菜单 
void menu()
{
	//所有操作都同步到文件
	printf("*********************************************\n");
	printf("------------【学生信息管理系统】-------------\n");
	printf("*********************************************\n\n");
	printf("****************系统功能菜单*****************\n");
	printf("*                                           *\n");
	printf("*\t\t┌──────────┐\t\t    *\n");
	printf("*\t\t│0.系统说明│\t\t    *\n");
	printf("*\t\t│1.录入信息│\t\t    *\n");
	printf("*\t\t│2.浏览信息│\t\t    *\n");
	printf("*\t\t│3.修改信息│\t\t    *\n");
	printf("*\t\t│4.删除信息│\t\t    *\n");
	printf("*\t\t│5.查找信息│\t\t    *\n");
	printf("*\t\t│6.查看排名│\t\t    *\n");
	printf("*\t\t│7.退出系统│\t\t    *\n");
	printf("*\t\t└──────────┘\t\t    *\n");
	printf("*                                           *\n");
	printf("******************欢迎使用*******************\n\n");
}
void menu1()
{
	//所有操作都同步到文件
	printf("*********************************************\n");
	printf("------------【学生信息管理系统】-------------\n");
	printf("*********************************************\n\n");
	printf("****************系统功能菜单*****************\n");
	printf("*                                           *\n");
	printf("*\t\t┌──────────┐\t\t    *\n");
	printf("*\t\t│0.系统说明│\t\t    *\n");
	printf("*\t\t│1.查看信息│\t\t    *\n");
	printf("*\t\t│2.查看排名│\t\t    *\n");
	printf("*\t\t│3.退出系统│\t\t    *\n");
	printf("*\t\t└──────────┘\t\t    *\n");
	printf("*                                           *\n");
	printf("******************欢迎使用*******************\n\n");
}

//用户的交互
void interaction()
{
	int choice;
	printf("请选择您想使用的功能：");
	scanf("%d", &choice);
	switch (choice)
	{
	case 0:
		printf("\n--------【系统说明】--------");
		help();
		break;
	case 1:
		printf("\n--------【录入信息】--------\n");
		insertNodeByHead(list);
		break;
	case 2:
		printf("\n--------【浏览信息】--------\n");
		printList(list);
		break;
	case 3:
		printf("\n--------【修改信息】--------\n");
		change(list);
		break;
	case 4:
		printf("\n--------【删除信息】--------\n");
		deleteNode(list);
		break;
	case 5:
		printf("\n--------【查找信息】--------\n");
		searchInfoByData(list);
		break;
	case 6:
		printf("\n--------【查看排名】--------\n");
		sortStudentListByTotal(list);
		printList(list);
		break;
	case 7:
		printf("\n--------【系统已退出】-------\n");
		writeInfoToFile(list, "学生信息档案.txt");
		system("pause");
		exit(0);
		break;
	default:
		printf("选择错误，请重新输入\n");
		break;
	}
}
void interaction1()
{
	int choice;
	printf("请选择您想使用的功能：");
	scanf("%d", &choice);
	switch (choice)
	{
	case 0:
		printf("\n--------【系统说明】--------");
		help();
		break;
	case 1:
		printf("\n--------【查看信息】--------\n");
		searchInfoByData(list);
		break;
	case 2:
		printf("\n--------【查看排名】--------\n");
		sortStudentListByTotal(list);
		printList1(list);
		break;
	case 3:
		printf("\n--------【系统已退出】-------\n");
		system("pause");
		writeInfoToFile(list, "学生信息档案.txt");
		exit(0);
		break;
	default:
		printf("选择错误，请重新输入\n");
		break;
	}
}

int main() {
	//system("color 81");
	list = createList();
	readInfoToFile(list, "学生信息档案.txt");

	while (1)
	{
		Hello();
		system("pause");
		system("cls"); 
		
	}
	return 0;
}