/*
    program : quickSort_ymh
    name : minhyuck yun
    last_edit : 23.07.23
*/

//퀵정렬
#include <stdio.h>

#define SWAP(a, b, temp) temp = a, a = b, b = temp // SWAP 매크로를 정의하여 두 변수의 값을 교환하는데 사용됩니다.

typedef struct {
    int key;
}element; // element라는 이름의 구조체를 정의합니다. 이 구조체는 정렬하려는 데이터를 담을 때 사용됩니다.

void quickSort(element a[], int left, int right); // 퀵 정렬 함수의 원형을 선언합니다.

int main(void)
{
    int left = 0; // 정렬할 배열의 시작 인덱스를 저장할 변수입니다.
    int right = 9; // 정렬할 배열의 끝 인덱스를 저장할 변수입니다.
    element a[10] = { 26, 5, 37, 1, 61, 11, 59, 15, 48, 19 }; // 정렬하려는 원본 데이터가 담긴 배열입니다.

    printf("초기값\n");
    for (int i = 0; i < 10; i++)
        printf("%d  ", a[i]);
    printf("\n");

    quickSort(a, left, right); // 퀵 정렬 함수를 호출하여 배열을 정렬합니다.

    printf("정렬 후\n");
    for (int i = 0; i < 10; i++)
        printf("%d  ", a[i]);
    printf("\n");
}

void quickSort(element a[], int left, int right)
{
    int pivot, i, j; // pivot은 기준이 되는 원소의 인덱스, i와 j는 각각 왼쪽과 오른쪽에서 pivot과 비교할 원소들의 인덱스를 가리킵니다.
    element temp; // SWAP 매크로를 사용하여 값 교환 시 임시로 사용할 구조체 변수입니다.

    if (left < right) // 배열의 크기가 1 이상인 경우에만 정렬을 수행합니다. 즉, left가 right보다 작을 때만 재귀적으로 정렬을 수행합니다.
    {
        i = left; // i는 배열의 왼쪽 끝에서 시작합니다.
        j = right + 1; // j는 배열의 오른쪽 끝에서 시작합니다.
        pivot = a[left].key; // 배열의 가장 왼쪽에 있는 원소를 pivot으로 선택합니다.

        do
        {
            do
                i++; // pivot보다 크거나 같은 원소를 찾을 때까지 i를 증가시킵니다.
            while (a[i].key < pivot);

            do
                j--; // pivot보다 작거나 같은 원소를 찾을 때까지 j를 감소시킵니다.
            while (a[j].key > pivot);

            if (i < j) // i와 j가 엇갈리지 않은 경우 (아직 정렬할 원소들이 남아있는 경우)
                SWAP(a[i], a[j], temp); // i와 j에 해당하는 원소를 교환합니다. 이를 통해 pivot을 중심으로 왼쪽은 작은 값, 오른쪽은 큰 값이 오도록 정렬됩니다.
        } while (i < j); // i와 j가 엇갈릴 때까지 반복합니다.

        SWAP(a[left], a[j], temp); // pivot과 a[j]를 교환합니다. 이로써 pivot을 올바른 위치에 배치합니다.

        quickSort(a, left, j - 1); // pivot을 중심으로 왼쪽 부분 배열을 재귀적으로 정렬합니다.
        quickSort(a, j + 1, right); // pivot을 중심으로 오른쪽 부분 배열을 재귀적으로 정렬합니다.
    }
}