/*#include <stdio.h>
int memo[100];  // �޸������̼��� ���� �迭(�ߺ��� ���� ������� �ʱ� ���� ���)
int fibo(int n)
{ // �Ǻ���ġ ��� �Լ� 

	if (n == 1 || n == 2)                                // 1��, 2���� �� 1 ��ȯ
		return 1;
	else if (memo[n] != 0)                                // memo�� ���� ���� ��(�̹� ����� ���� �ִٸ�)
		return memo[n];
	else                                                 // 1��, 2���� �ƴϰ�, memo�� ���� ���� ��                            
		return memo[n] = (fibo(n - 1) + fibo(n - 2));
}
int main()
{
	int n;
	scanf_s("%d", &n);
	printf("%d", fibo(n));
}*/