/*
    program : hip_ymh
    name : minhyuck yun
    last_edit : 23.07.23
*/

//히프정렬
#include <stdio.h>

#define SWAP(a, b, temp) temp = a, a = b, b = temp // SWAP 매크로를 정의하여 두 변수의 값을 교환하는데 사용됩니다.

typedef struct {
    int key;
}element; // element라는 이름의 구조체를 정의합니다. 이 구조체는 정렬하려는 데이터를 담을 때 사용됩니다.

void heapSort(element a[], int n);
void adjust(element a[], int root, int n);

int main(void)
{
    element a[8] = { 0, 26, 5, 37, 1, 61, 11, 59 }; // 인덱스 0은 사용하지 않으며, 데이터는 인덱스 1부터 시작합니다.
    printf("초기값\n");
    for (int i = 1; i < 8; i++)
        printf("%d  ", a[i]);
    printf("\n");

    heapSort(a, 7); // 히프 정렬 함수를 호출하여 배열을 정렬합니다.

    printf("정렬 후\n");
    for (int i = 1; i < 8; i++)
        printf("%d  ", a[i]);
    printf("\n");
}

void heapSort(element a[], int n)
{
    int i, j;
    element temp;

    // 초기 히프를 구성합니다.
    for (i = n / 2; i > 0; i--)
        adjust(a, i, n);

    // 히프 정렬을 수행합니다.
    for (i = n - 1; i > 0; i--)
    {
        SWAP(a[1], a[i + 1], temp); // 최대 히프의 최대값(루트 노드)을 현재 정렬되지 않은 부분의 마지막 값과 교환합니다.
        adjust(a, 1, i); // 교환된 루트 노드를 기준으로 최대 히프 속성을 만족하도록 조정합니다.
    }
}

void adjust(element a[], int root, int n)
{
    int child, rootkey;
    element temp;
    temp = a[root];
    rootkey = a[root].key;
    child = 2 * root;

    while (child <= n)
    {
        if ((child < n) && (a[child].key < a[child + 1].key))
            child++; // 두 자식 중 더 큰 값을 가진 자식을 선택합니다.

        if (rootkey > a[child].key)
            break; // 최대 히프 속성을 만족하면 루프를 종료합니다.
        else
        {
            a[child / 2] = a[child]; // 부모 노드와 더 큰 자식 노드를 교환합니다.
            child *= 2; // 자식 노드로 이동합니다.
        }
    }

    a[child / 2] = temp; // 최종적으로 부모 노드와 교환되어야 할 위치에 원래 root 노드 값을 배치합니다.
}