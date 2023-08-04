#include <stdio.h>
#define MAX(a,b) a>b?a:b

int dp[301];
int stair[301];

int main() {
    int n;
    scanf_s("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf_s("%d", &stair[i]);
    }

    //�ʱⰪ �������ֱ�
    dp[0] = 0;
    dp[1] = stair[1];
    dp[2] = stair[1] + stair[2];

    //�ִ� �� ���ϱ�
    for (int i = 3; i <= n; i++) {
        dp[i] = stair[i] + (MAX(dp[i - 2], stair[i - 1] + dp[i - 3]));
    }

    //��� ���
    printf("%d\n", dp[n]);
    return 0;
}