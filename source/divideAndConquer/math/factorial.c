#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>

int factorial(int n);

int main() {
	int num;
	printf("수를 입력하세요. : ");
	scanf("%d", &num);
	printf("%d != %d", num, factorial(num));
}

int factorial(int n) {
	if (n == 0) {
		return 1;
	}
	else {
		return (n * factorial(n - 1));
	}
}