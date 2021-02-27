#include <stdio.h>
#include <stdlib.h>
typedef struct BiTNode
{
	int data;
	struct BiTNode *llink, *rlink;
} BiTNode, *BiTree;

void CreateBiTree(BiTree *T);
int IsBST(BiTree T);
int main()
{
	BiTree T;
	printf("CreatNewTree:\n");
	CreateBiTree(&T);
	int a = IsBST(T);
	if (a == 0)
	{
		printf("NO");
	}
	else
	{
		printf("YES");
	}
}
//����һ������ǰ���������
void CreateBiTree(BiTree *T)
{
	int c;
	scanf("%d", &c);
	if (0 == c)
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTNode *)malloc(sizeof(BiTNode));
		(*T)->data = c;
		CreateBiTree(&(*T)->llink);
		CreateBiTree(&(*T)->rlink);
	}
}
int IsBST(BiTree T)
{
	int left;
	int right;

	if (T->llink == NULL && T->rlink != NULL)//�������գ��������ǿ�
	{
		if (T->data < T->rlink->data)
		{
			right = IsBST(T->rlink);
			return (1 && right);
		}
		else
			return 0;
	}
	else if (T->llink != NULL && T->rlink == NULL)//�������ǿգ���������
	{
		if (T->data > T->llink->data)
		{
			left = IsBST(T->llink);
			return (1 && left);
		}
		else
			return 0;
	}
	else if (T->llink != NULL && T->rlink != NULL)//�������ǿգ��������ǿ�
	{
		if (T->data > T->llink->data && T->data < T->rlink->data)
		{
			right = IsBST(T->rlink);
			left = IsBST(T->llink);
			return (1 && right && left);
		}
		else
			return 0;
	}
	else//����������Ϊ�գ�ֻ��һ����
		return 1;
}
