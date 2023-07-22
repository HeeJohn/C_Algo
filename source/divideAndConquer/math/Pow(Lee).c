#define _CRT_SECURE_NO_WARNINGS/*항공소프트웨어공학과 202000974 이재혁*/
#include <stdio.h>
long long int pow(int x, int n)          // x는 밑, n은 지수 
{ /* 거듭제곱 함수 */
	long long int ret = 1;   // 결과값

	while (n)	            // 지수가 존재하는 동안 반복
	{
		if (n & 1)        // LSB가 1이라면
			ret *= x;

		n >>= 1;        // 오른쪽 시프트 연산
		x *= x;        // 밑은 제곱해준다.(밑의 값이 각 자리의 제곱으로 따라감)
	}

	return ret;
}

int main()
{
	int base, exp, ret;

	printf("밑과 지수를 입력하세요 -> ");
	scanf("%d %d", &base, &exp);

	printf("%d ^ %d = %lld\n", base, exp, pow(base, exp));
	return 0;
}