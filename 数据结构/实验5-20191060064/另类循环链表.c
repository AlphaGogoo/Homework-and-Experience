#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
typedef int ElemType;
typedef int Position;
typedef enum { false, true } bool;

typedef struct QNode
{
	ElementType *Data;  /* �洢Ԫ�ص�����   */
	Position Front;     /* ���е�ͷָ��     */
	int Count;          /* ������Ԫ�ظ���   */
	int MaxSize;        /* �����������     */
} *PtrToQNode,*Queue;

bool AddQ( Queue Q, ElementType X )//�����
{
	if(Q->Count == Q->MaxSize)//����������
	{
		printf("Queue Full\n");
		return false;
	}
	else//������δ��
	{
		Q->Data[(Q->Front + Q->Count)%Q->MaxSize] = X;//(Q->Front + Q->Count)/Q->MaxSize  ��ʾ��βԪ�ص���һ��Ԫ�ص��±�
		Q->Count++;//Ԫ������1
	}
	return true;
}
ElementType DeleteQ( Queue Q )//������
{
	ElementType e;
	if(0 == Q->Count)//�ӿ�
	{
		printf("Queue Empty\n");
		return ERROR;
	}
	else
	{
		e = Q->Data[Q->Front];//��ȡ����Ԫ��
		Q->Front = (Q->Front + 1)%Q->MaxSize;//ͷָ��ǰ��
		Q->Count--;//Ԫ������һ
	}
	return e;
}









