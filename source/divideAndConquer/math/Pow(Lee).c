#define _CRT_SECURE_NO_WARNINGS/*�װ�����Ʈ������а� 202000974 ������*/
#include <stdio.h>
long long int pow(int x, int n)          // x�� ��, n�� ���� 
{ /* �ŵ����� �Լ� */
	long long int ret = 1;   // �����

	while (n)	            // ������ �����ϴ� ���� �ݺ�
	{
		if (n & 1)        // LSB�� 1�̶��
			ret *= x;

		n >>= 1;        // ������ ����Ʈ ����
		x *= x;        // ���� �������ش�.(���� ���� �� �ڸ��� �������� ����)
	}

	return ret;
}

int main()
{
	int base, exp, ret;

	printf("�ذ� ������ �Է��ϼ��� -> ");
	scanf("%d %d", &base, &exp);

	printf("%d ^ %d = %lld\n", base, exp, pow(base, exp));
	return 0;
}