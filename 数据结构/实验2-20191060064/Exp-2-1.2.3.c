#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
        char id[20];
        double Chinese;
        double Math;
        double English;
        double sum;//�ܷ�
        double weight_average;//��Ȩƽ����
} ElemType;

typedef struct
{
        ElemType *num;
        int length;//���Ա�ǰ����
        int listsize;
} Sqlist;

void InitList(Sqlist *L, int n);//��ʼ��˳���
void ListInsert(Sqlist *L, int k);//����Ԫ��
void DeleteList(Sqlist *L, char input[]);//��ѧ��ɾ��Ԫ��
void SortList(Sqlist *L);//���ܷ���������
void DisplayList(Sqlist L);//��ӡ����ѧ������Ϣ
void GetInput(Sqlist *L, int n);

int main()
{
        int n, k;
        char input[20];
        printf("������ѧ��������\n");
        scanf("%d", &n);
        Sqlist L;//����һ��˳���
        InitList(&L, n);//��ʼ��N��ѧ����Ϣ
        printf("���ڵ�ѧ����ϢΪ\n");
        DisplayList(L);
        printf("������Ҫ��Ӽ���ѧ������Ϣ\n");
        scanf("%d", &k);
        ListInsert(&L, k);//����k��ѧ����Ϣ
        printf("���ڵ�ѧ����ϢΪ\n");
        DisplayList(L);//��ӡ���ڵ�ѧ����Ϣ
        printf("������Ҫɾ����ѧ��\n");
        scanf("%s", input);
        DeleteList(&L, input);//ɾ����ѧ�ŵ�ѧ����Ϣ
        DisplayList(L);//��ӡ���ڵ�ѧ����Ϣ
        printf("��������˳����������\n");
        SortList(&L);
        DisplayList(L);//��ӡѧ����Ϣ
        return 0;
}

void ListInsert(Sqlist *L, int k)//��β������K��ѧ������Ϣ
{
        //�ٷ���K����λ�ռ�
        if(L->length+k >= L->listsize)
        {
                L->num = (ElemType*)realloc(L->num, (L->listsize + k) * sizeof(ElemType));
                if(! L->num)
                {
                        exit(1);
                }
        }
        GetInput(L, k);//����ѧ����Ϣ
        L->length += k;
        L->listsize +=k; //����k
}
void InitList(Sqlist *L, int n)
{
        L->num = malloc(n * sizeof(ElemType));//����n��ѧ���Ŀռ�
        if(!L->num)
        {
                exit(1);
        }
        L->length = 0;
        GetInput(L, n);//        ����ѧ����Ϣ
        L->length = n;
        L->listsize = n;
}
void DeleteList(Sqlist *L, char input[])//��ѧ��ɾ��
{
        int i = 0;
        while(i != L->length && strcmp(L->num[i].id, input))
        {
                i++;
        }
        //iΪҪɾ���������±����Ϊ0;
        //iΪ0ʱ�����i��Ӧ��id�������ѧ�Ų�ͬ����δ�ҵ���ѧ��
        if(i == 0 && strcmp(L->num[i].id, input))
        {
                printf("δ�ҵ���ѧ��\n");
        }
        //ɾ������
        for(int j = i; j < L->length - 1; j++)
        {
                L->num[j] = L->num[j + 1];
        }
        L->length--;
}

void SortList(Sqlist *L)//���ܷ���������
{
        int i, j;
        int min ;
        //ѡ������
        for(i = 0; i < L->length - 1; i++)
        {
                min = i;
                for(j = i + 1; j < L->length; j++)
                {
                        if(L->num[i].sum > L->num[j].sum)
                        {
                                min = j;
                        }
                }
                if(min != i)
                {
                        ElemType temp = L->num[i];
                        L->num[i] = L->num[min];
                        L->num[min] = temp;
                }
        }
}

void DisplayList(Sqlist L)//��ӡ����ѧ����Ϣ
{
        for(int i = 0; i < L.length; i++)
        {
                printf("ѧ��:%s\t����:%.2lf\t��ѧ:%.2lf\tӢ��:%.2lf\t�ܷ�:%.2lf\t��Ȩƽ����:%.2lf\n", L.num[i].id, L.num[i].Chinese, L.num[i].Math, L.num[i].English, L.num[i].sum, L.num[i].weight_average);
        }
}

void GetInput(Sqlist *L, int n)//�����Ϣ
{
        int j ;
        for(j = L->length; j < L->length + n; j++)
        {
                printf("�������%d��ѧ����ѧ��:\n", j + 1);
                scanf("%s", L->num[j].id);
                printf("�������%d��ѧ�������ĳɼ�\n", j + 1);
                scanf("%lf", &L->num[j].Chinese);
                printf("�������%d��ѧ������ѧ�ɼ�\n", j + 1);
                scanf("%lf", &L->num[j].Math);
                printf("�������%d��ѧ����Ӣ��ɼ�\n", j + 1);
                scanf("%lf", &L->num[j].English);
                L->num[j].sum = L->num[j].Chinese + L->num[j].Math + L->num[j].English;
                L->num[j].weight_average = 0.3 * L->num[j].Chinese + 0.5 * L->num[j].Math + 0.2 * L->num[j].English;
        }
}
