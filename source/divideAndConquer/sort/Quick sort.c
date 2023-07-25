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
	if (left < right) {	 // ���ʺ��� �������� ū ��� 
		i = left;
		j = right + 1;
		pivot = a[left].key;
		do {
			do i++;
			while (a[i].key < pivot);	// �Ǻ����� ���� ��� 
			do j--;
			while (a[j].key > pivot);	// �Ǻ����� ū ��� 
			if (i < j)
				SWAP(a[i], a[j], temp);	// i���� j�� ū ��� ���� 
		} while (i < j);			// ���ʺ��� �������� Ŭ������ 
		SWAP(a[left], a[j], temp);	// �Ǻ��� ������ �������� �������� 
		print(a, pivot);			// ���ҵǴ� ������ �����ش�.
		quickSort(a, left, j - 1);	// �Ǻ� ���� ���
		quickSort(a, j + 1, right);	// �Ǻ� ������ ��� 
	}
}
void print(element a[], int pivot) {
	printf("\nPivot is %d\n", pivot);
	for (int i = 0; i < 10; i++) {

		printf("%d ", a[i].key);
	}
	printf("\n");
}