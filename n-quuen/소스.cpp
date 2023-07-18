#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 16

int n;
int b_row[MAX_SIZE];
int b_col[MAX_SIZE];

int chack(int row, int col);    // n-quuen�� �ذ����ִ� ����Լ� 
void scan_print(void);          // �Է°� ����� ���ִ� �Լ� 

int main() {
    scan_print();
}

int chack(int row, int col) {   // ��, ��

    /* ���� ��ġ�� ������ش�. */
    b_row[row] = row;
    b_col[row] = col;

    for (int i = 0; i < row; i++) {
        /* ��Ʈ��ŷ(����ġ��) */
        if (row == b_row[i]) // ���� ����ġ��
            return 0;
        if (col == b_col[i]) // ���� ����ġ�� 
            return 0;
        if (abs(col - b_col[i]) == abs(row - b_row[i]))   // �밢 ����ġ��
            return 0;
    }

    if (row == n - 1) {
        /* ���������� n * n�� ü���� ���� �����ϸ� 1�� ��ȯ */
        return 1;
    }



    int q = 0;
    for (int i = 0; i < n; i++) {
        /* ��� �Լ� */
        q += chack(row + 1, i);
    }
    return q;
}

void scan_print(void) {
    scanf("%d", &n);
    if (n < 1 || n > 16) {
        fprintf(stderr, "n�� 1 ~ 16������ ����մϴ�. ");
        exit(EXIT_FAILURE);
    }
    int q = 0;
    for (int i = 0; i < n; i++) {
        q += chack(0, i);
    }
    printf("%d\n", q);
}