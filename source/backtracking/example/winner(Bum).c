/*
* program: ���� �����ϱ�
* name: ��â��
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
    printf("������ ������ �Է��ϼ���: ");
    scanf_s("%d", &n);

    int* nums = (int*)malloc(sizeof(int) * n);
    printf("���ڸ� �Է��ϼ���: ");
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &nums[i]);
    }

    bool isPlayer1 = true;
    bool result = TheWinner(nums, 0, n - 1, 0, 0, isPlayer1);

    if (result) {
        printf("Player 1�� �¸�.\n");
    }
    else {
        printf("Player 2�� �¸�.\n");
    }

    return 0;
}
