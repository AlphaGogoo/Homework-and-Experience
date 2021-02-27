#include <stdio.h>
#include <stdlib.h>
typedef char ElemType;
typedef struct BiTNode
{
	ElemType data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
typedef struct QNode
{
	BiTNode  node;
	struct QNode *next;
} QNode, *QueuePtr;
typedef struct
{
	QueuePtr front;
	QueuePtr rear;
} LinkQueue;

void InitQueue(LinkQueue *Q)//��ʼ��һ���ն���
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if(!Q->front)
	{
		exit(0);
	}
	else
	{
		Q->front->next = NULL;
	}
}

void InsertQueue(LinkQueue *q, BiTNode e)//����в���
{
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if(p == NULL)
	{
		exit(0);
	}
	p->node = e;
	p->next = NULL;
	q->rear ->next = p;
	q->rear = p;
}

void DeleteQueue(LinkQueue *q, BiTNode *e)//�����в���
{
	QueuePtr p;
	if(q->front == q->rear)
	{
		return ;
	}
	p = q->front->next;
	*e = p->node;
	q->front->next = p->next;
	if(q->rear == p)
	{
		q->rear = q->front;
	}
	free(p);
}
int EmptyQueue(LinkQueue Q)
{
	return (Q.front == Q.rear ? 0 :  1);
}
visit(char c)
{
	printf("%c", c); 
}

void LevelOrderTraverse(BiTree T)
{
	LinkQueue Q; //�������
	InitQueue(&Q); //��ʼ������
	BiTNode BT;
	if(T)
	{
		InsertQueue(&Q, *T); //���ڵ�ָ�������
	}
	while(EmptyQueue(Q)) //���в���ʱ
	{
		DeleteQueue(&Q, &BT); //������
		visit(BT.data);//����ýڵ��ֵ
		if(BT.lchild != NULL)
		{
			InsertQueue(&Q, *BT.lchild); //�����ӾͰ����������
		}
		if(BT.rchild != NULL)
		{
			InsertQueue(&Q, *BT.rchild); //���Һ��ӾͰ��Һ��������
		}
	}
}
void CreateBiTree(BiTree *T)
{
	char c;
	scanf("%c", &c);
	if(' ' == c)
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTNode *)malloc(sizeof(BiTNode));
		(*T)->data = c;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
}
int main()
{
	BiTree T;
	CreateBiTree(&T);
	LevelOrderTraverse(T);
}
