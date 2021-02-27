#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef char ElemType;
typedef struct strStack
{
        ElemType *base;
        ElemType *top;
        int StackSize;
} sqStack;//����һ��ջ
struct strQueue
{
        ElemType e;
        struct strQueue *next;
};
typedef struct Queue
{
        struct strQueue *front;
        struct strQueue *rear;
} Queue;//����һ������

void InitStack(sqStack *S);//��ʼ��ջ
void Push_Stack(sqStack *S, ElemType e);//��ջ
void Pop(sqStack *S, ElemType *e);//��ջ
void InitQueue(Queue *Q);//��ʼ������
void InserQueue(Queue *Q, ElemType e);//�����
void DeleteQueue(Queue *Q, ElemType *e);//������
int StackLen(sqStack S);//��ջ�ĳ���
int main()
{
        sqStack S;
        Queue Q;
        InitStack(&S);
        InitQueue(&Q);//��ʼ��ջ�Ͷ���
        char ch;
        int len;//ջ�ĳ���
        int flag = 1;
	/*������Ԫ����ջ�������*/
        while((ch = getchar()) != '\n')
        {
                Push_Stack(&S, ch);
                InserQueue(&Q, ch);
        }
        len = StackLen(S);//ջ�ĳ���
        for(int i = 0; i < len; i++)
        {
                char elem_stack, elem_Queue;
                Pop(&S, &elem_stack);
                DeleteQueue(&Q, &elem_Queue);
                /*���γ�ջ��������*/
                /*��ȡ����Ԫ�ز�һ��ʱ�����Ѿ����ǻ��Ĵ�������ѭ��*/
                if(elem_stack != elem_Queue)
                {
                        flag = 0;
                        break;
                }

        }
        if(flag == 0)
        {
                printf("���ǻ��Ĵ�\n");
        }
        else
        {
                printf("�ǻ��Ĵ�\n");
        }
        return 0;
}
void InitStack(sqStack *S)//��ʼ��ջ
{
        S->base  = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(ElemType));
        if(S->base == NULL)
        {
                exit(-1);
        }
        S->top = S->base;
        S->StackSize = STACKINCREMENT;
}

void Push_Stack(sqStack *S, ElemType e)//��ջ
{
        if(S->top - S->base == S->StackSize)
        {
                S->base = (ElemType*)realloc(S->base, (STACKINCREMENT + S->StackSize) * sizeof(ElemType));
                if(S->base == NULL)
                {
                        exit(-1);
                }
        }
        *(S->top) = e;
        S->top ++;
}

void Pop(sqStack *S, ElemType *e)//��ջ
{
        if(S -> top == S->base)
        {
                return ;
        }
        *e = *--(S->top);
}

void InitQueue(Queue *Q)//��ʼ������
{
        Q->front  = Q->rear = (struct strQueue*)malloc(sizeof(struct strQueue));
        if(!Q->front)
        {
                exit(0);
        }
        else
        {
                Q->front->next = NULL;
        }
}

void InserQueue(Queue *Q, ElemType e)//�����
{
        struct strQueue *q = (struct strQueue*)malloc(sizeof(struct strQueue));
        if(!q)
        {
                exit(-1);
        }
        else
        {
                q->e = e;
                q->next = NULL;
                Q->rear->next = q;
                Q->rear = q;
        }
}

void DeleteQueue(Queue *Q, ElemType *e)//������
{
        if(Q->front == Q->rear)
        {
                return ;
        }
        else
        {
                struct strQueue *q = Q->front->next;
                *e = q->e;
                Q->front->next = q->next;
                if(Q->rear == q)
                {
                        Q->rear = Q->front;
                }
                free(q);
        }
}
int StackLen(sqStack S)//��ջ�ĳ���
{
        return (S.top  -  S.base);
}
