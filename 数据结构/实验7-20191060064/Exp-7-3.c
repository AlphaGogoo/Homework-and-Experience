#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 256
#define TRUE 1
#define FALSE 0

typedef int Boolean;//��������
typedef int VerType;//��������
typedef int ElemType;
Boolean visited[MAXSIZE];//���ʱ�־����
typedef struct ArcNode
{
	int adjvex;//��β�±�
	struct ArcNode *next;
} ArcNode;
typedef struct
{
	//VerType data;//����
	ArcNode *FirstArc;//��һ����
} VNode, AdjList[MAXSIZE]; //�ڽӱ�
typedef struct
{
	int vexnum;//������
	int arcnum;//����
	AdjList vertices;//�ڽӱ�����
} ALGraph;

typedef struct QNode
{
	ElemType data;
	struct QNode *next;
} QNode, *QueuePtr;
typedef struct
{
	QueuePtr front;
	QueuePtr rear;
} LinkQueue; //����

void InitQueue(LinkQueue *Q);//��ʼ������
void EnQueue(LinkQueue *Q, ElemType e);//�����
void DeleteQueue(LinkQueue *Q, int *e);//������
int EmptyQueue(LinkQueue Q);//�ж϶����Ƿ�Ϊ��

void CreatALGraph(ALGraph *G);//��������ͼ
int path_BFSTraverse(ALGraph G,int i, int j);//�ж��Ƿ���·��


int main()
{
	int i ,j;
	ALGraph G;
	CreatALGraph(&G);
	scanf("%d %d",&i,&j);
	int result =path_BFSTraverse(G, i, j) ;
	if( 1 == result )
		printf("There is a path between %d and %d.",i,j);
	else
		printf("There is no path between %d and %d.",i,j);
	return 0;
}

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
void EnQueue(LinkQueue *Q, ElemType e)//����в���
{
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if(p == NULL)
	{
		exit(0);
	}
	p->data = e;
	p->next = NULL;
	Q->rear ->next = p;
	Q->rear = p;
}
void DeleteQueue(LinkQueue *Q, int *e)//�����в���
{
	QueuePtr p;
	if(Q->front == Q->rear)
	{
		return ;
	}
	p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	if(Q->rear == p)
	{
		Q->rear = Q->front;
	}
	free(p);
}

int EmptyQueue(LinkQueue Q)
{
	return (Q.front == Q.rear ? 1 : 0);
}

void CreatALGraph(ALGraph *G)//��������ͼ
{
	scanf("%d %d", &G->vexnum,&G->arcnum);//���붥�����ͱ���
	getchar();
	for(int i = 0; i < G->vexnum; i++)
	{
		G->vertices[i].FirstArc = NULL;
	}
	for( int k = 0; k < G->arcnum; k++ )
	{
		int V1, V2;
		scanf("%d %d", &V1, &V2);
		getchar();
		ArcNode *e = (ArcNode*)malloc(sizeof(ArcNode));
		e->adjvex = V2;
		e->next = G->vertices[V1].FirstArc;
		G->vertices[V1].FirstArc = e;

		ArcNode *t = (ArcNode*)malloc(sizeof(ArcNode));
		t->adjvex = V1;
		t->next = G->vertices[V2].FirstArc;
		G->vertices[V2].FirstArc = t;
	}
}

int path_BFSTraverse(ALGraph G,int i, int j)//������ȱ���
{
	if(i == j)//����β�ͻ�ͷ��ͬ��ֱ�ӷ���1
	{
		return 1;
	}
	int s;
	ArcNode*p;
	LinkQueue Q;
	InitQueue(&Q);
	for(int k = 0; k < G.vexnum; k++)
	{
		visited[k] = FALSE;
	}
	visited[i] = TRUE;//��i��ʼ����
	EnQueue(&Q, i);
	while( !EmptyQueue(Q) )
	{
		DeleteQueue(&Q, &s);
		p = G.vertices[s].FirstArc;
		while(p)
		{
			if( !visited[p->adjvex] )
			{
				if( p->adjvex == j )//��������j
				{
					return 1;
				}
				visited[p->adjvex] = TRUE;
				EnQueue(&Q, p->adjvex);
			}
			p = p->next;
		}
	}
	return 0;
}
