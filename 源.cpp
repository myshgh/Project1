#include <sdkddkver.h>
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

struct subject
{
	char subName[20];
	int credit;
	int score;
	// int id;
};
vector<subject> fileSubjects;
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
	vector<subject> subjects;
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
	struct Node *next;
};
struct Node *list;

struct Node *createList();
struct Node *createNode(struct student data);
struct Node *sortStudentListByTotal(struct Node *head);
void changeGrade(struct Node *headNode);
void addSubject(struct Node *headNode);
void deleteSubject(struct Node *headNode);
void changeSubject(struct Node *headNode);
void Hello();
void registeruser();
void registeruser1();
void login();
void login1();
void help();
void insertNodeByHead(struct Node *headNode);
int deleteNode(struct Node *headNode);
void change(struct Node *headNode);
struct Node *searchInfoByData(struct Node *headNode);
void printList1(struct Node *headNode);
void printList(struct Node *headNode);
void readInfoToFile(struct Node *headNode, char *fileName);
void writeInfoToFile(struct Node *headNode, char *fileName);
void menu();
void menu1();
void interaction();
void interaction1();

//创建信息表
struct Node *createList()
{
	//结构体变量表示表头
	//指针变成变量  用动态内存申请
	struct Node *headNode = new Node();
	headNode->next = NULL;
	return headNode;
};

//创建结点
struct Node *createNode(struct student data)
{
	struct Node *newNode = new Node();
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
};
// 添加，减少，修改科目
/*
	char subName[20];
	int credit;
	int score;
*/

void changeGrade(struct Node *headNode)
{
	struct Node *pMove = headNode->next;
	while (pMove != NULL)
	{
		int index = fileSubjects.size();
		int i = 0;
		int credits = 0;  // 总学分
		double grade = 0; // 当前加权
		while (i < index)
		{
			credits += pMove->data.subjects[i].credit;
			grade += (pMove->data.subjects[i].score / 10.0 - 5) * pMove->data.subjects[i].credit;
			// printf("!!!!!%lf\n", grade);
			i++;
		}
		// printf("!!%lf", grade);
		pMove->data.grade = grade / credits;
		// printf("!%lf", pMove->data.grade);
		pMove = pMove->next;
	}
}
void addSubject(struct Node *headNode)
{
	struct subject temp;
	printf("请输入要增加学科的名称，学分:\n");
	scanf("%s%d", temp.subName, &temp.credit);
	temp.score = 0;
	// 查重学科名
	auto iter = find_if(fileSubjects.begin(), fileSubjects.end(), [temp](subject n)
						{ return (0 == strcmp(n.subName, temp.subName)); });
	if (iter != fileSubjects.end())
	{
		printf("学科重复！");
		return;
	}
	else
	{
		fileSubjects.push_back(temp);
	}
	struct Node *changeNode = headNode->next;
	// 更改所有学生链表的内容
	while (changeNode)
	{
		changeNode->data.subjects.push_back(temp);
		changeNode = changeNode->next;
	}
	changeGrade(list);
}
void deleteSubject(struct Node *headNode)
{
	char name[20];
	printf("输入要删除的学科的名称：");
	scanf("%s", name);
	auto iter = find_if(fileSubjects.begin(), fileSubjects.end(), [name](subject n)
						{ return (0 == strcmp(n.subName, name)); });
	// 删除vector学科内容
	if (iter == fileSubjects.end())
	{
		printf("删除失败！");
		return;
	}
	else
	{
		fileSubjects.erase(iter);
		printf("删除成功！");
	}
	// 更改所有学生链表的内容
	struct Node *changeNode = headNode->next;

	while (changeNode)
	{
		auto iter = find_if(changeNode->data.subjects.begin(), changeNode->data.subjects.end(), [name](subject n)
							{ return (0 == strcmp(n.subName, name)); });
		// 删除vector学科内容
		if (iter == changeNode->data.subjects.end())
		{
			// printf("\nif删除失败！");
			return;
		}
		else
		{
			// printf("\nelse删除成功！");

			changeNode->data.subjects.erase(iter);
		}
		changeNode = changeNode->next;
	}
	changeGrade(list);
}
void changeSubject(struct Node *headNode)
{
	char name[20];
	int credit;
	printf("输入要修改的学科的名称：");
	scanf("%s", name);
	auto iter = find_if(fileSubjects.begin(), fileSubjects.end(), [name](subject n)
						{ return (0 == strcmp(n.subName, name)); });
	// 删除vector学科内容
	if (iter == fileSubjects.end())
	{
		printf("修改失败！");
		return;
	}
	else
	{
		printf("修改后的名称和学分：\n");
		scanf("%s%d", name, &credit);
		iter->credit = credit;
		strcpy(iter->subName, name);
	}
	struct Node *changeNode = headNode->next;
	// 更改所有学生链表的内容
	while (changeNode)
	{
		auto iter = find_if(changeNode->data.subjects.begin(), changeNode->data.subjects.end(), [name](subject n)
							{ return (0 == strcmp(n.subName, name)); });
		// 删除vector学科内容
		if (iter == fileSubjects.end())
		{
			return;
		}
		else
		{
			iter->credit = credit;
			strcpy(iter->subName, name);
		}
		changeNode = changeNode->next;
	}
	changeGrade(list);
}
//登录界面
void Hello()
{
	char se[100];
	char a;
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
	scanf("%s", se);
	if (se[1] == '\0')
	{
		a = se[0];

		switch (a)
		{
		case '1':
			login();
			break;
		case '2':
			login1();
			break;
		case '3':
			registeruser();
			break;
		case '4':
			registeruser1();
			break;
		case '5':
			printf("\n\t\t【成功退出】\n");
			exit(0);
			system("pause");
			break;
		default:
			printf("请输入正确的数字");
			break;
		}
	}
}

