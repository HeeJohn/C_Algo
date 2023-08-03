#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 16

int n;
int b_row[MAX_SIZE];
int b_col[MAX_SIZE];

int chack(int row, int col);    // n-quuen을 해결해주는 재귀함수 
void scan_print(void);          // 입력과 출력을 해주는 함수 

int main() {
    scan_print();
}

int chack(int row, int col) {   // 열, 행

    /* 퀸의 위치를 기억해준다. */
    b_row[row] = row;
    b_col[row] = col;

    for (int i = 0; i < row; i++) {
        /* 백트래킹(가지치기) */
        if (row == b_row[i]) // 가로 가지치기
            return 0;
        if (col == b_col[i]) // 세로 가지치기 
            return 0;
        if (abs(col - b_col[i]) == abs(row - b_row[i]))   // 대각 가지치기
            return 0;
    }

    if (row == n - 1) {
        /* 정상적으로 n * n의 체스판 끝에 도착하면 1을 반환 */
        return 1;
    }



    int q = 0;
    for (int i = 0; i < n; i++) {
        /* 재귀 함수 */
        q += chack(row + 1, i);
    }
    return q;
}

void scan_print(void) {
    scanf("%d", &n);
    if (n < 1 || n > 16) {
        fprintf(stderr, "n은 1 ~ 16까지만 허용합니다. ");
        exit(EXIT_FAILURE);
    }
    int q = 0;
    for (int i = 0; i < n; i++) {
        q += chack(0, i);
    }
    printf("%d\n", q);
}