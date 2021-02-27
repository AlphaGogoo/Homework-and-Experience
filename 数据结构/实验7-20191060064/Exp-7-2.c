#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 256
#define TRUE 1
#define FALSE 0

typedef int Boolean;//��������
typedef char VerType;//��������
typedef int ElemType;//����Ԫ������
Boolean visited[MAXSIZE];//���ʱ�־����
int color[MAXSIZE];//Ϳɫ����ʼֵΪ0��1��2����ͬ��ɫ
typedef struct ArcNode
{
	int adjvex;//��β�±�
	struct ArcNode *next;
} ArcNode;
typedef struct
{
	VerType data;//����
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

void InitQueue(LinkQueue *Q);
void EnQueue(LinkQueue *Q, ElemType e);
void DeleteQueue(LinkQueue *Q, int *e);
int EmptyQueue(LinkQueue Q);
int LocateVex(ALGraph *G, VerType V);
void CreatALGraph(ALGraph *G);
int BFSTraverse(ALGraph G);

int main()
{
	int result;
	ALGraph G;
	CreatALGraph(&G);
	result = BFSTraverse(G);
	if( 1 == result)
	{
		printf("YES\n");
	}
	else
	{
		printf("NO\n");
	}
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

int LocateVex(ALGraph *G, VerType V)
{
	int i;
	for(i = 0; i < G->vexnum; i++)
	{
		if(V == G->vertices[i].data)
			break;
	}
	return i;
}
void CreatALGraph(ALGraph *G)//��������ͼ
{
	printf("�����붥�����\n");
	scanf("%d", &G->vexnum);
	printf("������ߵĸ���\n");
	scanf("%d", &G->arcnum);
	fflush(stdin);
	printf("����ÿ�����������\n");
	for(int i = 0; i < G->vexnum; i++)
	{
		scanf("%c", &G->vertices[i].data);
		G->vertices[i].FirstArc = NULL;
	}
	fflush(stdin);
	printf("���������\n");
	for(int k = 0; k < G->arcnum; k++)
	{
		char V1, V2;
		scanf("%c%c", &V1, &V2);
		fflush(stdin);
		int i = LocateVex(G, V1);
		int j = LocateVex(G, V2);
		ArcNode *e = (ArcNode*)malloc(sizeof(ArcNode));
		e->adjvex = j;
		e->next = G->vertices[i].FirstArc;
		G->vertices[i].FirstArc = e;
		
		ArcNode *t = (ArcNode*)malloc(sizeof(ArcNode));
		t->adjvex = i;
		t->next = G->vertices[j].FirstArc;
		G->vertices[j].FirstArc = t;
	}
}
int BFSTraverse(ALGraph G)//������ȱ���
{
	int i, j;
	ArcNode*p;
	LinkQueue Q;
	InitQueue(&Q);
	for(i = 0; i < G.vexnum; i++)
	{
		visited[i] = FALSE;
		color[i] = 0;
	}
	for(i = 0; i < G.vexnum; i++)
	{
		if(!visited[i])
		{
			color[i] = 1;//ͼ�ϵ�һ����ɫ
			visited[i] = TRUE;
			EnQueue(&Q, i);
			while( !EmptyQueue(Q) )
			{
				DeleteQueue(&Q, &j);
				p = G.vertices[j].FirstArc;
				while(p)
				{
					if (!visited[p->adjvex])//��δ�������ͽ���Ϳ�ϵڶ�����ɫ
					{
						color[p->adjvex] = 2;
						visited[p->adjvex] = TRUE;
						EnQueue(&Q, p->adjvex);
					}
					else//�ѱ������ͱȽ����뻡β�������ɫ
					{
						if( color[j] == color[p->adjvex] )//��һ�������޷�����Ҫ��
						{
							return 0;
						}
					}
					p = p->next;
				}
			}
		}
	}
	return 1;
}