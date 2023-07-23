/*
    program : guje_ymh
    name : minhyuck yun
    last_edit : 23.07.23
*/

//거듭제곱
#include <stdio.h>

// 함수 원형 선언
int je(int num, int n);

int main()
{
    int num, n, x;

    // 사용자로부터 값을 입력받습니다.
    printf("어떤 수를 제곱제곱할까요?\n->");
    scanf_s("%d", &num);
    printf("몇 제곱할까요?\n->");
    scanf_s("%d", &n);

    // je 함수를 호출하여 num의 n 제곱 값을 계산합니다.
    x = je(num, n);

    // 계산한 값을 출력합니다.
    printf("계산한 값\n=%2d", x);

    return 0;
}

/* 재귀 함수를 사용하여 정수 num을 n 제곱으로 계산하는 함수 */
int je(int num, int n)
{
    if (n == 0)
        return 1; // n이 0인 경우, num의 0 제곱은 항상 1이므로 1을 반환합니다.
    else
    {
        // 재귀적으로 num의 n-1 제곱 값을 계산하고, num과 곱하여 num의 n 제곱 값을 구합니다.
        return num * je(num, n - 1);
    }
}