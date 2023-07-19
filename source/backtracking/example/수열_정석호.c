#include <stdio.h>
#include <Windows.h>
//1���� N���� �ڿ��� �߿��� �ߺ� ���� M���� �� ����
int n, m;
int result[1000];
int visit_just_number[1000];

void permutation(int digit)
{
	int i;

	if (digit == m)//������ �ڸ��� �� á�ٸ� ������ ����Ѵ�.
	{
		for (int i = 0; i < m; i++)
			printf("%d ", result[i]);
		printf("\n");
	}
	else
	{
		for (i = 1; i <= n; i++)
		{
			if (visit_just_number[i] == false)//�湮���� ���� ���ڶ��
			{
				result[digit] = i;//������ ���ڸ� �ִ´�
				visit_just_number[i] = true;//�湮�ߴٰ� ǥ�ø� �����
				permutation(digit + 1);//���� �ڸ����� �Ѿ��.
				visit_just_number[i] = false;//��� ȣ���� ������ �湮 ���θ� false�� �ʱ�ȭ �ؼ� �ٸ� �ڸ��� �� �� �ְ� �Ѵ�.
			}
		}
	}
}
void inputNM(void) {
	printf("1���� N���� �ڿ��� �߿��� �ߺ� ���� M���� �� ������ ��� ã�����Դϴ�.\n");
	printf("N��M�� �Է����ּ���.(���� : N>=M) : ");
	scanf_s("%d %d", &n, &m);
	while (m > n) {
		printf("�ٽ� �Է��ּ���!!\n"); system("pause");system("cls");
		printf("1���� N���� �ڿ��� �߿��� �ߺ� ���� M���� �� ������ ��� ã�����Դϴ�.\n");
		printf("N��M�� �Է����ּ���.(���� : N>=M) : ");
		scanf_s("%d %d", &n, &m);
	}
}

int main(void)
{
	inputNM();//�Է��Լ�
	permutation(0);
	return 0;
}