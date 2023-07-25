#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void hanoi(int n, char start, char middle, char end);

int main() {
    int num;
    printf("������ ������ �Է��ϼ���: ");
    scanf("%d", &num);

    hanoi(num, 'A', 'B', 'C');

    return 0;
}

void hanoi(int n, char start, char middle, char end) {
    /* ���� ž�� �������� end�̴�. */
    if (n == 1) {
        printf("���� 1��(��) %c���� %c�� �ű�ϴ�.\n", start, end);
        return;
    }

    hanoi(n - 1, start, end, middle);
    printf("���� %d��(��) %c���� %c�� �ű�ϴ�.\n", n, start, end);
    hanoi(n - 1, middle, start, end);
}