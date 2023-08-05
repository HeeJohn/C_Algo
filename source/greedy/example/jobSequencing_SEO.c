/*
    program : jobSequencing
    name : HuiJun Seo
    last_edit: 23.08.05
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
    if (!((p) = malloc(s))) { \
        fprintf(stderr, "insufficient memory space"); \
        exit(1); \
    }
#define SWAP(x, y, t) { (t) = (x); (x) = (y); (y) = (t); }

// A structure to represent a job
typedef struct Job {
    char id;      // Job Id
    int dead;     // Deadline of job
    int profit;   // Profit if job is over before or on deadline
} Job;

void printJobScheduling(Job arr[], int max);
void quickSort(Job arr[], int left, int right);
void printSlot(Job arr[], bool slot[], int result[], int n);
int findMaxDeadline(Job arr[], int n);
void printArray(Job arr[], int n);


// Driver's code
int main()
{
    Job arr[] = {
     { 'a', 2, 100 },
     { 'b', 2, 20 },
     { 'c', 1, 40 },
     { 'd', 3, 35 },
     { 'e', 1, 25 },
     { 'f', 4, 45 },
     { 'g', 3, 30 },
     { 'h', 2, 50 },
     { 'i', 5, 10 },
    };
    int n = sizeof(arr) / sizeof(arr[0]);




    printArray(arr, n);
    quickSort(arr, 0, n - 1); // Sort all jobs according to decreasing order of profit

    printf("\n--Sorted as decreasing order of profit--\n"); printArray(arr, n);


    printf("\n\nFollowing is maximum profit sequence of jobs\n");
    printJobScheduling(arr, n); // Function call

    return 0;
}

/* ----------------print ------------------*/

void printArray(Job arr[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("id : %c\t", arr[i].id);
        printf("dealine : %d\t", arr[i].dead);
        printf("profit : %d\n", arr[i].profit);
    }
    puts("");
}

void printSlot(Job arr[], bool slot[], int result[], int max)
{
    // Print the result
    int totalProfit = 0;
    for (int i = 0; i < max; i++) {
        if (slot[i]) {
            printf("id : %c\t", arr[result[i]].id);
            printf("dealine : %d\t", arr[result[i]].dead);
            printf("profit : %d\n", arr[result[i]].profit);
            totalProfit += arr[result[i]].profit;
        }
    }
    printf("\ntotal profit is %d\n", totalProfit);
}
/* ----------------print ------------------*/




/* ----------------job scheduling ------------------*/

int findMaxDeadline(Job arr[], int n)
{
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (max < arr[i].dead)
            max = arr[i].dead;
    }

    return max;
}

void printJobScheduling(Job arr[], int n)
{

    int max = findMaxDeadline(arr, n);
    printf("max deadline : %d\n", max);
    int* result;
    MALLOC(result, max); // To store result (Sequence of jobs)
    bool* slot;
    MALLOC(slot, max); // To keep track of free time slots



    // Initialize all slots to be free
    for (int i = 0; i < n; i++)
        slot[i] = false;

    int maxDeadline = 0;
    // Iterate through all given jobs
    for (int i = 0; i < n; i++)
    {
        int j = arr[i].dead - 1;
        if (slot[j] == false && maxDeadline + arr[i].dead <= max)
        {
            result[j] = i; // Add this job to result
            slot[j] = true; // Make this slot occupied
            maxDeadline += arr[i].dead;
        }
    }
    printSlot(arr, slot, result, max); // print the best slot
}
/* ----------------job scheduling ------------------*/


/* ---------------- sort jobs in order of decreasing profit ------------------*/
void quickSort(Job arr[], int left, int right)
{
    if (left < right)
    {
        int i, j;
        i = left;
        j = right + 1;
        Job pivot = arr[left];
        Job temp;
        do
        {
            do i++; while (pivot.profit < arr[i].profit);
            do j--; while (pivot.profit > arr[j].profit);
            if (i < j) SWAP(arr[i], arr[j], temp);
        } while (i < j);
        SWAP(arr[left], arr[j], temp);

        quickSort(arr, left, j - 1);
        quickSort(arr, j + 1, right);
    }
}

/* ---------------- sort jobs in order of decreasing profit ------------------*/