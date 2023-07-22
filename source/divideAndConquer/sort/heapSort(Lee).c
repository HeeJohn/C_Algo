#define _CRT_SECURE_NO_WARNINGS/*�װ�����Ʈ������а� 202000974 ������*/
#include <stdio.h>
#define MAX_HEAP 100
typedef struct
{ /* �� ���� ����ü */
	int key;
}element;
void adjust(element a[], int root, int n)
{ /* �ִ�(�ּ�) ���� ���� �Լ� */
	int child, rootkey;
	element temp;
	temp = a[root];
	rootkey = a[root].key;
	child = 2 * root;
	while (child <= n)
	{
		if ((child < n) && (a[child].key < a[child + 1].key))
			child++;
		if (rootkey > a[child].key)
		{
			break;
		}
		else
		{
			a[child / 2] = a[child];
			child *= 2;
		}
	}
	a[child / 2] = temp;
}
void SWAP(element* s1, element* s2)
{
	element temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}
void heapSort(element a[], int n)
{ /* �� ���� �Լ� */
	int i, j;

	for (i = n / 2;i > 0;i--)
		adjust(a, i, n);

	for (i = n - 1;i > 0;i--)
	{
		SWAP(&a[1], &a[i + 1]);
		adjust(a, 1, i);
	}
}
int main()
{
	element heap[MAX_HEAP] = { 0, 26, 5, 77, 1, 59, 11, 61, 15, 48, 19 };

	printf("���� ��:");
	for (int i = 1;i <= 10;i++)
		printf("%d ", heap[i].key);

	heapSort(heap, 10);

	printf("\n���� ��: ");
	for (int i = 1;i <= 10;i++)
		printf("%d ", heap[i].key);

	return 0;
}