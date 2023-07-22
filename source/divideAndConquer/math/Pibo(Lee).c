#define _CRT_SECURE_NO_WARNINGS/*항공소프트웨어공학과 202000974 이재혁*/
#include <stdio.h>
double memo[201];  // 메모제이션을 위한 배열(중복된 값을 계산하지 않기 위해 사용)
double pibo(int n)
{ /* 피보나치 계산 함수 */

	if (n == 1 || n == 2)                                  // 1항, 2항일 때
		return 1;
	else if (memo[n] != 0)                               // memo에 값이 있을 때(이미 계산한 적이 있다면)
		return memo[n];
	else                                                // 1항, 2항이 아니고, memo에 값이 없을 때                            
		return memo[n] = (pibo(n - 1) + pibo(n - 2));
}
int main()
{
	int n;

	scanf("%d", &n);
	printf("%lf", pibo(n));


}