#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef char ElemType;
typedef struct QNode
{
	ElemType date;
	struct QNode *next;
} QNode, *QueuePrt;
typedef struct
{
	QueuePrt front;//��ͷ
	QueuePrt rear;//��β
} LinkQueue;

void initQueue(LinkQueue *q)//��ʼ��һ���ն���
{
	q->front = q->rear = (QueuePrt)malloc(sizeof(QNode));
	if(!q->front)
	{
		exit(0);
	}
	else
	{
		q->front->next = NULL;
	}
}

void InsertQueue(LinkQueue *q, ElemType e)//����в���
{
	QueuePrt p;
	p = (QueuePrt)malloc(sizeof(QNode));
	if(p == NULL)
	{
		exit(0);
	}
	p->date = e;
	p->next = NULL;
	q->rear ->next = p;
	q->rear = p;
}

void DeleteQueue(LinkQueue *q, ElemType *e)//�����в���
{
	QueuePrt p;
	if(q->front == q->rear)
	{
		return ;
	}
	p = q->front->next;
	*e = p->date;
	q->front->next = p->next;
	if(q->rear == p)
	{
		q->rear = q->front;
	}
	free(p);
}


int main()
{
	char c;
	LinkQueue Q;
	initQueue(&Q);
	printf("�������ַ�������#����:\n");

	scanf("%c", &c);
	while(c != '#')
	{
		InsertQueue(&Q, c);//�����
		scanf("%c", &c);
	}
	printf("�����н��Ϊ\n");
	while(Q.front != Q.rear)
	{
		DeleteQueue(&Q, &c);//������

		printf("%c", c);
	}
	return 0;
}
