#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))
#include<stdio.h>

typedef struct {
	int key;
}element;

void quickSort(element a[], int left, int right);
void print(element a[], int pivot);
void scan(void);
int main() {

	scan();
}
void scan(void) {
	int i;
	element a[10];
	for (i = 0; i < 10; i++) {
		scanf("%d", &a[i].key);
	}
	quickSort(a, 0, 9);
}
void quickSort(element a[], int left, int right) {
	int pivot, i, j;
	element temp;
	if (left < right) {	 // 왼쪽보다 오른쪽이 큰 경우 
		i = left;
		j = right + 1;
		pivot = a[left].key;
		do {
			do i++;
			while (a[i].key < pivot);	// 피봇보다 작은 경우 
			do j--;
			while (a[j].key > pivot);	// 피봇보다 큰 경우 
			if (i < j)
				SWAP(a[i], a[j], temp);	// i보다 j가 큰 경우 스왑 
		} while (i < j);			// 왼쪽보다 오른쪽이 클때까지 
		SWAP(a[left], a[j], temp);	// 피봇과 마지막 오른쪽을 스왑해줌 
		print(a, pivot);			// 스왑되는 과정을 보여준다.
		quickSort(a, left, j - 1);	// 피봇 왼쪽 재귀
		quickSort(a, j + 1, right);	// 피봇 오른쪽 재귀 
	}
}
void print(element a[], int pivot) {
	printf("\nPivot is %d\n", pivot);
	for (int i = 0; i < 10; i++) {

		printf("%d ", a[i].key);
	}
	printf("\n");
}