/*
	program : factorial
	name : yeongjin kim
	last edited : 23.07.24
*/
#include <stdio.h>

int factorial(int n)
{
	if (n <= 1)
		return 1;

	return n * factorial(n-1);
}

int main()
{
	int n, result;
	printf("���ϰ��� �ϴ� ���丮�� �� :");
	scanf_s("%d", &n);
	result = factorial(n);
	printf("%d factorial is %d\n",n, result);

	return 0;
}