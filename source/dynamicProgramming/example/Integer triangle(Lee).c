#define _CRT_SECURE_NO_WARNINGS/*항공소프트웨어공학과 202000974 이재혁*/
#include <stdio.h>

int arr[501][501];             // 정수값 저장하는 삼각형 배열
int max(int a, int b)
{
	return (a > b) ? a : b;
}
int main()
{
	int n;

	scanf("%d", &n);

	for (int i = 0;i < n;i++)
		for (int j = 0;j < i + 1;j++)
			scanf("%d", &arr[i][j]);

	for (int i = n - 1;i >= 1;i--)
		for (int j = 0;j < i;j++)
			arr[i - 1][j] += max(arr[i][j], arr[i][j + 1]);     /* 아래에서부터 시작해 두 값을 비교 후 큰 값을
					                                       위의 숫자에 더해간다. 그러면 마지막에는 꼭대기에 한자리가 남는데
	                						       이곳에 더해진 수가 최댓값이 된다. */

	printf("%d", arr[0][0]);

	return 0;
}
