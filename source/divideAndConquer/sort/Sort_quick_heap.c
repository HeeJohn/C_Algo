#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

int partition(int *arr, int start, int end) {
    int pivot, temp; 
    int low, high; 

    low = start; 
    high = end + 1; 
    pivot = arr[start]; 

    do {
        do { low++; } while (low <= end && arr[low] < pivot);
        do { high--; } while (high >= start && arr[high] > pivot);

        if (low < high)
            SWAP(*(arr + low), *(arr + high), temp);
    }
    while (low<high); 
    SWAP(*(arr+start), *(arr+high), temp);
    return high; 
}
void quickSort(int* arr, int start, int end) {
    int part;
    if (start < end) {
        part = partition(arr, start, end);
        quickSort(arr, start, part - 1);
        quickSort(arr, part + 1, end);
    }
}

void minHeap(int *arr, int n, int root) {
    int smallest = root; // 루트 노드
    int left = 2 * root + 1; // 왼쪽 자식 노드
    int right = 2 * root + 2; // 오른쪽 자식 노드
    int temp;

    // 왼쪽 자식 노드가 루트보다 작다면 smallest를 왼쪽 자식으로 설정
    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    // 오른쪽 자식 노드가 smallest보다 작다면 smallest를 오른쪽 자식으로 설정
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    // smallest가 루트가 아니라면 루트와 smallest의 위치를 교환하고
    // 재귀적으로 smallest가 루트가 될 때까지 최소 힙 구성
    if (smallest != root) {
        SWAP(*(arr+root), *(arr+smallest), temp);
        minHeap(arr, n, smallest);
    }
}
void heapSort(int *arr, int n) {
    int temp;
    // 최소 힙으로 구성
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeap(arr, n, i);
    }

    // 힙에서 가장 작은 값(루트 노드)을 꺼내 배열의 뒤로 보내며 정렬
    for (int i = n - 1; i >= 0; i--) {
        SWAP(*arr, *(arr+i), temp);
        minHeap(arr, i, 0);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // 임시 배열에 데이터 복사
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0; // 왼쪽 배열의 인덱스
    j = 0; // 오른쪽 배열의 인덱스
    k = left; // 원래 배열의 인덱스

    // 두 개의 배열을 합병
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    // 남은 원소들을 배열에 복사
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}
// 합병 정렬 함수
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // 두 개의 부분 배열로 나눔
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // 나뉜 부분 배열을 합병
        merge(arr, left, mid, right);
    }
}

int main() {
    int arr[] = { 1, 38, 27, 43, 3, 9, 82, 10, 88 };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("<퀵정렬>\n퀵 정렬 이전 배열: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    quickSort(arr, 0, n - 1);
    printf("\n퀵 정렬 이후 배열: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    
    int arr1[] = { 1, 13, 27, 34, 3, 9, 82, 20, 78 };
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("\n<힙정렬>\n힙 정렬 이전 배열: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr1[i]);
    }
    heapSort(arr1, n1);
    printf("\n힙 정렬 이후 배열: ");
    for (int i = 0; i < n1; i++) {
        printf("%d ", arr1[i]);
    }


    mergeSort(arr, 0, n - 1);

    printf("\n합병 정렬 이후 배열: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
