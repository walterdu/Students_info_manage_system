#define  _CRT_SECURE_NO_WARNINGS
//#define _TEST_VERSER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

struct SUser
{
	int nNumb;
	char sName[20];
	float fMath;
};
typedef SUser DATA;

struct SNode
{
	DATA data;//28 Byte
	SNode* pNext; //4 Byte
};

SNode* g_pHead = NULL;



void AddHead(DATA data)
{//
	SNode* p = (SNode*)malloc(sizeof(SNode));
	p->data = data;
	p->pNext = g_pHead;

	g_pHead = p;
}
void AddTail(DATA data)
{
	SNode* pNew = (SNode*)malloc(sizeof(SNode));
	pNew->data = data;
	pNew->pNext = NULL;
	if (!g_pHead)
	{
		g_pHead = pNew;
		return;
	}
	SNode* p = g_pHead;
	while (p->pNext != NULL)
		p = p->pNext;
	p->pNext = pNew;
}

void Save()
{
	FILE* pf = fopen("stud.lv", "w");
	if (!pf)
	{
		puts("Save file fail！");
		return;
	}
	SNode* p = g_pHead;
	while (p)
	{
		fwrite(p, 1, sizeof(p->data), pf);
		//fwrite(&p->data, 1, sizeof(p->data), pf);
		p = p->pNext;
	}
	fclose(pf);
}
void Print()
{
	SNode* p = g_pHead;
	puts("student number\t name\t subject(Math)");
	int i = 0;
	while (p)
	{
		printf("%d\t%s\t%0.1f\n", p->data.nNumb,
			p->data.sName, p->data.fMath);
		p = p->pNext;
		i++;

	}

	printf("Sum: %d record \n", i);
	system("pause");

}
void Input(int nDir) //directions: 方向dir
{
	int nNumb;
	printf("Please input student number：");
	scanf_s("%d", &nNumb);
	DATA data;
	data.nNumb = nNumb;
	printf("Please input student name：");
	scanf_s("%s", data.sName, sizeof(data.sName));
	printf("Please input grades of math：");
	scanf_s("%f", &data.fMath);
	if (nDir == 1)
		AddHead(data);
	else
		AddTail(data);
	Save();
	Print();

}
int AddMenu()
{
	system("cls");
	puts("\n\n\t\t1、Insert to head");
	puts("\t\t2、Insert to tail");
	puts("\t\t0、Back to main menu");
	int i = 0;
	scanf_s("%d", &i);
	switch (i)
	{
	case 1:
	case 2:
		Input(i);
		break;
	}
	return i;
}
int Judge(SNode* q, SNode* m, int nIndex)
{
	switch (nIndex)
	{
	case 1:
		return q->data.nNumb < m->data.nNumb;
	case 2:
		return strcmp(q->data.sName, m->data.sName) < 0;
	case 3:
		return q->data.fMath > m->data.fMath;
	}
	return 0;
}
/*
void Sort(int nIndex)
{
SNode* p = g_pHead;
if (!p)
return;
while (p ->pNext)
{
SNode* q = p->pNext;
SNode* m = p;
while (q)
{
if (Judge(q,m,nIndex))
m = q;
q = q->pNext;
}

if (m != p)
{
DATA t = p->data;
p->data = m->data;
m->data = t;
}


p = p->pNext;
}
Print();
}*/

