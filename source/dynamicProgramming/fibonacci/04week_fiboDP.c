/*
    program : fibonacci (dynamic programming)
    name : yeongjin kim
    last edited : 23.07.24
*/
#include <stdio.h>

int memo[100]; //�޸������̼� ����. ���� �����̹Ƿ� 0���� �ʱ�ȭ

int fibonacci(unsigned int n)
{
    if (n <= 1) //0��°, 1��° �Ǻ���ġ ��
        return n;
    if (memo[n] != 0) //�޸� �ִ��� Ȯ��(0���� �ʱ�ȭ�Ǿ����Ƿ� 0�� �ƴ϶�� �޸� ���� ����)
        return memo[n]; //�޸� ����
    memo[n] = fibonacci(n - 1) + fibonacci(n - 2); //���� ������ ����
    return memo[n];
}

int main()
{
    int n, result;
    printf("���ϰ� ���� �Ǻ���ġ ���� : ");
    scanf_s("%d", &n);

    result = fibonacci(n);
    printf("%d ��° �Ǻ���ġ ���� : %d\n", n, result);

    return 0;
}