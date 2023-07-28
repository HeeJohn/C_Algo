/*
	program : quicksort
	name : yeongjin kim
	last edited : 23.07.24
*/
#include <stdio.h>

#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))
typedef struct
{
	int key;
}element;

void quickSort(element a[], int left, int right)
{
	int pivot, i, j;
	element temp;
	if (left < right)
	{
		i = left;
		j = right + 1;
		pivot = a[left].key;
		do
		{
			do { i++; } while (a[i].key < pivot);
			do { j--; } while (a[j].key > pivot);
			if (i < j) SWAP(a[i], a[j], temp);
		} while (i < j);
	SWAP(a[left], a[j], temp);
	quickSort(a, left, j - 1);
	quickSort(a, j + 1, right);
	}
}
int main()
{
	int a[10] = { 26,5,37,1,61,11,59,15,48,19 };
	printf("Before sorted: ");
	for (int i = 0; i < 10; i++)
		printf("%d ", a[i]);
	quickSort(a, 0, 9);
	printf("\nAfter sorted: ");
	for (int i = 0; i < 10; i++)
		printf("%d ", a[i]);
	return 0;
}