#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int fibonacci_DC(int n, int* count);  // DC 분할정복 
int fibonacci_MZ(int n, int fibo[], int* count);  // DP (동적 계획법)
int fibonacci_BU(int n, int* count); // 바텀업 방식 (Bottom-Up)

int main() {
    int count = 0;
    int fibo[100] = { 0 };
    int fi, result;

    printf("피보나치 수를 입력하세요. ");
    scanf("%d", &fi);

    // 분할정복 방식
    result = fibonacci_DC(fi, &count);
    printf("분할정복(CP)\n");
    printf("%d번째 피보나치 수 : %d\n함수를 재귀한 횟수 : %d\n\n", fi,result, count);

    // 동적 계획법(메모이제이션 방식)
    count = 0;  // 초기화
    result=fibonacci_MZ(fi, fibo, &count);
    printf("메모이제이션(MZ)\n");
    printf("%d번째 피보나치 수 : %d\n함수를 재귀한 횟수 : %d\n\n", fi,result, count);

    // 동적 계획법(바텀업 방식)
    count = 2;
    result = fibonacci_BU(fi, &count);
    printf("바텀업 방식(BU)\n");
    printf("%d번째 피보나치 수 : %d\n반복횟수: %d\n\n", fi,result , count);

    return 0;
}


int fibonacci_DC(int n, int* count) {
    (*count)++;
    if (n == 1 || n == 2)
        return 1;
    else {
        return fibonacci_DC(n - 1, count) + fibonacci_DC(n - 2, count);
    }
}

int fibonacci_MZ(int n, int fibo[], int* count) {
    (*count)++;
    if (n == 1 || n == 2)
        return 1;
    else if (fibo[n] != 0)
        return fibo[n];
    else {
        return fibo[n] = fibonacci_MZ(n - 1, fibo, count) + fibonacci_MZ(n - 2, fibo, count);
    }
}

int fibonacci_BU(int n, int* count) {
    int fibo[100] = { 0 };
    fibo[1] = fibo[2] = 1;

    for (int i = 3; i <= n; i++) {
        (*count)++;
        fibo[i] = fibo[i - 1] + fibo[i - 2];
    }

    return fibo[n];
}