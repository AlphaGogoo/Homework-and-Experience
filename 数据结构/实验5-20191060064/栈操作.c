#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef char ElemType;
typedef struct
{
	ElemType *base;//ջ��
	ElemType *top;//ջ��
	int stackSize; //ջ�ĵ�ǰ��ʹ�õ��������
} sqStack;

void initStack(sqStack *s)//��ʼ����ջ
{
	s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if(!s->base)
	{
		exit(0);
	}
	else
	{
		s->top = s->base;//�ʼ��ջ������ջ��
		s->stackSize = STACK_INIT_SIZE;
	}
}

void Push(sqStack *s, ElemType e)//��ջ
{
	//���ջ����׷�ӿռ�
	if(s->top - s->base >= s->stackSize)
	{
		s->base = (ElemType *)realloc(s->base, (s->stackSize + STACK_INIT_SIZE) * sizeof(ElemType));
		if(!s->base)
		{
			exit(0);
		}
		else
		{
			s->top = s->base + s->stackSize;//����ջ��
			s->stackSize = s->stackSize + STACKINCREMENT;
		}
	}
	*(s->top) = e;
	s->top++;
}

void Pop(sqStack *s, ElemType *e)//��ջ����
{
	if(s -> top == s->base)
	{
		return ;
	}
	else
	{
		*e = *--(s->top);
	}
}
int main()
{
	char e,c;
	sqStack S;
	initStack(&S);
	char input[100];
	printf("����һ���ַ�\n");
	scanf("%s",input);
	for(int i = 0; ( c = input[i] ) != '\0' ; i++)
	{
		Push(&S,c);
	}
	printf("���ڿ�ʼ��ջ\n");
	for(int i=0; ( c = input[i] ) != '\0' ; i++)
	{
		Pop(&S,&e);
		printf("%c",e);
	}
	return 0;
}
