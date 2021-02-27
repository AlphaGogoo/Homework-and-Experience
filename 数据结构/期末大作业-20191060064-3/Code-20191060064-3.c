#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BitNode
{
	char data;
	struct BitNode *lchild;
	struct BitNode *rchild;
} BitNode;

BitNode *Creat_ProperBiTree(char *pre, char *post, int length, int *tag); //ǰ�����ת����
void InOrderTraverse(BitNode*T);

int main(void)
{
	int c;
	while(1)
	{
		printf("�뿪ʼѡ��0���������������1���˳�\n");
		scanf("%d", &c);
		fflush(stdin);
		switch(c)
		{
		case 0:
		{
			FILE *fp ;
			int tag = 0;//��Ǵ���0Ϊ�޴���
			if((fp = fopen("proper-bitree.txt", "a")) == NULL)
			{
				printf("���ļ�ʧ��\n");
				exit(EXIT_FAILURE);
			}
			system("cls");
			char pre[1024];
			char post[1024];
			//�ļ�д��ǰ������
			printf("������ǰ���������(��Ҫ�пո�)\n");
			gets(pre);
			fputs(pre, fp);
			fprintf(fp, "\n");
			//�ļ�д���������
			printf("����������������(��Ҫ�пո�)\n");
			gets(post);
			fputs(post, fp);
			fprintf(fp, "\n");
			fclose(fp);
			int prelength = strlen(pre);
			int postlength = strlen(post);
			if(prelength != postlength || prelength % 2 == 0 || postlength % 2 == 0)
			{
				tag = 1;//���Ȳ�����Ҫ�����ô���
			}
			//��ʼ�����������
			BitNode* T;
			T = Creat_ProperBiTree(pre, post, prelength, &tag);//tagָʾ�Ƿ����

			if(tag == 0)
			{
				InOrderTraverse(T);
				if((fp = fopen("proper-bitree.txt", "a")) == NULL)
				{
					printf("���ļ�ʧ��\n");
					exit(EXIT_FAILURE);
				}
				fprintf(fp, "\n");//��ĩ���ӻ���
				fclose(fp);
				printf("�����д���ļ�\n");
			}
			else
			{
				if((fp = fopen("proper-bitree.txt", "a")) == NULL)
				{
					printf("���ļ�ʧ��\n");
					exit(EXIT_FAILURE);
				}
				fprintf(fp, "�Բ�������������޷������������\n");
				fclose(fp);
				printf("�����д���ļ�\n");
			}
			system("pause");
		}
		break;
		case 1:
		{
			return 0;
			break;
		}
		default:
			printf("�����������������\n");
			break;
		}
	}
	return 0;
}


void InOrderTraverse(BitNode*T)
{
	if(T)
	{
		InOrderTraverse(T->lchild);
		//���ļ���д�������������
		FILE *fp1;
		if((fp1 = fopen("proper-bitree.txt", "a")) == NULL)
		{
			printf("���ļ�ʧ��\n");
			exit(EXIT_FAILURE);
		}
		fputc(T->data, fp1);
		fclose(fp1);
		InOrderTraverse(T->rchild);
	}
}

BitNode *Creat_ProperBiTree(char *pre, char *post, int length, int *tag) //ǰ�����ת����
{
	if(length == 1)//��һ���ڵ㣬��Ϊ��
	{
		BitNode* T = (BitNode*)malloc(sizeof(BitNode));
		if(pre[0] == post[0])//Ψһ�Ľڵ���ͬ
		{
			T->data = pre[0];
			T->lchild = NULL;
			T->rchild = NULL;
			return T;
		}
		else//Ψһ�Ľڵ㲻��ͬ���ش���
		{
			*tag = 1;
			return NULL;
		}
	}
	if(length % 2 == 0)//���г���Ϊż�����޷������������
	{
		*tag = 1;
		return NULL;
	}

	int i = 0;
	if(pre[0] != post[length - 1])//��ǰ��ͺ�������������ҵ��ĸ���һ��
	{
		*tag = 1;//���ô���
		return NULL;
	}

	char Root = pre[0];//��
	char rightRoot = post[length - 2]; //��������
	while(pre[i] != rightRoot && i < length)
	{
		i++;//��ǰ��������ҵ��������ĸ����Ӷ��ָ���������
	}
	if( i == length )
	{
		*tag = 1;//��ǰ������û�ҵ��������ĸ�������
		return NULL;
	}

	int leftlength = i - 1;//�������ڵ����
	int rightlength = length - i;//�������ڵ����

	BitNode * T = (BitNode*)malloc(sizeof(BitNode));
	T->data = Root;

	T->lchild = Creat_ProperBiTree(&pre[1], &post[0], leftlength,tag);
	T->rchild = Creat_ProperBiTree(&pre[i], &post[i - 1], rightlength,tag);
	return T;
}
