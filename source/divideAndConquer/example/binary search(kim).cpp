//#include <stdio.h>
//#define SWAP(x,y,t) ((t)=(x), (x)=(y),(y)=(t))
//
//typedef struct {
//	int key;
//}element;
//
//element a[10] = { 26,5,37,1,61,11,59,15,48,19 };
//int Binary_Search(element arr[], int target, int low, int high);
//void quickSort(element a[], int left, int right);
//
//void main() {
//	int l = 0, r = 9;
//	int target;
//	quickSort(a, l, r);
//
//	for (int i = 0; i < 10; i++)
//		printf("%d  ", a[i].key);
//
//
//	printf("\n찾고 싶은 값을 입력하시오\n");
//	scanf_s("%d", &target);
//
//	printf("target = %d", Binary_Search(a, target, 0, 10));
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
//
//int Binary_Search(element arr[], int target, int low, int high) {
//    int mid = (low + high) / 2;
//    if (arr[mid].key == target)
//        return mid+1;
//    else if (arr[mid].key > target)
//        return Binary_Search(arr, target, low, mid - 1);
//    else
//        return Binary_Search(arr, target, mid + 1, high);
//}