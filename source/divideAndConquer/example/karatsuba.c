#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int karatsuba(int num1, int num2) {
    if (num1 < 10 || num2 < 10) //single digit, end condition
        return num1 * num2;

    int m;
    m = fmin((int)(log10(num1) + 1), (int)(log10(num2) + 1));
    m /= 2;

    int high1, low1;
    high1 = num1 / pow(10, m);
    low1 = num1 % (int)pow(10, m);
    int high2, low2;
    high2 = num2 / pow(10, m);
    low2 = num2 % (int)pow(10, m);

    int a0 = karatsuba(low1, low2);
    int a1 = karatsuba((low1 + high1), (low2 + high2));
    int a2 = karatsuba(high1, high2);

    return (a2 * pow(10, (m * 2)) + ((a1 - a2 - a0) * pow(10, m)) + a0);
}

int main() {
    int A, B;
    printf("put A, B for mulitiply = ");
    scanf("%d %d", &A, &B);
    printf("%d\n", karatsuba(A, B));
    return 0;
}
