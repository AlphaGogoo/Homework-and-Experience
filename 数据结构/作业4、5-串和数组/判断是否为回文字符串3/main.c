#include <stdio.h>
#include <stdlib.h>
typedef char ElemType;
typedef struct LNode
{
        ElemType data;
        struct LNode *next;
} LinkNode, *LinkList;
void InitList(LinkList *L, int n);
void OutPut(LinkList L);
void DisPlay(LinkList L);
LinkList Div_ReverseList(LinkList *L);
void Compare(LinkList former,LinkList latter);
int main()
{
        LinkList L = NULL;
        int n;
        printf("�����ַ�����\n");
        scanf("%d", &n);
        fflush(stdin);
        InitList(&L, n);
        LinkList former = Div_ReverseList(&L);
        LinkList latter = L;
        Compare(former,latter);
        return 0;
}
void InitList(LinkList *L, int n)
{
        printf("�����뺬%d���ַ����ַ���\n",n);
        char c;
        *L = (LinkList)malloc(sizeof(LinkNode));
        (*L)->next = NULL;
        scanf("%c", &c);
        (*L)->data = c;
        LinkList q  = *L;
        LinkList p;
        for(int i = 0; i < n - 1; i++)
        {
                p = (LinkList)malloc(sizeof(LinkNode));
                scanf("%c", &c);
                p->data = c;
                q->next = p;
                q = p;
        }
        p->next = NULL;
}
void DisPlay(LinkList L)
{
        LinkList p = L;
        while(p != NULL)
        {
                printf("%c", p->data);
                p = p->next;
        }
}
LinkList Div_ReverseList(LinkList *L)//��������תһ��ֳ������ȳ�����
{
        LinkList lslow = *L;//��ָ��
        LinkList lfast = (*L)->next;//��ָ��
        LinkList temp = NULL;
        if(lslow->next == NULL)
        {
                return lslow;
        }
        while(lslow->next != NULL&&lfast->next != NULL && lfast->next->next != NULL)
        {
                *L = lslow->next;
                lslow->next = temp;
                temp = lslow;
                lslow = *L;
                lfast = lfast->next->next;
        }
        if(lfast->next == NULL)
        {
                *L = lslow->next;
                lslow->next = temp;
                return lslow;
        }//��ʱ������ֳ�����lslow��*LΪͷ��������������
        else //(lfast->next->next == NULL)
        {
                LinkList t = (*L)->next;
                *L = lslow->next->next;
                lslow->next = temp;
                free(t);//���м�Ľڵ��ͷŵ�
                return lslow;
        }//��ʱ����ֳ�����temp��*LΪͷ������������
//        else//(lslow->next == NULL)
//        {
//                return lslow;
//        }
}
void Compare(LinkList former,LinkList latter)
{
        while(former != NULL)
        {
                if(former->data != latter->data)//����һ������ȣ��ͱز��ǻ��Ĵ�
                {
                        printf("No\n");
                        break;
                }
                former = former->next;
                latter = latter->next;
        }
        if(former == NULL)
        {
                printf("YES\n");
        }
}

