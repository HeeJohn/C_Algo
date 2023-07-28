/*
	program : heapsort
	name : yeongjin kim
	last edited : 23.07.24
*/
#include <stdio.h>

#define MAX_ELEMENT 200
#define HEAP_FULL(n) (n==MAX_ELEMENT-1)
#define HEAP_EMPTY(n) (!n)
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct
{
	int key;
}element;
element heap[MAX_ELEMENT];
int n = 0;

void adjust(element a[], int root, int size)
{
	int child, rootkey;
	element temp;
	temp = a[root];
	rootkey = a[root].key;
	child = 2 * root;
	while (child <= size)
	{
		if ((child < size) && (a[child].key < a[child + 1].key))
			child++;
		if (rootkey > a[child].key)
			break;
		else
		{
			a[child / 2] = a[child];
			child *= 2;
		}
	}
	a[child / 2] = temp;
}

void heapSort(element a[], int size)
{
	int i, j;
	element temp;

	for (i = size / 2; i > 0; i--)
		adjust(a, i, size);
	for (i = size - 1; i > 0; i--)
	{
		SWAP(a[1], a[i+1], temp);
		adjust(a, 1, i-1);
	}
}
int main()
{
	int a[11] = { NULL,26,5,37,1,61,11,59,15,48,19};
	printf("Before sorted: ");
	for (int i = 1; i < 11; i++)
		printf("%d ", a[i]);
	heapSort(a, 10);
	printf("\nAfter sorted: ");
	for (int i = 1; i < 11; i++)
		printf("%d ", a[i]);
	return 0;
}