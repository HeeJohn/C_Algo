/*
    program : fibonaci( dynamic programming )
    name : HuiJun Seo
    last_edit: 23.07.30
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 50

int memoization[MAX_SIZE];
int DP[MAX_SIZE];

int fiboTopDown(int n);
int fiboBottomUp(int n);
int fibonacciDC(int n);

int main()
{
    printf("fibonacci DC algorithm : %d\n", fiboTopDown(6));
    printf("fibonacci DP algorithm(top-down) : %d\n", fiboTopDown(6));
    printf("fibonacci DP algorithm(bottom-top) : %d\n", fiboTopDown(6));
    return 0;
}

int fiboTopDown(int n)
{
    if (n == 1 || n == 2)
        return 1;
    if (memoization[n] != 0)
        return memoization[n];
    memoization[n] = fiboTopDown(n - 1) + fiboTopDown(n - 2);

    return memoization[n];
}

int fiboBottomUp(int n)
{
    int i;
    DP[1] = DP[0] = 1; //a(1), a(2)

    for (i = 2; i <= n; i++)
        DP[i] = DP[i - 1] + DP[i - 2];

    return DP[i - 1];
}


int fibonacciDC(int n)
{
    if (n == 1 || n == 2)
        return 1;
    else
        return fibonacciDC(n - 1) + fibonacciDC(n - 2);
}