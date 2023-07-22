#define _CRT_SECURE_NO_WARNINGS/*항공소프트웨어공학과 202000974 이재혁*/
#include <stdio.h>
long long int factorial(int n, long long int total)
{ /* 팩토리얼 함수(꼬리재귀) */
	if (n == 1)
		return total;
	return factorial(n - 1, n * total);
}
int main()
{
	int number;

	printf("숫자를 입력하세요-> ");
	scanf("%d", &number);

	printf("%d! = %lld", number, factorial(number, 1));

	return 0;
}