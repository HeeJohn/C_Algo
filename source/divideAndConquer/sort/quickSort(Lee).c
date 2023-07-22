#define _CRT_SECURE_NO_WARNINGS/*항공소프트웨어공학과 202000974 이재혁*/
#include <stdio.h>
typedef struct
{ /* 레코드 구조체 */
	int key;
}element;
void SWAP(element* n1, element* n2, element* temp)
{ /* n1과 n2 swap 함수 */
	*temp = *n1;
	*n1 = *n2;
	*n2 = *temp;
}
void quickSort(element a[], int left, int right)
{ /* 퀵정렬(오름차순) */
	int pivot, i, j;
	element temp;
	if (left < right)
	{
		i = left;
		j = right + 1;
		pivot = a[left].key;                            // pivot은 left의 key 값으로 정함
		do
		{
			do i++; while (a[i].key < pivot && i < right);        // pivot을 기준으로 왼쪽은 pivot보다 작은 값이 오도록 한다.
			do j--; while (a[j].key > pivot && j > left);       // pivot을 기준으로 오른쪽은 pivot보다 큰 값이 오도록 한다.
			if (i < j) SWAP(&a[i], &a[j], &temp);  /* if문이 실행됐다면 pivot을 기준으로 i 위치에 pivot보다 큰 값이 있고
													  j 위치에 pivot보다 작은 값이 있다는 것이다. 그러므로 SWAP 함수를 통해 바꿔준다. */

		} while (i < j);                          // i와 j가 엇갈리면 pivot 기준 정렬이 끝남
		SWAP(&a[left], &a[j], &temp);            // left를 pivot으로 정했으므로 left와 j의 값을 바꿔준다.(j는 pivot보다 작은 값을 가리키기 때문)
		quickSort(a, left, j - 1);              // left ~ (pivot-1) 재귀
		quickSort(a, j + 1, right);            //  (pivot+1) ~ right 재귀
	}
}
int main()
{
	element arr[11] = { 0, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

	printf("정렬 전: ");
	for (int i = 1;i <= 10;i++)
		printf("%d ", arr[i].key);

	quickSort(arr, 1, 10);

	printf("\n정렬 후: ");
	for (int i = 1;i <= 10;i++)
		printf("%d ", arr[i].key);
}