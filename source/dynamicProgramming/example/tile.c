#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int tile(int* dp[], int n);
int main() {
    /* �޸������̼� ��� */
    int *dp[30] = { 0 }; // ������ �迭 dp �ʱ�ȭ
    int n;
    printf("3 x n �� �Է��ϼ��� : ");
    scanf("%d", &n);

    printf("3 x %d�� 2x1 Ȥ�� 1x2�� ����� ä�� �� �ִ� ����� ���� ", n);
    if (n >= 1 && n <= 30)
        printf("%d�Դϴ�.\n\n", tile(dp, n));
    else 
        printf("0");    // �����̰ų� 30���� ū ���� ��� 0�� ����� ��
    return 0;
}

int tile(int* dp[], int n) {
    if (n == 0) return 1;   // �ʱⰪ �ʱ�ȭ
    if (n == 1) return 0;   // �ʱⰪ �ʱ�ȭ
    if (n == 2) return 3;   // �ʱⰪ �ʱ�ȭ 
    if (dp[n] != 0)
        return dp[n];

    int result = tile(dp, n - 2) * 3;   // dp[n-2] * 3 �κ�

    for (int i = 4; i <= n; i += 2) {   // dp[n-i] * 2 �κ� ���� 
        result += 2 * tile(dp, n - i);
    }
    return dp[n] = result;  // ���� ������ �迭�� ����
}