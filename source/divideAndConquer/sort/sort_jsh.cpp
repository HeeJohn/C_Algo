#include <stdio.h>
#include <time.h>
#include<stdlib.h>
#include<Windows.h>
#define MAX_SIZE 8
#define SWAP(x,y,t) ((t)=(x), (x)=(y),(y)=(t))
typedef struct {
    int key;
}element;

void printarr(element arr[], bool isheap);
//������
void arrcreateRandom(element arr[],bool isheap);
void qsort(element arr[], int left, int right);

//������
void adjust(element arr[], int root, int n);
void heapSort(element arr[], int n);
int main() {
    element quicksort[MAX_SIZE];
    bool isheap = false;
    arrcreateRandom(quicksort, isheap);
    qsort(quicksort, 0, MAX_SIZE-1);
    printarr(quicksort, isheap);
    
 
    isheap = true;
    element heapsort[MAX_SIZE + 1];
    arrcreateRandom(heapsort, isheap);
    heapSort(heapsort, MAX_SIZE);
    printarr(heapsort, isheap);
}

void printarr(element arr[], bool isheap)
{
 
    printf("���� \n");
    int i,j;
    i=j=0;
    if (isheap)
    {
        i++;   j++;
    }
    for (; i < MAX_SIZE + j; i++)
        printf("%d ", arr[i].key);


    printf("\n");
}
void arrcreateRandom(element arr[],bool isheap) {
    Sleep(200);
    srand((unsigned)time(NULL));
    printf("���� : ");
    int i,j;
    i = j = 0;
    if (isheap)
    {
        i++;   j++;
    }
    for (; i < MAX_SIZE + j; i++)
    {
        arr[i].key = rand() % 100;
        printf("%d ", arr[i].key);
    }
    printf("\n");
}
void qsort(element arr[], int left, int right)
{
    int i, j, pivot;
    element temp;

    if (left < right)
    {
        pivot = arr[left].key;//���� ���ʿ� �ִ� ���Ҹ� �Ǻ����� ����
        i = left;//���� ��
        j = right+1;//������ ��

        do {
            do i++; while (arr[i].key < pivot);//�Ǻ����� ū ���Ҹ� ã�� �� ���� i����
            do j--; while (arr[j].key > pivot);//�Ǻ����� ���� ���Ҹ� ã�� �� ���� j����

            if (i < j) SWAP(arr[i], arr[j], temp);//�׷��� j�� ũ�ٸ� i��° ���ҿ� j��° ���Ҹ� ��ȯ�ϹǷν� �Ǻ��� �߽����� ������ ���� ��, �����ʿ��� ū ���� ����
        } while (i < j); //j�� i���� �۾��� �� ���� �ݺ�
        SWAP(arr[left], arr[j], temp);//�Ǻ��� j��° ���Ҹ� ��ȯ�ϹǷν� �Ǻ��� �������� ��ġ
        qsort(arr, left, j - 1);//�Ǻ��� ������ ȣ�������ν� �����ڵ� �ݺ�
        qsort(arr, j + 1, right);//�Ǻ��� �������� ȣ�������ν� ���� �ڵ� �ݺ�
    }
}





void adjust(element arr[], int root, int n)//�������� ����
{
    int child, rootkey;
    element temp;
    temp = arr[root];
    rootkey = arr[root].key;
    child = 2 * root;

    while (child <= n)
    {
        if ((child < n) && (arr[child].key < arr[child + 1].key))
            child++;//�� �ڽĿ����� �� ū �ڽĿ��� ����

        if (rootkey > arr[child].key)
            break;
        else {//�ڽĿ��Ұ� �θ���Һ��� Ŭ ���
            arr[child / 2] = arr[child]; // �θ���ҿ� �ڽĿ��� ��ȯ
            child *= 2;
        }
    }
    arr[child / 2] = temp; //�θ� ��忡 ��Ʈ��� ��ġ

}

void heapSort(element arr[], int n)//�������� ����
{
    int i;
    element temp;

    for (i = n / 2; i > 0; i--)
        adjust(arr, i, n);
    for (i = n - 1; i > 0; i--)
    {
        SWAP(arr[1], arr[i + 1], temp);
        adjust(arr, 1, i);
    }
}