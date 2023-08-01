/*
    name : minhyuck_yun
    last_edit : 23.08.01
*/

#include <stdio.h>
#include <stdlib.h>

int money_count(int n, int m);

int main(void) {
    int num, money;
    printf("화폐를 이용하여 어떠한 값을 도출 할 때 가장 적은 값을 이용한 화폐의 총 갯수를 구해주는 프로그램입니다.\n");
    printf("화폐의 갯수를 입력해주세요: ");
    scanf_s("%d", &num);

    printf("화폐로 구할 값을 입력해주세요: ");
    scanf_s("%d", &money);

    money = money_count(num, money);

    if (money == -1) {
        printf("구하려는 값이 화폐로 나타낼 수 없습니다.\n");
        exit(1);
    }
    printf("사용할 화폐의 총 갯수 = %2d", money);

    return 0;
}

int money_count(int n, int m) {
    int* money = (int*)malloc(n * sizeof(int));

    printf("화폐를 입력해주세요.\n");
    for (int i = 0; i < n; i++) {
        printf("%d번째: ", i + 1);
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