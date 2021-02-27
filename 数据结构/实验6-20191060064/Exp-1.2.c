#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tag = 0;//ȫ�ֱ���,ָʾ�Ƿ��ǳɹ����������
typedef struct BitNode
{
	char data;
	struct BitNode *lchild;
	struct BitNode *rchild;
} BitNode;

BitNode *CreateBiTree_Post(char *prestr, char *instr, int length); //ǰ������ԭ������
void PostOrderTraverse(BitNode*T);//�������ʱ
void PreOrderTraverse(BitNode*T);//ǰ�����
void InOrderTraverse(BitNode*T);//�������

int Tree_Depth(BitNode *T);//�������
int LeaveCounts(BitNode *T);//Ҷ����


int main(void)
{
	while(1)
	{
		tag = 0;//��������־��0;
		printf("------��ʼ-------\n");
		char prestr[100];
		char instr[100];
		printf("������ǰ���������");
		scanf("%s", prestr);
		printf("�����������������");
		scanf("%s", instr);
		int lengthpre = strlen(prestr);
		int lengthin = strlen(instr);
		fflush(stdin);
		if(lengthpre != lengthin)//ǰ�����к��������в�һ����
		{
			printf("�������\n");
			continue;
		}
		BitNode* T;
		T = CreateBiTree_Post(prestr, instr, lengthpre);
		if(1 == tag)//�������д���
		{
			printf("�������\n");
			continue;
		}
		else
		{
			printf("��������Ϊ\n");
			PostOrderTraverse(T);
			printf("\n");
		}
		printf("���������Ϊ%d\n", Tree_Depth(T));
		printf("Ҷ������%d��\n", LeaveCounts(T));
	}
	return 0;
}
BitNode *CreateBiTree_Post(char *prestr, char *instr, int length) //ǰ������ԭ
{
	if(length == 0)//�������г���Ϊ0,����
	{
		return NULL;
	}
	int i = 0;
	char c = prestr[0];//�ҵ���
	while(instr[i] != c && i < length)
	{
		i++;
	}
	if(i == length)//δ�������������ҵ���
	{
		tag = 1;//���ô���ָʾ��
		return NULL;
	}
	int leftlength = i;
	int rightlength = length - i - 1;
	BitNode*T = (BitNode*)malloc(sizeof(BitNode));
	T->data = c;
	T->lchild = CreateBiTree_Post(&prestr[1], &instr[0], leftlength);//�ݹ鹹��������
	T->rchild = CreateBiTree_Post(&prestr[i + 1], &instr[i + 1], rightlength);//�ݹ鹹��������
	return T;
}

void PostOrderTraverse(BitNode*T)
{
	if(T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c ", T->data);
	}
}
void PreOrderTraverse(BitNode*T)
{
	if(T)
	{
		printf("%c ", T->data);
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
	}
}
void InOrderTraverse(BitNode*T)
{
	if(T)
	{
		PostOrderTraverse(T->lchild);
		printf("%c ", T->data);
		PostOrderTraverse(T->rchild);
	}
}

int Tree_Depth(BitNode *T)
{
	int LDepth;
	int RDepth;
	if(T)
	{
		LDepth = Tree_Depth(T->lchild);
		RDepth = Tree_Depth(T->rchild);
		return (LDepth > RDepth ? LDepth + 1 : RDepth + 1);
	}
	else
	{
		return 0;
	}
}

int LeaveCounts(BitNode *T)
{
	if(T == NULL)
		return 0;
	else if(T->lchild == NULL && T->rchild == NULL)
	{
		return 1;
	}
	return (LeaveCounts(T->lchild) + LeaveCounts(T->rchild));
}

