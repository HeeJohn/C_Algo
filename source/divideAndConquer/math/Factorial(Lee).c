#define _CRT_SECURE_NO_WARNINGS/*�װ�����Ʈ������а� 202000974 ������*/
#include <stdio.h>
long long int factorial(int n, long long int total)
{ /* ���丮�� �Լ�(�������) */
	if (n == 1)
		return total;
	return factorial(n - 1, n * total);
}
int main()
{
	int number;

	printf("���ڸ� �Է��ϼ���-> ");
	scanf("%d", &number);

	printf("%d! = %lld", number, factorial(number, 1));

	return 0;
}