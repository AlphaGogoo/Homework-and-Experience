#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef struct LinkNode
{
	ElemType data;
	struct LinkNode* next;
} LinkNode, *LinkList;

int  Compare(int, int);
void OrderInsert(LinkList L, int e, int(*compare)(int, int));//���뺯��
void OrderInput(LinkList L, int(*compare)(int, int));//���������
void OrderMerge(LinkList La, LinkList Lb, LinkList Lc, int(*compare)(int ,int ));//�ϲ������
void DisPlay(LinkList L);//��ӡ�������Ϣ

int main()
{
	int (*compare)(int, int);
	compare =  Compare;//������ָ�븳ֵ

	LinkList La,Lb,Lc;
	La = (LinkList)malloc(sizeof(LinkNode));//�����La
	La->next = NULL;
	Lb = (LinkList)malloc(sizeof(LinkNode));//�����Lb
	Lb->next = NULL;
	Lc = (LinkList)malloc(sizeof(LinkNode));//�����Lc
	Lc->next = NULL;
	printf("��ʼ��La\n");
	OrderInput(La,compare);
	printf("�����La����������");
	DisPlay(La);
	printf("��ʼ��Lb\n");
	OrderInput(Lb,compare);
	printf("�����Lb����������");
	DisPlay(Lb);
	printf("�ϲ�ΪLc\n");
	OrderMerge(La,Lb,Lc,compare);
	printf("�����Lc����������");
	DisPlay(Lc);
	return 0;
}
int Compare(int a, int b)
{
	return(a>=b ? 1 : 0);//ǰ�ߴ��ڵ��ں��ߣ�����1�����򷵻�0
}
void OrderInsert(LinkList L, int e, int(*compare)(int, int))
{
	LinkList q = L->next;//qΪ��һ����ֵ�Ľڵ�
	LinkList pre = L;//preָ��q��ǰһ��Ԫ��
	if(L->next  == NULL)//�������Ϊ��
	{
		LinkList p = (LinkList)malloc(sizeof(LinkNode));
		p->data = e;
		p->next = NULL;
		L->next = p;
	}
	else//����ǿ�
	{
		while(q != NULL && compare(e, q->data))//�ҵ�e��data��С�Ľڵ�
		{
			pre = q;
			q = q->next;
		}//��ʱԪ��eӦ�ò��뵽pre��q֮��Ľڵ�
		LinkList p = (LinkList)malloc(sizeof(LinkNode));
		p->data = e;
		p->next = q;
		pre->next = p;
	}
}

void OrderInput(LinkList L, int(*compare)(int, int))//����n��Ԫ�ص������
{
	int e;
	printf("������һ�����֣��м��Կո���������-1����\n");
	scanf("%d", &e);
	while(e != -1)
	{
		OrderInsert(L, e, compare);
		scanf("%d", &e);
	}
}
void OrderMerge(LinkList La, LinkList Lb, LinkList Lc, int(*compare)(int ,int ))//�ϲ�����
{
	LinkList la = La->next;
	LinkList lb = Lb->next;
	LinkList lc = Lc;
	while(la != NULL && lb != NULL)
	{
		if(compare(la->data,lb->data))//���ǰ�ߴ��ں���
		{
			OrderInsert(Lc,lb->data,compare);//�Ѻ��߲��뵽���������
			lb = lb->next;
		}
		else
		{
			OrderInsert(Lc,la->data,compare);//��ǰ�߲��뵽���������
			la = la->next;
		}
		lc = lc->next;
	}
	while(la != NULL)//��ĳ��������Ԫ��δ����Lc�У����ʣ�µ�����Ԫ�ز��뵽Lc��
	{
		OrderInsert(Lc,la->data,compare);
		la = la->next;
	}
	while(lb != NULL)
	{
		OrderInsert(Lc,lb->data,compare);
		lb = lb->next;
	}
}
void DisPlay(LinkList L)//��ӡ�������Ϣ
{
	LinkList p = L->next;
	while(p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
