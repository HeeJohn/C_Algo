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
//퀵정렬
void arrcreateRandom(element arr[],bool isheap);
void qsort(element arr[], int left, int right);

//힙정렬
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
 
    printf("정렬 \n");
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
    Sleep(200);//랜덤 숫자의 차이를 두기 위해 시간 지연
    srand((unsigned)time(NULL));
    printf("숫자 : ");
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
        pivot = arr[left].key;//가장 왼쪽에 있는 원소를 피봇으로 설정
        i = left;//왼쪽 끝
        j = right+1;//오른쪽 끝

        do {
            do i++; while (arr[i].key < pivot);//피봇보다 큰 원소를 찾을 때 까지 i증가
            do j--; while (arr[j].key > pivot);//피봇보다 작은 원소를 찾을 때 까지 j감소

            if (i < j) SWAP(arr[i], arr[j], temp);//그래도 j가 크다면 i번째 원소와 j번째 원소를 교환하므로써 피봇을 중심으로 왼쪽은 작은 값, 오른쪽에는 큰 값이 정렬
        } while (i < j); //j가 i보다 작아질 때 까지 반복
        SWAP(arr[left], arr[j], temp);//피봇과 j번째 원소를 교환하므로써 피봇을 기준으로 배치
        qsort(arr, left, j - 1);//피봇의 왼쪽을 호출함으로써 위의코드 반복
        qsort(arr, j + 1, right);//피봇의 오른쪽을 호출함으로써 위의 코드 반복
    }
}





void adjust(element arr[], int root, int n)//내림차순 정렬
{
    int child, rootkey;
    element temp;
    temp = arr[root];
    rootkey = arr[root].key;
    child = 2 * root;

    while (child <= n)
    {
        if ((child < n) && (arr[child].key < arr[child + 1].key))
            child++;//두 자식원소중 더 큰 자식원소 선택

        if (rootkey > arr[child].key)
            break;
        else {//자식원소가 부모원소보다 클 경우
            arr[child / 2] = arr[child]; // 부모원소와 자식원소 교환
            child *= 2;
        }
    }
    arr[child / 2] = temp; //부모 노드에 루트노드 배치

}

void heapSort(element arr[], int n)//내림차순 정렬
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
