/*
    name : minhyuck_yun
    last_edit : 23.08.01
*/

#include <stdio.h>
#include <stdlib.h>

int money_count(int n, int m);

int main(void) {
    int num, money;
    printf("ȭ�� �̿��Ͽ� ��� ���� ���� �� �� ���� ���� ���� �̿��� ȭ���� �� ������ �����ִ� ���α׷��Դϴ�.\n");
    printf("ȭ���� ������ �Է����ּ���: ");
    scanf_s("%d", &num);

    printf("ȭ��� ���� ���� �Է����ּ���: ");
    scanf_s("%d", &money);

    money = money_count(num, money);

    if (money == -1) {
        printf("���Ϸ��� ���� ȭ��� ��Ÿ�� �� �����ϴ�.\n");
        exit(1);
    }
    printf("����� ȭ���� �� ���� = %2d", money);

    return 0;
}

int money_count(int n, int m) {
    int* money = (int*)malloc(n * sizeof(int));

    printf("ȭ�� �Է����ּ���.\n");
    for (int i = 0; i < n; i++) {
        printf("%d��°: ", i + 1);
        scanf_s("%d", &money[i]);
    }

    int* dp = (int*)malloc((m + 1) * sizeof(int));
    for (int i = 0; i <= m; i++) {
        dp[i] = 100000;
    }

    dp[0] = 0;

    for (int i = 0; i < n; i++)
        for (int j = money[i]; j <= m; j++)
            if (dp[j - money[i]] != 100000)
                if (dp[j] > dp[j - money[i]] + 1)
                    dp[j] = dp[j - money[i]] + 1;

    if (dp[m] == 100000)
        return -1;
    else
        return dp[m];
}