void PrintS(SNode** ps)
{
	puts("student number\t name\t subject(Math)");
	int i = 0;
	while (ps[i])
	{
		SNode* p = ps[i];//ps[i]都是SNode*类型
		printf("%d\t%s\t%0.1f\n", p->data.nNumb, p->data.sName, p->data.fMath);
		++i;
	}

	printf("Sum: %d records\n", i);
	system("pause");
}
void Sort(int nIndex)
{
	if (!g_pHead)
		return;
	SNode* p = g_pHead;
	//SNode* ps[100] = {0};
	int n = 0, i = 0;
	while (p)
	{
		p = p->pNext;
		++n;
	}

	SNode** ps = (SNode**)malloc(sizeof(SNode*)* n);
	n = 0;
	while (p)
	{
		ps[n] = p;
		p = p->pNext;
		++n;
	}
	ps[n] = NULL;
	while (i < n - 1)
	{
		int j = i + 1;
		int m = i;
		while (j < n)
		{
			if (Judge(ps[j], ps[m], nIndex)) //ps[j] ps[i] 与ps[m]的类型都是SNode*类型
				m = j;
			++j;
		}
		if (m != i)
		{
			SNode* t = ps[i];
			ps[i] = ps[m];
			ps[m] = t;
		}
		++i;
	}

	PrintS(ps);
}
int SortMenu()
{
	system("cls");
	puts("\n\n\t\t1、Sort by student number");
	puts("\t\t2、Sort by student name");
	puts("\t\t3、Sort by math grade");
	puts("\t\t4、print without sorting ");
	puts("\t\t0、Back to main menu");
	int i = 0;
	scanf_s("%d", &i);
	switch (i)
	{
	case 1:
	case 2:
	case 3:
		Sort(i);
		break;
	case 4:
		Print();
		break;
	}

	return i;
}
void Modify()
{
	int nNumb;
	printf("Please input student number that you wanna modify：");
	scanf_s("%d", &nNumb);
	SNode* p = g_pHead;

	while (p->pNext)
	{
		if (p->data.nNumb == nNumb)
			break;
		p = p->pNext;
	}
	if (!p)
	{
		puts("the number that you input is not exsiting");
		return;
	}
	printf("%d\t%s\t%0.1f\n\n", p->data.nNumb, p->data.sName, p->data.fMath);
	printf("Please input name and grades：");
	scanf_s("%s", p->data.sName, sizeof(p->data.sName));
	scanf_s("%f", &p->data.fMath);
	Save();
	Print();

}
int DelNumber(int nNumb)
{//算法代码
	SNode* p = g_pHead, *p1 = NULL;
	if (!p)
		return 0;
	if (p->data.nNumb == nNumb)
	{
		g_pHead = p->pNext;
		free(p);
		return 1;
	}
	while (p)
	{
		if (p->data.nNumb == nNumb)
		{
			p1->pNext = p->pNext;
			free(p);
			return 1;
		}
		p1 = p;
		p = p->pNext;
	}
	return 0;//means fail
}
void Delete()
{//业务代码
	char c;
	do
	{
		int nNumb;
		printf("Please input the num that you wanna delete请输入要删除的学号：");
		scanf_s("%d", &nNumb);
		if (DelNumber(nNumb))
		{
			Save();
			Print();
		}
		else
			puts("the number that you input is not exsiting");
		printf("continue to delete？[y/n]");
		fflush(stdin);
		c = getchar();
	} while (c == 'y' || c == 'Y');
}
int Menu()
{
	system("cls");//clear screen
	puts("\n\t\t1、Scan all the information");
	puts("\t\t2、Add infomation ");
	puts("\t\t3、Delete infomation");
	puts("\t\t4、Modify infomation");
	puts("\t\t5、Search infomation");
	puts("\t\t6、Color setting");
	puts("\t\t0、Exit");
	printf("\t\t Please choose：");
	int i = 0;
	scanf_s("%d", &i);
	switch (i)
	{
	case 1:
		while (SortMenu())
			;
		break;
	case 2:
		while (AddMenu())
			;
		break;
	case 3:
		Delete();
		break;
	case 4:
		Modify();
		break;
	}

	return i;
}

void Load()
{
	FILE* pf = fopen("stud.lv", "r");
	if (!pf)
		return;
	DATA data;
	while (fread(&data, 1, sizeof(data), pf) == sizeof(data))
		AddTail(data);
	fclose(pf);
}
int main()
{
	system("color 1f");

	printf("\n\n");
#ifdef _TEST_VERSER
	puts("This is test version");
#else
	printf("  \t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("  \t┃ *********************************************************┃\n");
	printf("  \t┃***┏━━━━━━━━━━━━━━━━━━━━━━━━┓***┃\n");
	printf("  \t┃***┃************************************************┃***┃\n");
	printf("  \t┃***┃***                                         ****┃***┃\n");
	printf("  \t┃***┃***   Welcome to Student Info Manage System ****┃***┃\n");
	printf("  \t┃***┃***                                         ****┃***┃\n");
	printf("  \t┃***┃***                                         ****┃***┃\n");
	printf("  \t┃***┃***                  walterdu              **** |***┃\n");
	printf("  \t┃***┃***                                         ****┃***┃\n");
	printf("  \t┃***┃***                2015.04.15               ****┃***┃\n");
	printf("  \t┃***┃***                                         ****┃***┃\n");
	printf("  \t┃***┃************************************************┃***┃\n");
	printf("  \t┃***┗━━━━━━━━━━━━━━━━━━━━━━━━┛***┃\n");
	printf("  \t┃ *********************************************************┃\n");
	printf("  \t┗━━━━━━━━━press anykey to continue ━━━━━━━━┛\n");
#endif
	char c = _getch();
	//system("pause");
	Load();
	while (Menu())
		;
	return 0;
}