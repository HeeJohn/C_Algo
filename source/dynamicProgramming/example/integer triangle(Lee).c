#define _CRT_SECURE_NO_WARNINGS/*항공소프트웨어공학과 202000974 이재혁*/
#include <stdio.h>

int arr[1001];
int memo[1001];

int max(int a, int b)
{
	return (a > b) ? a : b;
}
int main()
{
	int n;
	scanf("%d", &n);

	for (int i = 1;i <= n;i++)
		scanf("%d", &arr[i]);

	for (int i = 1;i <= n;i++)
		for (int j = 1;j <= i;j++)
			memo[i] = max(memo[i], memo[i - j] + arr[j]);	

	printf("%d", memo[n]);

	return 0;
}