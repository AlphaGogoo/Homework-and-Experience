#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int BinarySearch( char input[], int n, char key );
int main()
{
	int n;
	char input[1024], key;
	printf("������һ�ηǵݼ���������\n");
	gets(input);
	n = strlen(input);
	printf("������Ҫ���ҵ��ַ�\n");
	scanf("%c",&key);
	if( BinarySearch( input, n, key) )
	{
		printf("�ҵ����ַ�\n");
	}
	else
	{
		printf("δ�ҵ����ַ�\n");
	}
	return 0;
}
int BinarySearch( char input[], int n, char key )
{
	int low, high, mid;
	low = 0;
	high = n-1;
	while( high >= low )
	{
		int mid = (low + high)/2;
		if( key == input[mid] )
		{
			return 1;
		}
		else if( key > input[mid] )
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}
	return 0;
}