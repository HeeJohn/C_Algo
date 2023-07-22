#define _CRT_SECURE_NO_WARNINGS/*항공소프트웨어공학과 202000974 이재혁*/
#include <stdio.h>
long long f(long long x)
{
	if (x == 1)
		return 0;
	long long i;
	for (i = 1;i * 2 < x;i *= 2);    // x를 넘지 않는 2의 거듭제곱 찾기
	return !f(x - i);           // 뒤집히기 전 문자 재귀(not을 통해 뒤집힌 후 문자 얻기)
}
int main()
{
	long long n;
	scanf("%lld", &n);

	printf("%lld", f(n));

	return 0;
}