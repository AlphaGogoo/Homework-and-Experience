#include <stdio.h>
#include <stdlib.h>
/*
����һ��������������ɵ���������������������������������ȵ��������ڣ����Ա�д��ʵ�����й��ܵ��㷨 ����Ҫ�������ٵ�ʱ�����С�Ŀռ䣩
(1)ȷ���������б�������x������м�������ͬ����ֻ����һ�Σ�������{20,20,17,16,15,15,11,10,8,7,7,5,4}�� ��10�������5������
(2)�ڵ�������������xС�������ݼ��������У�
(3)����������x���ż���ӵ�������ɾ����
*/
typedef int ElemType;
typedef struct node
{
        ElemType data;
        struct node *next;
} Node, *LinkList;

int Count(LinkList L, int x);
void DisplayList(LinkList L);
void Reverse(LinkList *L, int x);
void Delete_Than(LinkList *L, int x);
int main()
{
        int input;
        LinkList L = NULL;
        LinkList node;
        printf("�밴��������һ�������м��Կո�������-1��β\n");
        scanf("%d", &input);
        while(1)
        {
                static LinkList tail;
                node = (LinkList)malloc(sizeof(Node));
                node ->data = input;
                if(L == NULL)
                {
                        L = node;
                        node->next  = NULL;
                }
                else
                {
                        tail->next = node;
                        node->next = NULL;
                }
                tail = node;
                scanf("%d", &input);
                if(input == -1)
                        break;
                while(input < tail->data)
                {
                        printf("������������������Ĳ���\n");
                        scanf("%d", &input);
                }
        }
        printf("���ڵ�����Ϊ\n");
        DisplayList(L);
        //��X��ĸ���
        int x;
        scanf("%d", &x);
        int a = Count(L, x);
        printf("��x�������%d��\n", a);
        Reverse(&L, x);
        printf("���ڵ�����Ϊ\n");
        DisplayList(L);
        Delete_Than(&L,x);
        printf("���ڵ�����Ϊ\n");
        DisplayList(L);
        return 0;
}
void DisplayList(LinkList L)
{
        LinkList node = L;
        while(node != NULL)
        {
                printf("%d ", node->data);
                node = node->next;
        }
        printf("\n");
}
void Reverse(LinkList *L, int x)
{
        LinkList r = *L;
        LinkList p = *L;
        LinkList q = NULL;
        while(p->data < x)
        {
                q = p;
                p = p->next;
        }
        if(p->data == x)
        {
                while(*L != q)
                {
                        *L = (*L)->next;
                        r->next = q->next;
                        q->next = r;
                        r = *L;
                }
        }
        else//p->data < x;
        {
                while(*L != p)
                {
                        *L = (*L)->next;
                        r ->next = p->next;
                        p->next = r;
                        r = *L;
                }
        }
}
int Count(LinkList L, int x)
{
        int  num =  0;
        int e;//ȡ����x�����
        LinkList p = L;
        while(p->data <= x)
        {
                p = p->next;
        }
        e = p->data;
        num++;
        p = p->next;
        while(p)
        {
                if(p->data > e)
                {
                        e = p->data;
                        num++;
                }
                p = p->next;
        }
        return num;
}

void Delete_Than(LinkList *L, int x)
{
        LinkList q = NULL;
        LinkList p = *L;
        while(p->data <= x)
        {
                q = p;
                p = p->next;
        }
        while(p)
        {
                if(p->data % 2 == 0)
                {
                        LinkList  temp = p;
                        q->next   =  p->next;
                        p = q->next;
                        free(temp);
                }
                else
                {
                        q = q->next;
                        p = p->next;
                }
        }
}














