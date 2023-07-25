#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int fibonacci(int n, int fibo[]);

int main() {
	int n;
	int fibo[100] = { 0 };	// �Ǻ���ġ �迭 ���� ��� ��� 0���� �ʱ�ȭ
	printf("������� �Ǻ���ġ ������ ����ұ��? ");
	scanf("%d", &n);
	if (n <= 0) {
		fprintf(stderr, "1���� ���� ���� �Է��� �� �����ϴ�.");
		return 0;
	}
	fibonacci(n, fibo);

	return 0;
}

int fibonacci(int n, int fibo[]) {
	/* ���� ���α׷����Ͽ� �Ǻ���ġ�� �ѹ� ����� ������ �迭�� �����Ų��. */
	int count = 0;
	while (count < n) { // n������ ���� ���ϱ� ���� count ���ش�.  
		if (fibo[n] != 0)	// 0�� �ƴ϶�� ��, �������� ������ �״�� ���ش�.
			return fibo[n];
		if (n == 1 || n == 2) {
			fibo[n] = 1;
		}
		else {
			fibo[n] = fibonacci(n - 1, fibo) + fibonacci(n - 2, fibo);	// n - 1���� n - 2���� ���� �Ǻ���ġ �迭�� ���� ��Ų��. 
		}
		printf("%d ", fibo[n]);	// ������ ��� 
		count++;
	}

}