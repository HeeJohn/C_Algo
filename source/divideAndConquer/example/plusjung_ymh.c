/*
    program : plusjung_ymh
    name : minhyuck yun
    last_edit : 23.07.23
*/

//합병정렬
#include <stdio.h>

int a[10] = { 26, 5, 37, 1, 61, 11, 59, 15, 48, 19 };
int temp[10];

void MergeSort(int l, int r);

int main()
{
    MergeSort(0, 9); // 배열을 합병 정렬합니다.

    // 정렬된 배열을 출력합니다.
    for (int i = 0; i < 10; i++)
        printf("%d ", a[i]);
}

void MergeSort(int l, int r)
{
    if (l >= r) return; // 배열의 크기가 1 이하인 경우, 정렬할 필요가 없으므로 함수를 빠르게 종료합니다.

    int m = (l + r) >> 1; // 배열을 중간 지점에서 분할하기 위해 중간 인덱스 m을 계산합니다.

    MergeSort(l, m); // 왼쪽 부분 배열을 재귀적으로 합병 정렬합니다.
    MergeSort(m + 1, r); // 오른쪽 부분 배열을 재귀적으로 합병 정렬합니다.

    // 분할된 두 부분 배열을 합병합니다.
    int p1 = l, p2 = m + 1, p3 = l;
    while (p1 <= m && p2 <= r)
        temp[p3++] = (a[p1] < a[p2]) ? a[p1++] : a[p2++]; // 두 부분 배열의 원소를 비교하여 작은 값을 temp 배열에 저장합니다.
    while (p1 <= m)
        temp[p3++] = a[p1++]; // 왼쪽 부분 배열이 남은 경우, 남은 원소들을 temp 배열에 복사합니다.
    while (p2 <= r)
        temp[p3++] = a[p2++]; // 오른쪽 부분 배열이 남은 경우, 남은 원소들을 temp 배열에 복사합니다.

     // 정렬된 결과를 원래 배열에 복사합니다.
    for (int i = l; i <= r; i++)
        a[i] = temp[i];
}