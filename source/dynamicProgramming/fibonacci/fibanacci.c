#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int fibonacci_DC(int n, int* count);  // DC �������� 
int fibonacci_MZ(int n, int fibo[], int* count);  // DP (���� ��ȹ��)
int fibonacci_BU(int n, int* count); // ���Ҿ� ��� (Bottom-Up)

int main() {
    int count = 0;
    int fibo[100] = { 0 };
    int fi, result;

    printf("�Ǻ���ġ ���� �Է��ϼ���. ");
    scanf("%d", &fi);

    // �������� ���
    result = fibonacci_DC(fi, &count);
    printf("��������(CP)\n");
    printf("%d��° �Ǻ���ġ �� : %d\n�Լ��� ����� Ƚ�� : %d\n\n", fi,result, count);

    // ���� ��ȹ��(�޸������̼� ���)
    count = 0;  // �ʱ�ȭ
    result=fibonacci_MZ(fi, fibo, &count);
    printf("�޸������̼�(MZ)\n");
    printf("%d��° �Ǻ���ġ �� : %d\n�Լ��� ����� Ƚ�� : %d\n\n", fi,result, count);

    // ���� ��ȹ��(���Ҿ� ���)
    count = 2;
    result = fibonacci_BU(fi, &count);
    printf("���Ҿ� ���(BU)\n");
    printf("%d��° �Ǻ���ġ �� : %d\n�ݺ�Ƚ��: %d\n\n", fi,result , count);

    return 0;
}


int fibonacci_DC(int n, int* count) {
    (*count)++;
    if (n == 1 || n == 2)
        return 1;
    else {
        return fibonacci_DC(n - 1, count) + fibonacci_DC(n - 2, count);
    }
}

int fibonacci_MZ(int n, int fibo[], int* count) {
    (*count)++;
    if (n == 1 || n == 2)
        return 1;
    else if (fibo[n] != 0)
        return fibo[n];
    else {
        return fibo[n] = fibonacci_MZ(n - 1, fibo, count) + fibonacci_MZ(n - 2, fibo, count);
    }
}

int fibonacci_BU(int n, int* count) {
    int fibo[100] = { 0 };
    fibo[1] = fibo[2] = 1;

    for (int i = 3; i <= n; i++) {
        (*count)++;
        fibo[i] = fibo[i - 1] + fibo[i - 2];
    }

    return fibo[n];
}