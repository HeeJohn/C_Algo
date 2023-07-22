/*
    program : sort(quickSort & heapSort)
    name : HuiJun Seo
    last_edit: 23.07.22
*/
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define SIZE 10
#define SWAP(x,y,t) ((t)=(x), (x)=(y),(y)=(t))

typedef struct {
    int key;
}element;


void quickSort(element target[], int left, int right);
void randomCreate(element target[], int option);
void printArr(element target[], int option);
void adjust(element target[], int root, int n);
void heapSort(element target[], int n);




int main()
{
    /* ------- quick sort ------*/
    element quick[SIZE];
    randomCreate(quick, 1);
    quickSort(quick, 0, SIZE - 1);
    printf("quick => "); printArr(quick, 1);

    /* ------- heap sort ------*/
    element heap[SIZE + 1];
    randomCreate(heap, 2);
    heapSort(heap, SIZE);
    printf("heap => "); printArr(heap, 2);


    return 0;
}

/* ----------------- quick sort ------------------*/
void quickSort(element target[], int left, int right)
{
    int i, j, pivot;
    element temp;

    if (left < right)
    {
        pivot = target[left].key;
        i = left;
        j = right + 1;

        do {
            do i++; while (target[i].key < pivot);
            do j--; while (target[j].key > pivot);

            if (i < j) SWAP(target[i], target[j], temp);
        } while (i < j); SWAP(target[left], target[j], temp);
        quickSort(target, left, j - 1);
        quickSort(target, j + 1, right);
    }
}
/* ----------------- quick sort ------------------*/


void printArr(element target[], int option)
{
    printf("sorted numbers : ");
    int p = 0; int i = 0;
    if (option == 2)
    {
        i++;   p++;
    }
    for (; i < SIZE + p; i++)
        printf("%d ", target[i].key);


    printf("\n");
}


void randomCreate(element target[], int option)
{
    srand((unsigned)time(NULL));
    printf("random numbers : ");

    int p = 0; int i = 0;
    if (option == 2)
    {
        i++;   p++;
    }
    for (; i < SIZE + p; i++)
    {
        target[i].key = rand() % 100;
        printf("%d ", target[i].key);
    }
    printf("\n");

}



/* ----------------- heap sort ------------------*/

void adjust(element target[], int root, int n)
{
    int child, rootkey;
    element temp;
    temp = target[root];
    rootkey = target[root].key;
    child = 2 * root;

    while (child <= n)
    {
        if ((child < n) && (target[child].key < target[child + 1].key))
            child++;

        if (rootkey > target[child].key)
            break;
        else {
            target[child / 2] = target[child]; // switch parent<->child
            child *= 2;
        }
    }
    target[child / 2] = temp; // current child's parent

}

void heapSort(element target[], int n)
{
    int i;
    element temp;

    for (i = n / 2; i > 0; i--)
        adjust(target, i, n);
    for (i = n - 1; i > 0; i--)
    {
        SWAP(target[1], target[i + 1], temp);
        adjust(target, 1, i);
    }
}

/* ----------------- heap sort ------------------*/