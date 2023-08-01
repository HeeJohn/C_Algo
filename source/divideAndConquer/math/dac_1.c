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

    printf("피보나치를 몇 번째 수로 구할까요? ");
    scanf_s("%d", &n);
    printf("F(%d) = %d\n", n, fibonacci(n));

    printf("팩토리얼을 구할 양의 정수 n을 입력하세요: ");
    scanf_s("%d", &n);

    if (n < 0) {
        printf("음수 값은 팩토리얼을 계산할 수 없습니다.\n");
    }
    else {
        printf("%d! = %d\n", n, factorial(n));
    }

    int base, exponent, result;
    printf("거듭제곱할 밑과 지수를 입력하세요 (base, exponent): ");
    scanf_s("%d %d", &base, &exponent);

    result = power(base, exponent);
    printf("%d의 %d 거듭제곱 결과: %d\n", base, exponent, result);
    return 0;
}




