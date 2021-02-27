#include <stdio.h>
#include <stdlib.h>


typedef struct polynomial
{
	int coefficient;//ϵ��
	int index;//ָ��
	struct polynomial *next;
} LNode, *LinkList;
void CreatePoly(LinkList L);
void OrderInsert(LinkList L, int coe, int ind);
int compare(int a, int b);
void DisPlay(LinkList L);
void OrderPlus(LinkList La, LinkList Lb, LinkList Lc);

int main()
{
	LinkList La;
	LinkList Lb;
	LinkList Lc;
	La = (LinkList)malloc(sizeof(LNode));
	La->next = NULL;
	Lb = (LinkList)malloc(sizeof(LNode));
	Lb->next = NULL;
	Lc = (LinkList)malloc(sizeof(LNode));
	Lc->next = NULL;
	printf("�����һ������ʽ\n");
	CreatePoly(La);
	printf("����ڶ�������ʽ\n");
	CreatePoly(Lb);
	OrderPlus(La, Lb, Lc);
	printf("��Ӻ�Ķ���ʽΪ\n");
	DisPlay(Lc);
	return 0;
}
void CreatePoly(LinkList L)
{
	int coe;//ϵ��
	int ind;//ָ��
	int n;
	printf("����������\n");
	scanf("%d", &n);
	for(int i = 0 ; i < n ; i++)
	{
		printf("�������%d���ϵ����ָ��\n", i + 1);
		scanf("%d%d", &coe, &ind);
		if(coe == 0 || ind < 0)
		{
			i--;
			printf("�����������������\n");
			continue;
		}
		OrderInsert(L, coe, ind);
	}
}
int compare(int a, int b)
{
	return (a > b ? 1 : 0);
}
void OrderInsert(LinkList L, int coe, int ind)
{
	LinkList q = L->next;
	LinkList pre = L;
	if(L->next  == NULL)
	{
		LinkList p = (LinkList)malloc(sizeof(LNode));
		p->coefficient = coe;
		p->index = ind;
		p->next = NULL;
		L->next = p;
	}
	else
	{
		while(q != NULL && compare(ind, q->index))
		{
			pre = q;
			q = q->next;
		}
		LinkList p = (LinkList)malloc(sizeof(LNode));
		p->coefficient = coe;
		p->index = ind;
		p->next = q;
		pre->next = p;
	}
}
void DisPlay(LinkList L)
{
	LinkList p = L->next;
	if(p->index == 0)
		printf("%d", p->coefficient);
	else if(p->index == 1)
	{
		if(p->coefficient == 1 || p->coefficient == -1)
		{
			if(p->coefficient < 0)
				printf("x");
			else
				printf("+x");
		}
		else
		{
			if(p->coefficient < 0)
				printf("%dx", p->coefficient);
			else
				printf("+%dx", p->coefficient);
		}
	}
	else
	{
		if(p->coefficient == 1  || p->coefficient == -1)
			if(p->coefficient < 0)
				printf("x^%d",  p->index);
			else
				printf("+x^%d",  p->index);
		else
		{
			printf("%dx^%d", p->coefficient, p->index);
		}
	}
	p = p->next;
	while(p != NULL)
	{
		if(p->index == 0)
		{
			printf("%d", p->coefficient);
		}
		else if(p->index == 1)
		{
			if(p->coefficient == 1 || p->coefficient == -1)
			{
				if(p->coefficient < 0)
					printf("x");
				else
					printf("+x");
			}
			else
			{
				if(p->coefficient < 0)
					printf("%dx", p->coefficient);
				else
					printf("+%dx", p->coefficient);
			}
		}
		else
		{
			if(p->coefficient == 1 || p->coefficient == -1)
			{
				if(p->coefficient < 0)
					printf("x*%d", p->index);
				else
					printf("+x%d", p->index);
			}
			else
			{
				if(p->coefficient < 0)
					printf("%dx^%d", p->coefficient, p->index);
				else
					printf("+%dx^%d", p->coefficient, p->index);
			}
		}
		p = p->next;
	}
}
void OrderPlus(LinkList La, LinkList Lb, LinkList Lc)
{
	LinkList la = La->next;
	LinkList lb = Lb->next;
	LinkList lc = Lc;
	while(la != NULL && lb != NULL)
	{
		LinkList p;
		p = (LinkList)malloc(sizeof(LNode));
		if(la->index == lb->index)//��ָ����ͬ
		{
			p->coefficient = la->coefficient + lb->coefficient;//ϵ�����
			p->index = la->index;
			p->next = NULL;
			lc->next = p;
			la = la->next;//ָ�����
			lb = lb->next;
		}
		else if(la->index < lb->index)//��ǰ��С�ں��ߣ����ǰ�߲��뵽���������
		{
			p->coefficient = la->coefficient;
			p->index = la->index;
			p->next = NULL;
			lc->next = p;
			la = la->next;
		}
		else//���򣬰Ѻ��߲��뵽���������
		{
			p->coefficient = lb->coefficient;
			p->index = lb->index;
			p->next = NULL;
			lc->next = p;
			lb = lb->next;
		}
		lc = lc->next;
	}
	if(la == NULL)
		lc->next = lb;
	else
		lc->next = la;
}
