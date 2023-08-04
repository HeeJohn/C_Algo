/*#include <stdio.h>
int memo[100];  // 메모이제이션을 위한 배열(중복된 값을 계산하지 않기 위해 사용)
int fibo(int n)
{ // 피보나치 계산 함수 

	if (n == 1 || n == 2)                                // 1항, 2항일 때 1 반환
		return 1;
	else if (memo[n] != 0)                                // memo에 값이 있을 때(이미 계산한 적이 있다면)
		return memo[n];
	else                                                 // 1항, 2항이 아니고, memo에 값이 없을 때                            
		return memo[n] = (fibo(n - 1) + fibo(n - 2));
}
int main()
{
	int n;
	scanf_s("%d", &n);
	printf("%d", fibo(n));
}*/