#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Added for random number generation
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
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

void printJobScheduling(Job arr[], int n);
void quickSort(Job arr[], int left, int right);
void printSlot(Job arr[], bool slot[], int result[], int n);
int findMaxDeadline(Job arr[], int n);
void printArray(Job arr[], int n);

// Driver's code
int main()
{
    srand(time(0)); // Seed the random number generator with current time


    int n;
    printf("Enter the number of jobs: ");
    scanf("%d", &n);

    Job* arr;
    MALLOC(arr, n * sizeof(Job));

    // Generate random profit and deadline for each job
    for (int i = 0; i < n; i++) {
        arr[i].id = 'a' + i; // Assign a unique id to each job (for better visualization)
        arr[i].profit = rand() % 100 + 1; // Random profit between 1 and 100
        arr[i].dead = rand() % 10 + 1;    // Random deadline between 1 and 10
    }

    printf("--Generated Random Job Details--\n");
    printArray(arr, n);

    quickSort(arr, 0, n - 1); // Sort all jobs according to decreasing order of profit

    printf("\n--Sorted as decreasing order of profit--\n");
    printArray(arr, n);

    printf("\n\nFollowing is maximum profit sequence of jobs\n");
    printJobScheduling(arr, n); // Function call

    free(arr); // Free the allocated memory for the array

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
}

void printSlot(Job arr[], bool slot[], int result[], int n)
{
    // Print the result
    int totalProfit = 0;
    for (int i = 0; i < n; i++) {
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
    int* result;
    MALLOC(result, n); // To store result (Sequence of jobs)
    bool* slot;
    MALLOC(slot, n); // To keep track of free time slots

    int max = findMaxDeadline(arr, n);
    printf("max deadline : %d\n", max);

    // Initialize all slots to be free
    for (int i = 0; i < n; i++)
        slot[i] = false;

    int maxDeadline = 0;
    // Iterate through all given jobs
    for (int i = 0; i < n; i++) {
        int j = arr[i].dead - 1;
        if (slot[j] == false && maxDeadline + arr[i].dead <= max) {
            result[j] = i; // Add this job to result
            slot[j] = true; // Make this slot occupied
            maxDeadline += arr[i].dead;
        }
    }
    printSlot(arr, slot, result, n); // print the best slot
}

/* ----------------job scheduling ------------------*/

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
