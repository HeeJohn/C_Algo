#include <stdio.h>
#define UNKNOWN -1
#define MAX_N 1000
int memo[MAX_N];

void initialize() {
    for (int i = 0;i < MAX_N;i++) {
        memo[i] = UNKNOWN;
    }
}
// 피보나치 수열을 메모이제이션하기 위한 함수
int fibonacci(int n) {
    if (n==0 || n == 1) {
        return n;
    }

    // 이미 계산한 값이라면 메모리제이션된 결과를 반환
    if (memo[n] != UNKNOWN) {
        return memo[n];
    }
    // 아직 계산하지 않은 경우, 재귀적으로 피보나치 수열 값을 계산하고 메모리에 저장
    memo[n] = fibonacci(n - 1) + fibonacci(n - 2);

    return memo[n];
}

int main() {
    int n;
    printf("몇 번째 피보나치 수열 값을 계산하시겠습니까? ");
    scanf_s("%d", &n);
    initialize();
    int result = fibonacci(n);

    printf("피보나치 수열의 %d번째 값은 %d입니다.\n", n, result);
    return 0;
}
