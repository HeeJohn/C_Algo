#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

float power(float base, int expon);	// 밑, 지수  

int main() {
	float base;
	int expon;

	printf("밑을 입력하세요. ");
	scanf("%f", &base);
	printf("지수를 입력하세요. ");
	scanf("%d", &expon);
	float result;
	result = power(base, expon);

	printf("%.2f^%d는 %.2f입니다.", base, expon, result);
}

float power(float base, int expon) {
	if (expon == 0) {
		return 1.0;
	}
	else if (expon < 0) {
		return 1.0 / power(base, -expon);
	}
	else {
		return base * power(base, expon - 1);
	}
}