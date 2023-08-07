/*
    program : fibonacci (dynamic programming)
    name : yeongjin kim
    last edited : 23.07.24
*/
#include <stdio.h>

int memo[100]; //메모이제이션 공간. 전역 변수이므로 0으로 초기화

int fibonacci(unsigned int n)
{
    if (n <= 1) //0번째, 1번째 피보나치 수
        return n;
    if (memo[n] != 0) //메모가 있는지 확인(0으로 초기화되었으므로 0이 아니라면 메모가 쓰인 것임)
        return memo[n]; //메모 리턴
    memo[n] = fibonacci(n - 1) + fibonacci(n - 2); //작은 문제로 분할
    return memo[n];
}

int main()
{
    int n, result;
    printf("구하고 싶은 피보나치 수열 : ");
    scanf_s("%d", &n);

    result = fibonacci(n);
    printf("%d 번째 피보나치 수열 : %d\n", n, result);

    return 0;
}