#include <stdio.h>
#include <stdlib.h>

int num = 0;
void hanio(int n, char a, char b, char c);
/*�����A�̷�ԭʼԲ�̣�C��ΪĿ��Բ��*/
int main()
{
        int n ;
        printf("������A��Բ�̸���\n");
        scanf("%d",&n);
        hanio(n, 'A', 'B', 'C');
}
void hanio(int n, char a, char b, char c)
{
        if(n == 1)
        {
                num++;//ͳ���ƶ�����
                printf("��%d�� %c-->%c\n", num, a, c);//ֱ�Ӵ�A�ƶ���C
        }
        else
        {
                hanio(n - 1, a, c, b);//�Ȱ�A��ǰn-1���̴�AŲ��B���м����C
                num++;//ͳ���ƶ�����
                printf("��%d�� %c-->%c\n", num, a, c);//��A�ƶ���C
                hanio(n - 1, b, a, c);//B��Ϊԭʼ����CΪĿ����������A�ƶ�
        }
}