// 注册账号功能
void registeruser()
{
	char ac[30];
	char pw[20], pd[20],w,d;
	int i, a = 0;

	printf("\t\t【注册帐号】\n");
	FILE *fp = fopen("账号信息档案.txt", "ab");
	printf("请输入用户账号和密码(账号、密码可以为数字,中文字母,英文字母,符号,密码必须6位)\n\n\n");
	printf("\t请你输入账号：");
	scanf("%s", &ac);
	int flag = 0;
	fp = fopen("账号信息档案.txt", "a+"); //读取文件操作
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
		int index=0;
		while(index<6)
		{
			w=_getch();
			string pattern("^\\w+$");
			regex r (pattern);
			smatch results;
			pw[index]=w;
			pw[index+1]='\0';
			string inputChar=pw;
			if(regex_match(inputChar,results,r))
			{
				printf("*");
				pw[index++]=w;
			}
			if(index>0&&w==VK_BACK)
			{
				printf("\b \b");
				pw[index--]='\0';
			}
			pw[6]='\0';
           
		}
		
		printf("\n\n\t再次确认密码：");
		index=0;
		while(index<6)
		{
			d=_getch();
			string pattern("^\\w+$");
			regex r (pattern);
			smatch results;
			pd[index]=d;
			pd[index+1]='\0';
			string inputChar=pd;
			if(regex_match(inputChar,results,r))
			{
				printf("*");
				pd[index++]=d;
			}
			if(index>0&&d==VK_BACK)
			{
				printf("\b \b");
				pd[index--]='\0';
			}
			pd[6]='\0';
		}
		for(i=0;i<7;i++)
		{
			if (pw[i] != pd[i])
			{
				printf("\n密码不对，请重新注册账号\n");
				return;
			}
		}
		strcpy(use[a].pw,pw);
		fprintf(fp, "账号\t密码\n");
		fprintf(fp, "%s\t%s\n", use[a].ac, use[a].pw);
		printf("\n注册成功!!!\n");
		fclose(fp);
	}
	system("pause");
	system("cls");
}

