/*
    program: cutting rod
    name: HuiJun Seo
    last_edit: 23.07.30
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // For dynamic memory allocation
#define MALLOC(p,s) \
    if(!((p)=malloc(s))) { \
       fprintf(stderr, "insufficient memory space\n"); \
        exit(EXIT_FAILURE); \
}
#define COMPARE(a,b) ( ((a > b)) ? (a) : (b) )

int cutRod(int price[], int n);

int main()
{
    int arr[] = { 1, 5, 8, 9 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Maximum Obtainable Value is %d\n", cutRod(arr, size));
    return 0;
}



int cutRod(int price[], int n)
{
    int* val; MALLOC(val, (n + 1) * sizeof(int)); // == val[n+1] // including val[0]

    val[0] = 0; // length of 0, which is none

    // Build the table val[] in bottom up manner and return the last entry
    // from the table
    for (int i = 1; i <= n; i++)
    {
        int max_val = -1; // initializing
        for (int j = 0; j < i; j++)
            max_val = COMPARE(max_val, price[j] + val[i - j - 1]); // compare to find biggest price
        val[i] = max_val; // save the biggest price for each length i
    }

    int result = val[n];
    free(val); // Free the dynamically allocated memory
    return result;
}
