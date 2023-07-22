#define _CRT_SECURE_NO_WARNINGS/*�װ�����Ʈ������а� 202000974 ������*/
#include <stdio.h>
typedef struct
{ /* ���ڵ� ����ü */
	int key;
}element;
void SWAP(element* n1, element* n2, element* temp)
{ /* n1�� n2 swap �Լ� */
	*temp = *n1;
	*n1 = *n2;
	*n2 = *temp;
}
void quickSort(element a[], int left, int right)
{ /* ������(��������) */
	int pivot, i, j;
	element temp;
	if (left < right)
	{
		i = left;
		j = right + 1;
		pivot = a[left].key;                            // pivot�� left�� key ������ ����
		do
		{
			do i++; while (a[i].key < pivot && i < right);        // pivot�� �������� ������ pivot���� ���� ���� ������ �Ѵ�.
			do j--; while (a[j].key > pivot && j > left);       // pivot�� �������� �������� pivot���� ū ���� ������ �Ѵ�.
			if (i < j) SWAP(&a[i], &a[j], &temp);  /* if���� ����ƴٸ� pivot�� �������� i ��ġ�� pivot���� ū ���� �ְ�
													  j ��ġ�� pivot���� ���� ���� �ִٴ� ���̴�. �׷��Ƿ� SWAP �Լ��� ���� �ٲ��ش�. */

		} while (i < j);                          // i�� j�� �������� pivot ���� ������ ����
		SWAP(&a[left], &a[j], &temp);            // left�� pivot���� �������Ƿ� left�� j�� ���� �ٲ��ش�.(j�� pivot���� ���� ���� ����Ű�� ����)
		quickSort(a, left, j - 1);              // left ~ (pivot-1) ���
		quickSort(a, j + 1, right);            //  (pivot+1) ~ right ���
	}
}
int main()
{
	element arr[11] = { 0, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

	printf("���� ��: ");
	for (int i = 1;i <= 10;i++)
		printf("%d ", arr[i].key);

	quickSort(arr, 1, 10);

	printf("\n���� ��: ");
	for (int i = 1;i <= 10;i++)
		printf("%d ", arr[i].key);
}