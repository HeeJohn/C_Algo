/*
    program : plusjung_ymh
    name : minhyuck yun
    last_edit : 23.07.23
*/

//�պ�����
#include <stdio.h>

int a[10] = { 26, 5, 37, 1, 61, 11, 59, 15, 48, 19 };
int temp[10];

void MergeSort(int l, int r);

int main()
{
    MergeSort(0, 9); // �迭�� �պ� �����մϴ�.

    // ���ĵ� �迭�� ����մϴ�.
    for (int i = 0; i < 10; i++)
        printf("%d ", a[i]);
}

void MergeSort(int l, int r)
{
    if (l >= r) return; // �迭�� ũ�Ⱑ 1 ������ ���, ������ �ʿ䰡 �����Ƿ� �Լ��� ������ �����մϴ�.

    int m = (l + r) >> 1; // �迭�� �߰� �������� �����ϱ� ���� �߰� �ε��� m�� ����մϴ�.

    MergeSort(l, m); // ���� �κ� �迭�� ��������� �պ� �����մϴ�.
    MergeSort(m + 1, r); // ������ �κ� �迭�� ��������� �պ� �����մϴ�.

    // ���ҵ� �� �κ� �迭�� �պ��մϴ�.
    int p1 = l, p2 = m + 1, p3 = l;
    while (p1 <= m && p2 <= r)
        temp[p3++] = (a[p1] < a[p2]) ? a[p1++] : a[p2++]; // �� �κ� �迭�� ���Ҹ� ���Ͽ� ���� ���� temp �迭�� �����մϴ�.
    while (p1 <= m)
        temp[p3++] = a[p1++]; // ���� �κ� �迭�� ���� ���, ���� ���ҵ��� temp �迭�� �����մϴ�.
    while (p2 <= r)
        temp[p3++] = a[p2++]; // ������ �κ� �迭�� ���� ���, ���� ���ҵ��� temp �迭�� �����մϴ�.

     // ���ĵ� ����� ���� �迭�� �����մϴ�.
    for (int i = l; i <= r; i++)
        a[i] = temp[i];
}