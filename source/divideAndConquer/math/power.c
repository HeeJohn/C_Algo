#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

float power(float base, int expon);	// ��, ����  

int main() {
	float base;
	int expon;

	printf("���� �Է��ϼ���. ");
	scanf("%f", &base);
	printf("������ �Է��ϼ���. ");
	scanf("%d", &expon);
	float result;
	result = power(base, expon);

	printf("%.2f^%d�� %.2f�Դϴ�.", base, expon, result);
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