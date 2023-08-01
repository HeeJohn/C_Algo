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
    int smallest = root; // ��Ʈ ���
    int left = 2 * root + 1; // ���� �ڽ� ���
    int right = 2 * root + 2; // ������ �ڽ� ���
    int temp;

    // ���� �ڽ� ��尡 ��Ʈ���� �۴ٸ� smallest�� ���� �ڽ����� ����
    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    // ������ �ڽ� ��尡 smallest���� �۴ٸ� smallest�� ������ �ڽ����� ����
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    // smallest�� ��Ʈ�� �ƴ϶�� ��Ʈ�� smallest�� ��ġ�� ��ȯ�ϰ�
    // ��������� smallest�� ��Ʈ�� �� ������ �ּ� �� ����
    if (smallest != root) {
        SWAP(*(arr+root), *(arr+smallest), temp);
        minHeap(arr, n, smallest);
    }
}
void heapSort(int *arr, int n) {
    int temp;
    // �ּ� ������ ����
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeap(arr, n, i);
    }

    // ������ ���� ���� ��(��Ʈ ���)�� ���� �迭�� �ڷ� ������ ����
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

    // �ӽ� �迭�� ������ ����
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0; // ���� �迭�� �ε���
    j = 0; // ������ �迭�� �ε���
    k = left; // ���� �迭�� �ε���

    // �� ���� �迭�� �պ�
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
    // ���� ���ҵ��� �迭�� ����
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
// �պ� ���� �Լ�
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // �� ���� �κ� �迭�� ����
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // ���� �κ� �迭�� �պ�
        merge(arr, left, mid, right);
    }
}

int main() {
    int arr[] = { 1, 38, 27, 43, 3, 9, 82, 10, 88 };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("<������>\n�� ���� ���� �迭: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    quickSort(arr, 0, n - 1);
    printf("\n�� ���� ���� �迭: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    
    int arr1[] = { 1, 13, 27, 34, 3, 9, 82, 20, 78 };
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("\n<������>\n�� ���� ���� �迭: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr1[i]);
    }
    heapSort(arr1, n1);
    printf("\n�� ���� ���� �迭: ");
    for (int i = 0; i < n1; i++) {
        printf("%d ", arr1[i]);
    }


    mergeSort(arr, 0, n - 1);

    printf("\n�պ� ���� ���� �迭: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
