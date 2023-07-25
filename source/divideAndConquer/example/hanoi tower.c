#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void hanoi(int n, char start, char middle, char end);

int main() {
    int num;
    printf("원판의 개수를 입력하세요: ");
    scanf("%d", &num);

    hanoi(num, 'A', 'B', 'C');

    return 0;
}

void hanoi(int n, char start, char middle, char end) {
    /* 최종 탑의 목적지는 end이다. */
    if (n == 1) {
        printf("원판 1을(를) %c에서 %c로 옮깁니다.\n", start, end);
        return;
    }

    hanoi(n - 1, start, end, middle);
    printf("원판 %d을(를) %c에서 %c로 옮깁니다.\n", n, start, end);
    hanoi(n - 1, middle, start, end);
}