#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 128
int paper[MAX_SIZE][MAX_SIZE];
int white = 0;
int blue = 0;

bool checkpaper(int x, int y, int size) {
    int color = paper[x][y];

    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + size; j++) {
            if (paper[i][j] != color)
                return false;
        }
    }

    return true;
}
void colorpaper(int x, int y, int n) {
    if (checkpaper(x, y, n)) {
        if (paper[x][y] == 0)
            white++;
        else
            blue++;
        return;
    }
    colorpaper(x, y, n / 2);
    colorpaper(x, y + n / 2, n / 2);
    colorpaper(x + n / 2, y, n / 2);
    colorpaper(x + n / 2, y + n / 2, n / 2);
}
void create(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            paper[i][j] = rand() % 2;
            printf("%d\t", paper[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("색종이 크기 N을 입력하세요 (1 <= N <= 128):");
    scanf_s("%d", &n);
    create(n);
    colorpaper(0, 0, n);
    printf("흰색 색종이 개수: %d\n푸른색 색종이 개수: %d", white, blue);
}
