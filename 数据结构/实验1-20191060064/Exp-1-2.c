#include <stdio.h>
#include <stdlib.h>

int fibonacci_1(int k, int n)
{
        if(!(k >= 1 && k <= 5))
                return 0;
        if(!(n >= 0 && n <= 30))
                return 0;
        int i = 0, sum = 0;
        if(n < k)
        {
                return 0;//ǰk-1��Ϊ0
        }
        else if(n == k)
        {
                return 1;//��k��Ϊ1
        }
        else
        {
                for(i = 1; i < k + 1; i++)
                {
                        sum = sum + fibonacci_1(k, n - i);//�ݹ����n��
                }
        }
        return sum;
}

int fibonacci_2(int k, int n)
{
        int sum, i, j, e[30], result = 0;
        if(n < k)
                return  0;
        else if(n == k)
                return  1;
        else
        {
                for(i = 0; i < k - 1; i++)
                {
                        e[i] = 0;//K��쳲��������е�ǰK-1���Ϊ0
                }
                e[k - 1] = 1;  //��k��Ϊ1
                for(i = k; i <= n; i++)
                {
                        sum = 0;
                        for(j = i - k; j < i; j++) //�Ժ��ÿһ���ǰk��ĺ�
                        {
                                sum += e[j];
                        }
                        e[i] = sum;  //���Ժ��ÿһ���ֵ�������e��
                }
                result = e[n - 1];
        }
        return result;
}
int main()
{
        int k,n,result;
        printf("���������н���:\n");
        scanf("%d",&k);
        printf("�����������еڶ�����:\n",&n);
        scanf("%d",&n);

        printf("�ý׳˵Ľ��Ϊ��\n");
        result = fibonacci_1(k, n);
        printf("%d\n",result);
        printf("�÷ǽ׳˵Ľ��Ϊ��\n");
        result = fibonacci_2(k, n);
        printf("%d\n",result);
        return 0;
}
