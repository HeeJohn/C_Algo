//#include <stdio.h>
//#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
//typedef struct {
//	int key;
//}element;
//
//element a[11] = { NULL, 26, 5, 77, 1, 59, 11, 61, 15, 48, 19 };
//
//void adjust(element a[], int root, int n);
//void heapSort(element a[], int n);
//
//void main() {
//
//	for (int i = 1; i <11; i++)
//		printf("%d  ", a[i].key);
//	printf("\n");
//
//	heapSort(a,10);
//
//	for (int i = 1; i < 11; i++)
//		printf("%d  ", a[i].key);
//
//}
//
//void adjust(element a[], int root, int n) {
//	int child, rootkey;
//	element temp;
//	temp = a[root];
//	rootkey = a[root].key;
//	child = 2 * root;
//	while (child <= n) {
//		if ((child < n) && (a[child].key < a[child + 1].key))
//			child++;
//		if (rootkey > a[child].key)
//			break;
//		else {
//			a[child / 2] = a[child];
//			child *= 2;
//		}
//	}
//	a[child / 2] = temp;
//}
//
//void heapSort(element a[],int n) {
//	int i, j;
//	element temp;
//
//	for (i = n / 2; i > 0; i--)
//		adjust(a, i, n);
//	for (i = n - 1; i > 0; i--)
//	{
//		SWAP(a[1], a[i + 1], temp);
//		adjust(a, 1, i);
//	}
//}