void registeruser1()
{
	char ac[30];
	char pw[20], pd[20],w,d;
	int i, a = 0;

	printf("\t\t【注册帐号】\n");
	FILE *fp = fopen("学生账号信息档案.txt", "ab");
	printf("请输入用户账号和密码(账号、密码可以为数字,中文字母,英文字母,符号,密码必须6位)\n\n\n");
	printf("\t请你输入账号：");
	scanf("%s", &ac);
	int flag = 0;
	fp = fopen("学生账号信息档案.txt", "a+"); //读取文件操作
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
		int index=0;
		while(index<6)
		{
			w=_getch();
			string pattern("^\\w+$");
			regex r (pattern);
			smatch results;
			pw[index]=w;
			pw[index+1]='\0';
			string inputChar=pw;
			if(regex_match(inputChar,results,r))
			{
				printf("*");
				pw[index++]=w;
			}
			if(index>0&&w==VK_BACK)
			{
				printf("\b \b");
				pw[index--]='\0';
			}
			pw[6]='\0';
           
		}
		
		printf("\n\n\t再次确认密码：");
		index=0;
		while(index<6)
		{
			d=_getch();
			string pattern("^\\w+$");
			regex r (pattern);
			smatch results;
			pd[index]=d;
			pd[index+1]='\0';
			string inputChar=pd;
			if(regex_match(inputChar,results,r))
			{
				printf("*");
				pd[index++]=d;
			}
			if(index>0&&d==VK_BACK)
			{
				printf("\b \b");
				pd[index--]='\0';
			}
			pd[6]='\0';
		}
		for(i=0;i<7;i++)
		{
			if (pw[i] != pd[i])
			{
				printf("\n密码不对，请重新注册账号\n");
				return;
			}
		}
		strcpy(use[a].pw,pw);
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
	int i, j, a = 0;
	int flag = 0;
	printf("--------【登录账号】--------\n");
	for (i = 0; i < 3; i++)
	{
		printf("请输入帐号:");
		scanf("%s", ac);
		printf("请输入密码:");
		int index = 0;
		while (index < 6)
		{
			pw = _getch();
			string pattern("^\\w+$");
			// 定义一个用于查找模式的regex
			regex r(pattern);
			// 定义一个对象保存搜索结果
			smatch results;
			ad[index] = pw;
			ad[index + 1] = '\0';
			string inputChar = ad;
			// 如果有匹配，则为真
			if (regex_match(inputChar, results, r))
			{
				printf("*");
				ad[index++] = pw;
			}
			else
			{
				// cout << inputChar << endl;
				if (index > 0 && pw == VK_BACK)
				{
					printf("\b \b");
					ad[index--] = '\0';
				}
			}
		}
		ad[6] = '\0';
		FILE *fp;
		fp = fopen("账号信息档案.txt", "r"); //读取文件操作
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
		else
		{
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
	int i, j, a = 0;
	int flag = 0;

	printf("--------【登录账号】--------\n");
	for (i = 0; i < 3; i++)
	{
		printf("请输入帐号:");
		scanf("%s", ac);
		printf("请输入密码:");
		int index = 0;
		while (index < 6)
		{
			pw = _getch();
			string pattern("^\\w+$");
			// 定义一个用于查找模式的regex
			regex r(pattern);
			// 定义一个对象保存搜索结果
			smatch results;
			ad[index] = pw;
			ad[index + 1] = '\0';
			string inputChar = ad;
			// 如果有匹配，则为真
			if (regex_match(inputChar, results, r))
			{
				printf("*");
				ad[index++] = pw;
			}
			else
			{
				// cout << inputChar << endl;
				if (index > 0 && pw == VK_BACK)
				{
					printf("\b \b");
					ad[index--] = '\0';
				}
			}
		}
		ad[6] = '\0';
		FILE *fp;
		fp = fopen("学生账号信息档案.txt", "r"); //读取文件操作
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
		else
		{
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
void insertNodeByHead(struct Node *headNode)
{
	struct student data;
	struct Node *pMove = headNode->next;
	printf("请输入学生姓名，学号，年龄，性别，电话，各科成绩：\n");
	scanf("%s%s%d%s%s", &data.name, &data.num, &data.age, &data.sex, &data.telephone);
	string pattern("^(?: (?: \\+|00)86)?1[3-9]\\d{9}$");
	string numbers = data.telephone;
	regex r(pattern);
	smatch results;
	if (regex_match(numbers, results, r))
	{
		// TODO：动态增加科目
		int index = fileSubjects.size();
		int i = 0;
		int credits = 0;  // 总学分
		double grade = 0; // 当前加权
		while (i < index)
		{
			subject temp;
			printf("%s: ", fileSubjects[i].subName);
			scanf("%d", &temp.score);
			strcpy(temp.subName, fileSubjects[i].subName);
			temp.credit = fileSubjects[i].credit;
			data.total += temp.score;
			credits += temp.credit;
			grade += (temp.score / 10.0 - 5) * temp.credit;
			data.subjects.push_back(temp);
			i++;
		}
		data.grade = grade / credits;
	}
	else
	{
		printf("请输入正确的电话号");
		return;
	}

	while (pMove != NULL)
	{
		if (strcmp(pMove->data.num, data.num) == 0)
		{
			printf("录入信息学号重复，请重新录入信息\n");
			break;
		}
		pMove = pMove->next;
	}
	struct Node *newNode = createNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
}

//删除功能
int deleteNode(struct Node *headNode)
{
	printf("请输入学生的学号:\n");
	scanf("%s", &number);
	struct Node *posNode = headNode->next;
	struct Node *posFrontNode = headNode;

	if (posNode == NULL)
	{
		printf("数据为空！\n");
		return 0;
	}
	//姓名是字符串，字符串：strcmp
	while (strcmp(posNode->data.num, number))
	{
		posFrontNode = posNode;
		posNode = posFrontNode->next;
		if (posNode == NULL)
		{
			printf("未找到指定位置！\n");
			return 0;
		}
	}
	posFrontNode->next = posNode->next;
	delete posNode;
	printf("学号为 % s学生的信息已经处理！\n", number);
	return 1;
}

//修改功能
void change(struct Node *headNode)
{
	printf("请输入要修改信息的学生学号：\n");
	scanf("%s", &number);

	struct Node *changeNode = headNode->next;
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
struct Node *searchInfoByData(struct Node *headNode)
{
	printf("请输入要查找的学生学号:\n");
	scanf("%s", &number);
	struct Node *pMove = headNode->next;
	if (pMove == NULL)
	{
		printf("未找到相关信息!\n");
		return NULL;
	}
	while (pMove != NULL)
	{
		if (strcmp(pMove->data.num, number) == 0)
		{
			printf("姓名\t学号\t年龄\t性别\t电话\t\t高数成绩\t线代成绩\t程序成绩\t总成绩\t学分\n");
			pMove->data.grade = ((pMove->data.math / 10 - 5) * 5 + (pMove->data.Linear / 10 - 5) * 5 + (pMove->data.C / 10 - 5) * 3) / 13.0;
			printf("%s\t%s\t%d\t%s\t%s\t%d\t\t%d\t\t%d\t\t%d\t%.2f\n", pMove->data.name, pMove->data.num, pMove->data.age, pMove->data.sex, pMove->data.telephone, pMove->data.math, pMove->data.Linear, pMove->data.C, pMove->data.total = pMove->data.math + pMove->data.Linear + pMove->data.C, pMove->data.grade);
		}
		pMove = pMove->next;
	}

	return NULL;
}

//浏览功能
void printList(struct Node *headNode)
{
	struct Node *pMove = headNode->next;
	printf("姓名\t学号\t年龄\t性别\t电话\t\t各科成绩,总成绩,绩点\n");
	while (pMove)
	{
		int index = fileSubjects.size();
		int i = 0;
		printf("%s\t%s\t%d\t%s\t%s", pMove->data.name, pMove->data.num, pMove->data.age, pMove->data.sex, pMove->data.telephone);
		while (i < index)
		{
			printf("\t%s: %d", pMove->data.subjects[i].subName, pMove->data.subjects[i].score);
			i++;
		}

		printf("\t总分：%d\t绩点：%.2f\n", pMove->data.total, pMove->data.grade);
		pMove = pMove->next;
	}
	printf("\n");
}
void printList1(struct Node *headNode)
{
	struct Node *pMove = headNode->next;
	printf("姓名\t\t各科成绩,总成绩,绩点\n");
	while (pMove)
	{
		int index = fileSubjects.size();
		int i = 0;
		printf("%s", pMove->data.name);
		while (i < index)
		{
			printf("\t%s: %d", pMove->data.subjects[i].subName, pMove->data.subjects[i].score);
			i++;
		}

		printf("\t总分：%d\t绩点：%.2f\n", pMove->data.total, pMove->data.grade);
		pMove = pMove->next;
	}
	printf("\n");
}
//总成绩排名
struct Node *sortStudentListByTotal(struct Node *head)
{
	if (head != NULL)
	{
		struct Node *p1, *p2, *max;
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
void readInfoToFile(struct Node *headNode, const char *fileName)
{
	fileSubjects.clear();
	FILE *fpScore = fopen("./score.txt", "rt");
	subject temp;
	int index = 0;
	if (fpScore)
	{
		while (fscanf(fpScore, "%s\t%d\t%d", temp.subName, &temp.credit, &temp.score) != EOF)
		{
			fileSubjects.push_back(temp);
			// printf("vector: %s\t%d\t%d\n", fileSubjects[index].subName, fileSubjects[index].credit, fileSubjects[index].score);
			index++;
		}
	}
	// 1、打开文件
	FILE *fp; //文件指针名
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
		// 2、读文件
		while (fscanf(fp, "%s\t%s\t%d\t%s\t%s", data.name, data.num, &data.age, data.sex, data.telephone) != EOF)
		{
			int i = 0;
			while (i < index)
			{
				subject subject1;
				fscanf(fp, "%s\t%d\t%d", subject1.subName, &subject1.score, &subject1.credit);
				data.subjects.push_back(subject1);
				// printf("%s\t%d\t%d", subject1.subName, subject1.credit, subject1.score);
				i++;
			}
			// printf("aaaaaa%d\n", data.subjects.size());
			fscanf(fp, "%d\t%lf", &data.total, &data.grade);
			struct Node *newNode = createNode(data);
			data.subjects.clear();
			// printf("newNodeName:%s,num:%s,age:%d,sex:%s,tele:%s,total:%d,grade:%.2f\n\n", newNode->data.name, newNode->data.num, newNode->data.age, newNode->data.sex, newNode->data.telephone, newNode->data.total, newNode->data.grade);
			newNode->next = headNode->next;
			headNode->next = newNode;
		}
	}

	// 3、关闭文件
	fclose(fp);
	// fclose(fpScore);
}
/*
姓名	学号3	18	1	18343603793	工数    99  6	线代    99  4	C   99  3	297	4.35
姓名	学号2	18	男	18343603793	工数    99  6	线代    99  4	C   99  3	297	4.35
姓名	学号1	18	男	18343603793	工数    99  6	线代    99  4	C   99  3	297	4.35
姓名	学号	18	男	18343603793	工数    99  6	线代    99  4	C   99  3	297	4.35

工数    6   0
线代    4   0
C   3   0
*/
//文件的存储
void writeInfoToFile(struct Node *headNode, const char *fileName)
{
	FILE *fpScore = fopen("./score.txt", "wt");
	subject temp;
	if (fpScore)
	{
		for (auto a = fileSubjects.begin(); a < fileSubjects.end(); a++)
		{
			fprintf(fpScore, "%s\t%d\t%d\n", a->subName, a->credit, a->score);
		}
	}
	fclose(fpScore);
	FILE *fp;
	fp = fopen(fileName, "wt");
	if (fp == NULL)
	{
		printf("文件打开失败！\n");
	}
	struct Node *pMove = headNode->next;
	while (pMove)
	{
		// pMove->data.grade = ((pMove->data.math / 10.0 - 5) * 5 + (pMove->data.Linear / 10 - 5) * 5 + (pMove->data.C / 10 - 5) * 3) / 13.0;
		// fprintf(fp, "%s\t%s\t%d\t%s\t%s\t%d\t%d\t%d\t%d\t%.2f\n", pMove->data.name, pMove->data.num, pMove->data.age, pMove->data.sex, pMove->data.telephone, pMove->data.math, pMove->data.Linear, pMove->data.C, pMove->data.total, pMove->data.grade);
		fprintf(fp, "%s\t%s\t%d\t%s\t%s\t", pMove->data.name, pMove->data.num, pMove->data.age, pMove->data.sex, pMove->data.telephone);
		for (auto a = pMove->data.subjects.begin(); a < pMove->data.subjects.end(); a++)
		{
			// printf("%s\t%d\t%d\t\n", a->subName, a->score, a->credit);

			fprintf(fp, "%s\t%d\t%d\t", a->subName, a->score, a->credit);
		}
		fprintf(fp, "%d\t%.2f\n", pMove->data.total, pMove->data.grade);
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
	printf("*\t\t┌───────────┐\t\t    *\n");
	printf("*\t\t│0.系统说明 │\t\t    *\n");
	printf("*\t\t│1.录入信息 │\t\t    *\n");
	printf("*\t\t│2.浏览信息 │\t\t    *\n");
	printf("*\t\t│3.修改信息 │\t\t    *\n");
	printf("*\t\t│4.删除信息 │\t\t    *\n");
	printf("*\t\t│5.查找信息 │\t\t    *\n");
	printf("*\t\t│6.查看排名 │\t\t    *\n");
	printf("*\t\t│7.退出系统 │\t\t    *\n");
	printf("*\t\t│8.增加科目 │\t\t    *\n");
	printf("*\t\t│9.删除科目 │\t\t    *\n");
	printf("*\t\t│a.导出成绩 │\t\t    *\n");
	printf("*\t\t└───────────┘\t\t    *\n");
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
	char se[100];
	char choice;
	printf("请选择您想使用的功能：");
	scanf("%s", se);
	if (se[1] == '\0')
	{
		choice = se[0];
		switch (choice)
		{
		case '0':
			printf("\n--------【系统说明】--------");
			help();
			break;
		case '1':
			printf("\n--------【录入信息】--------\n");
			insertNodeByHead(list);
			break;
		case '2':
			printf("\n--------【浏览信息】--------\n");
			printList(list);
			break;
		case '3':
			printf("\n--------【修改信息】--------\n");
			if (deleteNode(list))
				insertNodeByHead(list);
			//	change(list);
			break;
		case '4':
			printf("\n--------【删除信息】--------\n");
			deleteNode(list);
			break;
		case '5':
			printf("\n--------【查找信息】--------\n");
			searchInfoByData(list);
			break;
		case '6':
			printf("\n--------【查看排名】--------\n");
			sortStudentListByTotal(list);
			printList(list);
			break;
		case '7':
			printf("\n--------【系统已退出】-------\n");
			system("pause");
			writeInfoToFile(list, "学生信息档案.txt");
			exit(0);
			break;
		case '8':
			printf("\n--------【增加科目】--------\n");
			addSubject(list);
			break;
		case '9':
			printf("\n--------【删除科目】--------\n");
			deleteSubject(list);

			break;
		case 'a':
			printf("\n--------【导出成绩】--------\n");
			writeInfoToFile(list, "导出.txt");
			break;
		default:
			printf("选择错误，请重新输入\n");
			break;
		}
	}
}
void interaction1()
{
	char se[100];
	char choice;
	printf("请选择您想使用的功能：");
	scanf("%s", se);
	if (se[1] == '\0')
	{
		choice = se[0];
		switch (choice)
		{
		case '0':
			printf("\n--------【系统说明】--------");
			help();
			break;
		case '1':
			printf("\n--------【查看信息】--------\n");
			searchInfoByData(list);
			break;
		case '2':
			printf("\n--------【查看排名】--------\n");
			sortStudentListByTotal(list);
			printList1(list);
			break;
		case '3':
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
}

int main()
{
	// system("color 81");
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