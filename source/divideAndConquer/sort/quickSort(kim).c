//#include <stdio.h>
//#define SWAP(x,y,t) ((t)=(x), (x)=(y),(y)=(t))
//
//typedef struct {
//	int key;
//}element;
//
//element a[10] = {26,5,37,1,61,11,59,15,48,19};
//void quickSort(element a[], int left, int right);
//
//void main() {
//	int l=0, r=9;
//	quickSort(a,l,r);
//
//	for (int i = 0; i < 10; i++)
//		printf("%d  ", a[i].key);
//}
//
//void quickSort(element a[], int left, int right) {
//	int pivot, i, j;
//	element temp;
//	if (left < right) {
//		i = left; j = right + 1;
//		pivot = a[left].key;
//		do {
//			do i++; while (a[i].key < pivot);
//			do j--; while (a[j].key > pivot);
//			if (i < j)
//				SWAP(a[i], a[j], temp);
//		} while (i < j);
//		SWAP(a[left], a[j], temp);
//		quickSort(a, left, j - 1);
//		quickSort(a, j + 1, right);
//	}
//}