#define _CRT_SECURE_NO_WARNINGS/*�װ�����Ʈ������а� 202000974 ������*/
#include <stdio.h>
long long f(long long x)
{
	if (x == 1)
		return 0;
	long long i;
	for (i = 1;i * 2 < x;i *= 2);    // x�� ���� �ʴ� 2�� �ŵ����� ã��
	return !f(x - i);           // �������� �� ���� ���(not�� ���� ������ �� ���� ���)
}
int main()
{
	long long n;
	scanf("%lld", &n);

	printf("%lld", f(n));

	return 0;
}