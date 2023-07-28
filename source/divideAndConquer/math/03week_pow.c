/*
	program : pow
	name : yeongjin kim
	last edited : 23.07.24
*/
#include <stdio.h>

int pow(int x, int n)
{
	if (n == 0)
		return 1;

	return x * pow(x, n - 1);
}

int main()
{
	int x, n, result;
	printf("�ذ� ������ �Է� :");
	scanf_s("%d %d", &x,&n);
	result = pow(x,n);
	printf("%d^%d is %d\n", x, n, result);

	return 0;
}