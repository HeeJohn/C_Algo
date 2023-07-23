/*
    program : math(fibonacci & power & factorial)
    name : HuiJun Seo
    last_edit: 23.07.22
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int fibonacci(int n);
int power(int base, int expo);
int power(int base, int expo);

/* ------- calculation ------*/
int main() {
    /* --- fibo ---*/
    int n;
    printf("which number do you want to know :"); scanf("%d", &n);
    int result = fibonacci(n);
    printf("The %dth Fibonacci number : %d\n", n, result);

    /* --- power ---*/
    int base, exponent;
    printf("type base number and exponent:"); scanf("%d %d", &base, &exponent);
    result = power(base, exponent);
    printf("%d^%d : %d\n", base, exponent, result);

    /* --- factorial ---*/
    printf("type the n of n! :"); scanf("%d", &n);
    result = factorial(n);
    printf("%d! : %d\n", n, result);


    return 0;
}

int fibonacci(int n)
{
    if (n <= 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}



//µ¿Àû °èÈ¹¹ý
int fibonacci(int n) {
    if (n <= 0)
        return 0;

    intfValues[n + 1];
    fValues[0] = 0;
    fValues[1] = 1;

    for (int i = 2; i <= n; i++) {
       fValues[i] =fValues[i - 1] +fValues[i - 2];
    }

    returnfValues[n];
}


int power(int base, int expo)
{
    if (expo == 0)
        return 1;

    int half = power(base, expo / 2);

    if (expo % 2 == 0)
        return half * half;
    else
        return base * half * half;
}

int factorial(int n)
{
    if (n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

