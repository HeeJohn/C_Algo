/*
* program: 승자 예측하기
* name: 이창범
* date: 2023.07.18
*/
#include <stdio.h>
#include <stdbool.h>
#include<stdlib.h>

bool TheWinner(int nums[], int start, int end, int sum1, int sum2, bool isPlayer1) {
    if (start > end) {
        return sum1 >= sum2;
    }

    if (isPlayer1) {
        return !TheWinner(nums, start + 1, end, sum1 + nums[start], sum2, !isPlayer1) ||
            !TheWinner(nums, start, end - 1, sum1 + nums[end], sum2, !isPlayer1);
    }
    else {
        return !TheWinner(nums, start + 1, end, sum1, sum2 + nums[start], !isPlayer1) ||
            !TheWinner(nums, start, end - 1, sum1, sum2 + nums[end], !isPlayer1);
    }
}

int main() {
    int n;
    printf("숫자의 개수를 입력하세요: ");
    scanf_s("%d", &n);

    int* nums = (int*)malloc(sizeof(int) * n);
    printf("숫자를 입력하세요: ");
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &nums[i]);
    }

    bool isPlayer1 = true;
    bool result = TheWinner(nums, 0, n - 1, 0, 0, isPlayer1);

    if (result) {
        printf("Player 1이 승리.\n");
    }
    else {
        printf("Player 2가 승리.\n");
    }

    return 0;
}
