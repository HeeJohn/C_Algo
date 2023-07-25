#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct {
    int key;
} element;

void adjust(element a[], int root, int n);
void heapSort(element a[], int n);
void print(element a[], int n);

int main() {
    element a[11]; // 배열 크기를 10으로 수정
    for (int i = 1; i < 11; i++) { // Index는 1부터 시작해서 10까지 채워준다.
        scanf("%d", &a[i].key);
    }

    heapSort(a, 10); // 배열의 크기를 10으로 수정

    printf("\n\nSorted array: ");
    print(a, 10); // 배열의 크기를 10으로 수정

    return 0;
}

void adjust(element a[], int root, int n) {
    /* 최대 히프 구조로 만들어주는 함수 */
    int child, rootkey;
    element temp;
    temp = a[root];
    rootkey = a[root].key;
    child = 2 * root; // left child
    while (child <= n) {
        if ((child < n) && (a[child].key < a[child + 1].key))
            child++;
        if (rootkey > a[child].key) // root와 최고 트리를 비교
            break;
        else {
            a[child / 2] = a[child]; // 자식과 부모 바꾸기
            child *= 2;
        }
    }
    a[child / 2] = temp;
    printf("\n조정 후 (root %d): ", root); // 
    print(a, n); // 배열의 크기를 n으로 수정
}

void heapSort(element a[], int n) {
    /* 히프 정렬을 해주는 함수 */
    int i, j;
    element temp;

    printf("===========최대 히프로 정렬하겠습니다.=============\n");
    for (i = n / 2; i > 0; i--) {   // 최대 히프로 정렬 시켜준다. 
        adjust(a, i, n);
    }
    printf("====================정렬 완료======================\n\n");

    printf("==============히프 정렬 하겠습니다.================\n");
    printf("초기 히프 : ");
    print(a, 10);
    for (i = n - 1; i > 0; i--) {   // 히프 정렬 해준다. 
        SWAP(a[1], a[i + 1], temp);
        adjust(a, 1, i);
    }
}

void print(element a[], int n) {
    for (int i = 1; i <= n; i++) {
        printf("%d ", a[i].key);
    }
    printf("\n");
}