#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int tile(int* dp[], int n);
int main() {
    /* 메모이제이션 방식 */
    int *dp[30] = { 0 }; // 포인터 배열 dp 초기화
    int n;
    printf("3 x n 을 입력하세요 : ");
    scanf("%d", &n);

    printf("3 x %d를 2x1 혹은 1x2로 블록을 채울 수 있는 경우의 수는 ", n);
    if (n >= 1 && n <= 30)
        printf("%d입니다.\n\n", tile(dp, n));
    else 
        printf("0");    // 음수이거나 30보다 큰 경우는 모두 0의 경우의 수
    return 0;
}

int tile(int* dp[], int n) {
    if (n == 0) return 1;   // 초기값 초기화
    if (n == 1) return 0;   // 초기값 초기화
    if (n == 2) return 3;   // 초기값 초기화 
    if (dp[n] != 0)
        return dp[n];

    int result = tile(dp, n - 2) * 3;   // dp[n-2] * 3 부분

    for (int i = 4; i <= n; i += 2) {   // dp[n-i] * 2 부분 연속 
        result += 2 * tile(dp, n - i);
    }
    return dp[n] = result;  // 값을 포인터 배열에 저장
}