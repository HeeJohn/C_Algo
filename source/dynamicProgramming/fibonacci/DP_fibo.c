#include <stdio.h>
#define UNKNOWN -1
#define MAX_N 1000
int memo[MAX_N];

void initialize() {
    for (int i = 0;i < MAX_N;i++) {
        memo[i] = UNKNOWN;
    }
}
// �Ǻ���ġ ������ �޸������̼��ϱ� ���� �Լ�
int fibonacci(int n) {
    if (n==0 || n == 1) {
        return n;
    }

    // �̹� ����� ���̶�� �޸����̼ǵ� ����� ��ȯ
    if (memo[n] != UNKNOWN) {
        return memo[n];
    }
    // ���� ������� ���� ���, ��������� �Ǻ���ġ ���� ���� ����ϰ� �޸𸮿� ����
    memo[n] = fibonacci(n - 1) + fibonacci(n - 2);

    return memo[n];
}

int main() {
    int n;
    printf("�� ��° �Ǻ���ġ ���� ���� ����Ͻðڽ��ϱ�? ");
    scanf_s("%d", &n);
    initialize();
    int result = fibonacci(n);

    printf("�Ǻ���ġ ������ %d��° ���� %d�Դϴ�.\n", n, result);
    return 0;
}
