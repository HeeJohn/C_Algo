#define _CRT_SECURE_NO_WARNINGS/*�װ�����Ʈ������а� 202000974 ������*/
#include <stdio.h>
double memo[201];  // �޸����̼��� ���� �迭(�ߺ��� ���� ������� �ʱ� ���� ���)
double pibo(int n)
{ /* �Ǻ���ġ ��� �Լ� */

	if (n == 1 || n == 2)                                  // 1��, 2���� ��
		return 1;
	else if (memo[n] != 0)                               // memo�� ���� ���� ��(�̹� ����� ���� �ִٸ�)
		return memo[n];
	else                                                // 1��, 2���� �ƴϰ�, memo�� ���� ���� ��                            
		return memo[n] = (pibo(n - 1) + pibo(n - 2));
}
int main()
{
	int n;

	scanf("%d", &n);
	printf("%lf", pibo(n));


}