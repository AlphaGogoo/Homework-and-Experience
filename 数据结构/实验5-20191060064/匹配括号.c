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
int IsMatch(char input[],sqStack*S);
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

int StackLen(sqStack s)//����ջ�ĳ���
{
	return (s.top - s.base);
}
int main()
{
	sqStack S;
	initStack(&S);
	char input[100];

	printf("�����ַ���\n");
	scanf("%s",input);
	int tag = IsMatch(input,&S);
	if ( 0 == tag )
		printf("ƥ��ʧ��\n");
	else if( 1 == tag )
		printf("ƥ��ɹ�\n");
	else
		printf("δ�ҵ�����\n");
	return 0;
}

int IsMatch(char input[],sqStack*S)
{
	char c , e ;
	int change = 0;
	for(int i = 0 ; (c = input[i]) != '\0' ; i++)//ÿ�ζ�ȡһ���ַ�
	{
		if(c == '(' || c == '[' || c == '{')//����������ţ�����ջ
		{
			change = 1;
			Push(S, c);
		}
		else if(')' == c)//����С�����ţ����ջ
		{
			change = 1;
			Pop(S, &e);
			if(e != '(')//��δ�ҵ�С������
				return 0;
		}
		else if(']' == c)//�����������ţ����ջ
		{
			change = 1;
			Pop(S, &e);
			if(e != '[')//��δ�ҵ���������
				return 0;
		}
		else if( '}' == c)//���Ǵ������ţ����ջֱ���ҵ���������
		{
			change = 1;
			Pop(S, &e);
			if(e !='{' )//��ջΪ��ʱ��δ�ҵ��������ţ���ض��޷�ƥ��
				return 0;
		}
		else//���������ţ�������������֤ջ��ֻ��������
			continue;
	}
	if(change == 0)//ʽ����û������
		return 2;
	if(StackLen(*S) != 0)//ջ�ڲ��գ���ض�ջ�����������޷�ƥ�䡣
	{
		return 0;
	}
	return 1;
}




















