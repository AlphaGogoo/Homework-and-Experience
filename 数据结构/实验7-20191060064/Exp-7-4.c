#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1024
#define TRUE 1
#define FALSE 0
#define INFINITY 100000000
typedef int Boolean;//��������
typedef int VerType;//��������
typedef int ElemType;
Boolean visited[MAXSIZE];//���ʱ�־����
typedef struct ArcNode
{
	int adjvex;//��β�±�
	int weight;//Ȩ��
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

void CreatALGraph(ALGraph *G);//��������ͼ
int getweight(ALGraph G, int start, int end);//��ȡ�ߵ�Ȩֵ
int MiniSpanTree_Prim(ALGraph G);//����С������
void DFS(ALGraph G, int i);//��ȱ���
void DFSTraverse(ALGraph G);
int main()
{
	ALGraph G;
	CreatALGraph(&G);
	DFSTraverse(G);
	for( int i = 0; i < G.vexnum; i++ )//�������ж��Ƿ�Ϊ��ͨͼ
	{
		if( visited[i] != TRUE )
		{
			printf("-1");
			return 0;
		}
	}
	int MiniCost = MiniSpanTree_Prim(G);//������С������������С����
	printf("%d",MiniCost);
	return 0;
}

void CreatALGraph(ALGraph *G)//����������
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
		int w;
		scanf("%d %d %d", &V1, &V2, &w);
		getchar();
		ArcNode *e = (ArcNode*)malloc(sizeof(ArcNode));
		e->adjvex = V2-1;
		e->weight = w;
		e->next = G->vertices[V1-1].FirstArc;
		G->vertices[V1-1].FirstArc = e;

		ArcNode *t = (ArcNode*)malloc(sizeof(ArcNode));
		t->adjvex = V1-1;
		t->weight = w;
		t->next = G->vertices[V2-1].FirstArc;
		G->vertices[V2-1].FirstArc = t;
	}
}

int getweight(ALGraph G, int start, int end)//��ȡ�ߵ�Ȩֵ
{
	ArcNode *p;
	p = G.vertices[start].FirstArc;
	if(start == end)
	{
		return 0;
	}
	else
	{
		while(p)
		{
			if(end == p->adjvex)
			{
				return p->weight;
			}
			p = p->next;
		}
		return INFINITY;
	}
}
int MiniSpanTree_Prim(ALGraph G)////��С������prim�㷨
{
	int min, i, j, k;
	int weight;
	int adjvex[MAXSIZE];
	int lowcost[MAXSIZE];
	int MiniCost = 0;
	lowcost[0] = 0;
	adjvex[0] = 0;
	//��ʼ������
	for(int i = 0; i < G.vexnum; i++)
	{
		lowcost[i] = getweight(G, 0, i);
		adjvex[i] = 0;
	}
	//������С������
	for(i = 1; i < G.vexnum; i++)
	{
		min = INFINITY;
		j = 1;
		k = 0;
		//����ȫ������
		while(j < G.vexnum)
		{
			if(lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;
			}
			j++;
		}
		MiniCost += min;
		lowcost[k] = 0;
		for(j = 1; j < G.vexnum; j++)
		{
			weight = getweight(G, k, j);
			if(lowcost[j] != 0 && weight < lowcost[j])
			{
				lowcost[j] = weight;
				adjvex[j] = k;
			}
		}
	}
	return MiniCost;
}

void DFS(ALGraph G, int i)//��ȱ���
{
	ArcNode *p;
	visited[i] = TRUE;
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

void DFSTraverse(ALGraph G)//��ȱ���
{
	for(int i = 0; i < G.vexnum; i++)
	{
		visited[i] = FALSE;
	}
	DFS(G, 0);
}
