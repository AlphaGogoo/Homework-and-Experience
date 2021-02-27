#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 256
#define TRUE 1
#define FALSE 0
typedef int Boolean;//��������
typedef char VerType;//��������
typedef int ElemType;
Boolean visited[MAXSIZE];//���ʱ�־����
typedef enum {DG,DN,UDG,UDN} GraphKind ;//ͼ�����ͣ�����ͼ��������������ͼ��������
typedef struct ArcNode
{
	int adjvex;//��β�±�
	int weight;//Ȩ��
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
	GraphKind kind;//ͼ������
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
void EnQueue(LinkQueue *Q, ElemType e);//����в���
void DeleteQueue(LinkQueue *Q, int *e);//�����в���
int EmptyQueue(LinkQueue Q);//�����Ƿ�Ϊ��

int LocateVex(ALGraph *G, VerType V);//�ҵ�����λ��
void CreatALGraph(ALGraph *G, GraphKind  a);//����ĳ�����͵�ͼ
void CreatALGraph_UDN(ALGraph *G);//����������
void CreatALGraph_UDG(ALGraph *G);//��������ͼ
void CreatALGraph_DN(ALGraph *G);//����������
void CreatALGraph_DG(ALGraph *G);//��������ͼ

void DFS(ALGraph G, int i);//������ȱ���
void DFSTraverse(ALGraph G);
void BFSTraverse(ALGraph G);//������ȱ���


int main()
{
	ALGraph G;
	int a;
	printf("���봴����ͼ������,����ͼΪ0��������Ϊ1������ͼΪ2��������Ϊ3\n");
	scanf("%d",&a);
	CreatALGraph(&G, (GraphKind) a);
	printf("��ȱ������Ϊ:\n");
	BFSTraverse(G);
	printf("��ȱ������Ϊ:\n");
	DFSTraverse(G);
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
void CreatALGraph_UDN(ALGraph *G)//����������
{
	G->kind = UDN;
	printf("�����붥�����\n");
	scanf("%d", &G->vexnum);
	printf("������ߵĸ���\n");
	scanf("%d", &G->arcnum);
	fflush(stdin);
	printf("���붥��\n");
	for(int i = 0; i < G->vexnum; i++)
	{
		scanf("%c", &G->vertices[i].data);
		G->vertices[i].FirstArc = NULL;
	}
	fflush(stdin);
	printf("���뻡β��ͷ��Ȩ��\n");
	for(int k = 0; k < G->arcnum; k++)
	{
		char V1, V2;
		int w;
		scanf("%c%c%d", &V1, &V2, &w);
		fflush(stdin);
		int i = LocateVex(G, V1);
		int j = LocateVex(G, V2);
		ArcNode *e = (ArcNode*)malloc(sizeof(ArcNode));
		e->weight = w;
		e->adjvex = j;
		e->next = G->vertices[i].FirstArc;
		G->vertices[i].FirstArc = e;
		ArcNode *t = (ArcNode*)malloc(sizeof(ArcNode));
		t->weight = w;
		t->adjvex = i;
		t->next = G->vertices[j].FirstArc;
		G->vertices[j].FirstArc = t;
	}
}

void CreatALGraph_UDG(ALGraph *G)//��������ͼ
{
	G->kind = UDG;
	printf("�����붥�����\n");
	scanf("%d", &G->vexnum);
	printf("������ߵĸ���\n");
	scanf("%d", &G->arcnum);
	fflush(stdin);
	printf("���붥��\n");
	for(int i = 0; i < G->vexnum; i++)
	{
		scanf("%c", &G->vertices[i].data);
		G->vertices[i].FirstArc = NULL;
	}
	fflush(stdin);
	printf("���뻡β��ͷ\n");
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
void CreatALGraph_DN(ALGraph *G)//����������
{
	G->kind = DN;
	printf("�����붥�����\n");
	scanf("%d", &G->vexnum);
	printf("������ߵĸ���\n");
	scanf("%d", &G->arcnum);
	fflush(stdin);
	printf("���붥��\n");
	for(int i = 0; i < G->vexnum; i++)
	{
		scanf("%c", &G->vertices[i].data);
		G->vertices[i].FirstArc = NULL;
	}
	fflush(stdin);
	printf("���뻡β��ͷ��Ȩ��\n");
	for(int k = 0; k < G->arcnum; k++)
	{
		char V1, V2;
		int w;
		scanf("%c%c%d", &V1, &V2,&w);
		fflush(stdin);
		int i = LocateVex(G, V1);
		int j = LocateVex(G, V2);

		ArcNode *e = (ArcNode*)malloc(sizeof(ArcNode));
		e->adjvex = j;
		e->weight = w;
		e->next = G->vertices[i].FirstArc;
		G->vertices[i].FirstArc = e;
	}
}

void CreatALGraph_DG(ALGraph *G)//��������ͼ
{
	G->kind = DG;
	printf("�����붥�����\n");
	scanf("%d", &G->vexnum);
	printf("������ߵĸ���\n");
	scanf("%d", &G->arcnum);
	fflush(stdin);
	printf("���붥��\n");
	for(int i = 0; i < G->vexnum; i++)
	{
		scanf("%c", &G->vertices[i].data);
		G->vertices[i].FirstArc = NULL;
	}
	fflush(stdin);
	printf("���뻡β��ͷ\n");
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
	}
}

void CreatALGraph(ALGraph *G, GraphKind  a)
{
	switch(a)
	{
	case DG:
		CreatALGraph_DG(G);
		break;
	case UDG:
		CreatALGraph_UDG(G);
		break;
	case DN:
		CreatALGraph_DN(G);
		break;
	case UDN:
		CreatALGraph_UDN(G);
		break;
	default:
		break;
	}
}

//������ȱ���
void DFS(ALGraph G, int i)
{
	ArcNode *p;
	visited[i] = TRUE;
	printf("%c ", G.vertices[i].data);
	p = G.vertices[i].FirstArc;
	while(p)
	{
		if(visited[p->adjvex] != TRUE)
		{
			DFS(G, p->adjvex);
		}
		p = p->next;
	}
}

void DFSTraverse(ALGraph G)
{
	for(int i = 0; i < G.vexnum; i++)
	{
		visited[i] = FALSE;
	}
	for(int i = 0; i < G.vexnum; i++)
	{
		if(!visited[i])
		{
			DFS(G, i);
		}
	}
}


void BFSTraverse(ALGraph G)//������ȱ���
{
	int i, j;
	ArcNode*p;
	LinkQueue Q;
	InitQueue(&Q);
	for(i = 0; i < G.vexnum; i++)
	{
		visited[i] = FALSE;
	}
	for(i = 0; i < G.vexnum; i++)
	{
		if(!visited[i])
		{
			printf("%c ", G.vertices[i].data);
			visited[i] = TRUE;
			EnQueue(&Q, i);
			while(!EmptyQueue(Q))
			{
				DeleteQueue(&Q, &j);
				p = G.vertices[j].FirstArc;
				while(p)
				{
					if(!visited[p->adjvex])
					{
						printf("%c ", G.vertices[p->adjvex].data);
						visited[p->adjvex] = TRUE;
						EnQueue(&Q, p->adjvex);
					}
					p = p->next;
				}
			}
		}
	}
}
