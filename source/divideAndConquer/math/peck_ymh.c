/*
    program : peck_ymh
    name : minhyuck yun
    last_edit : 23.07.23
*/

// 팩토리얼
#include <stdio.h>

// 함수 원형 선언
int peck(int num);

int main()
{
    int num, x;

    // 사용자로부터 값을 입력받습니다.
    printf("어떤 수를 팩토리얼할까요?\n->");
    scanf_s("%d", &num);

    // peck 함수를 호출하여 num의 팩토리얼 값을 계산합니다.
    x = peck(num);

    // 계산한 값을 출력합니다.
    printf("계산한 값\n=%2d", x);

    return 0;
}

/* 재귀 함수를 사용하여 정수 num의 팩토리얼을 계산하는 함수 */
int peck(int num)
{
    if (num == 0)
        return 1; // 팩토리얼의 base case: 0!은 항상 1이므로 1을 반환합니다.
    else
    {
        // 재귀적으로 (num - 1)의 팩토리얼 값을 계산하고, num과 곱하여 num의 팩토리얼 값을 구합니다.
        return num * peck(num - 1);
    }
}