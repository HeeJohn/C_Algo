#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int fibonacci(int n, int fibo[]);

int main() {
	int n;
	int fibo[100] = { 0 };	// 피보나치 배열 저장 장소 모두 0으로 초기화
	printf("몇까지의 피보나치 수열을 출력할까요? ");
	scanf("%d", &n);
	if (n <= 0) {
		fprintf(stderr, "1보다 작은 값은 입력할 수 없습니다.");
		return 0;
	}
	fibonacci(n, fibo);

	return 0;
}

int fibonacci(int n, int fibo[]) {
	/* 동적 프로그래밍하여 피보나치를 한번 계산한 구간은 배열에 저장시킨다. */
	int count = 0;
	while (count < n) { // n번까지 값을 구하기 위해 count 해준다.  
		if (fibo[n] != 0)	// 0이 아니라면 즉, 계산된적이 있으면 그대로 써준다.
			return fibo[n];
		if (n == 1 || n == 2) {
			fibo[n] = 1;
		}
		else {
			fibo[n] = fibonacci(n - 1, fibo) + fibonacci(n - 2, fibo);	// n - 1번과 n - 2번을 더해 피보나치 배열에 저장 시킨다. 
		}
		printf("%d ", fibo[n]);	// 과정을 출력 
		count++;
	}

}