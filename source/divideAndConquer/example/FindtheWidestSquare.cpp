#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX 100

int histo[MAX];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int divide(int left, int right) {
    if (left == right)
        return histo[left];

    int mid = (left + right) / 2;//중앙 인덱스
    int leftp = mid;//왼쪽 포인터(위치)
    int rightp = mid;//오른쪽 포인터(위치)
    int height = histo[mid];//중앙 직사각형의 높이
    int vol = max(divide(left, mid), divide(mid + 1, right));//분할한다

    while (left < leftp || rightp < right) {
        if (left < leftp && (rightp == right || histo[leftp - 1] > histo[rightp + 1])) { 
            leftp--;//왼쪽 위치의 높이가 더 크다면 왼쪽포인터를 왼쪽으로 한칸 이동 
            height = min(height, histo[leftp]);//현재 높이와 왼쪽 포인터 높이중 낮은 높이 저장
        }
        else {
            rightp++;//오른쪽 위치의 높이가 더 크다면 ***
            height = min(height, histo[rightp]);
        }
        vol = max(vol, height * (rightp - leftp + 1));//분할 한것중에서 찾은 직사각형이 넓은지 합친것중에서 가장넓은 직사각형이 넓은지 확인
    }
    return vol;
}

int main(void) {
    int n;
    scanf_s("%d", &n);

        for (int i = 0; i < n; i++) {
            scanf_s("%d", &histo[i]);
        }
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < histo[i];j++)
                printf("■");
            printf("\n");
        }
        printf("%d\n", divide(0, n - 1));
        scanf_s("%d", &n);


    return 0;
}
