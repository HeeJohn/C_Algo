/*
    program : fibonacci
    name : yeongjin kim
    last edited : 23.07.24
*/
#include <stdio.h>

int fibonacci(int n) 
{
    if (n <= 1) 
    {
        return n;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    int n,result;
    printf("생성시키고자 하는 수열의 개수 입력 :");
    scanf_s("%d", &n);
    result = fibonacci(n);
    printf("Last value is %d\n", result);

    return 0;
}