#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct student
{
	char ID[20];
	double Chinese;
	double Math;
	double English;
	double sum;
	double weight_average;
	struct student *next;
} LinkNode, *LinkList;

void InitList(LinkList *L);//��ʼ������
void GetInput(LinkList *p);//��ֵ
void InsertList(LinkList *L);//����ڵ�
void DisPlay(LinkList L);//��������
void Delete(LinkList *L, char input[]);//ɾ��ĳ���ڵ�
void LinkSort(LinkList *L);//����
void menu()
{
	printf("1������ѧ����Ϣ\n");
	printf("2�����ѧ����Ϣ\n");
	printf("3��ɾ��ѧ����Ϣ\n");
	printf("4����ѧ���ɼ�����\n");
	printf("5���˳�\n");
}
int main()
{
	int n, i;
	char input[20];
	LinkList L;
	InitList(&L);//��ʼ������

	int c;
	while(1)
	{
		printf("��ѡ��Ҫ���еĲ���:\n");
		menu();
		scanf("%d", &c);
		switch(c)
		{
		case 1:
			printf("����������\n");
			scanf("%d", &n);
			for(i = 0; i < n; i++)
			{
				InsertList(&L);
			}//����һ��ʼ��ѧ����Ϣ
			DisPlay(L);//��ӡ��ǰ��������Ϣ
			break;
		case 2:
			printf("��������ӵ�����:\n");
			scanf("%d", &n);
			for(i = 0; i < n; i++)
			{
				InsertList(&L);
			}//�������ѧ����Ϣ
			DisPlay(L);//��ӡ��ǰ������Ϣ
			break;
		case 3:
			printf("������Ҫɾ����ѧ��:\n");
			scanf("%s", input);//����ѧ��
			Delete(&L, input);//ɾ��
			DisPlay(L);//��ӡ��ǰ������Ϣ
			break;
		case 4:
			printf("���ڶ���������:\n");
			LinkSort(&L);//����������
			DisPlay(L);//��ӡ��ǰ������Ϣ
			break;
		case 5:
			printf("��лʹ��\n");
			return 0;
		}
	}
	return 0;
}
void InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(LinkNode));
	if(*L == NULL)
	{
		exit(0);
	}
	else
	{
		(*L) ->next = NULL;
	}
}
void GetInput(LinkList *p)
{
	printf("������ѧ��:\n");
	scanf("%s", (*p)->ID);
	printf("���������ĳɼ�\n");
	scanf("%lf", &(*p)->Chinese);
	printf("��������ѧ�ɼ�:\n");
	scanf("%lf", &(*p)->Math);
	printf("������Ӣ��ɼ�:\n");
	scanf("%lf", &(*p)->English);
	(*p)->sum = (*p)->Chinese + (*p)->English + (*p)->Math;
	(*p)->weight_average = (*p)->Chinese * 0.3 + (*p)->Math * 0.5 + (*p)->English * 0.2;
}
void InsertList(LinkList *L)
{
	LinkList p = (LinkList)malloc(sizeof(LinkNode));
	static LinkList tail;
	GetInput(&p);
	if((*L)->next == NULL)
	{
		(*L)->next = p;
		p->next  = NULL;
	}
	else
	{
		p->next  = NULL;
		tail->next = p;
	}
	tail = p;
}
void DisPlay(LinkList L)
{
	printf("���ڵ�ѧ����ϢΪ:\n");
	L =  L->next;
	while(L != NULL)
	{
		printf("ѧ��:%s\t����:%.2lf\t��ѧ:%.2lf\tӢ��:%.2lf\t�ܷ�:%.2lf\t��Ȩƽ����:%.2lf\n", L->ID, L->Chinese, L->Math, L->English, L->sum, L->weight_average);
		L = L->next;
	}
}
void Delete(LinkList *L, char input[])
{
	LinkList current = *L;
	LinkList previous = NULL;
	while(current != NULL && strcmp(input, current->ID))
	{
		previous = current;
		current = current->next;
	}
	if(current == NULL)
	{
		printf("δ�ҵ���ѧ��\n");
		return;
	}
	else
	{
		previous->next = current->next;
		free(current);
	}
}
void LinkSort(LinkList *L)
{
	LinkNode temp;
	LinkList pf = (*L)->next;
	LinkList pb;
	if(pf == NULL)
	{
		printf("��������������\n");
	}
	else if(pf->next == NULL)
	{
		printf("ֻ��һ��Ԫ�أ���������:\n");
	}
	else
	{
		while(pf != NULL)
		{
			pb = pf->next;
			while(pb != NULL)
			{
				if(pf->sum > pb->sum)
				{
					temp = *pb;
					*pb = *pf;
					*pf = temp;
					temp.next = pf->next;
					pf->next = pb->next;
					pb->next = temp.next;
				}
				pb = pb->next;
			}
			pf = pf->next;
		}
	}
}












