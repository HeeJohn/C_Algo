#include <stdio.h>

int fibonacci(int n) {
    if (n <= 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);

}
int power(int base, int exponent) {
    int half;
    if (exponent == 0)
        return 1;
    else if (exponent % 2 == 0) {
        half = power(base, exponent / 2);
        return half * half;
    }
    else {
        half = power(base, (exponent - 1) / 2);
        return base * half * half;
    }
}
int factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

int main() {
    int n;

    printf("�Ǻ���ġ�� �� ��° ���� ���ұ��? ");
    scanf_s("%d", &n);
    printf("F(%d) = %d\n", n, fibonacci(n));

    printf("���丮���� ���� ���� ���� n�� �Է��ϼ���: ");
    scanf_s("%d", &n);

    if (n < 0) {
        printf("���� ���� ���丮���� ����� �� �����ϴ�.\n");
    }
    else {
        printf("%d! = %d\n", n, factorial(n));
    }

    int base, exponent, result;
    printf("�ŵ������� �ذ� ������ �Է��ϼ��� (base, exponent): ");
    scanf_s("%d %d", &base, &exponent);

    result = power(base, exponent);
    printf("%d�� %d �ŵ����� ���: %d\n", base, exponent, result);
    return 0;
}




