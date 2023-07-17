#define _CRT_SECURE_NO_WARNINGS/*�װ�����Ʈ������а� 202000974 ������*/
#include <stdio.h>

int ret = 0;  // 5�� �̵� �� ���� �� �ִ� ���� ū ����� ũ��

typedef struct
{ /* ���� �迭 ����ü */
	int map[20][20];
}BOARD;

void rotate(BOARD *k, int n)
{ /* ���� 90�� ������ �Լ� */
	int temp[20][20];

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			temp[y][x] = k->map[n - x - 1][y];
		}
	}
	// temp�� ���� �� map�� ����
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			k->map[y][x] = temp[y][x];
		}
	}
}

void get_max(BOARD *k, int n)
{ /* �ִ� ã�� �����ϴ� �Լ� */

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			if (ret < k->map[y][x])
			{
				ret = k->map[y][x];
			}
		}
	}
}

void up(BOARD* k, int n)
{ /* ���� �̵���Ű�� ����� �Լ�(���� ��, ��, ��, �� 4 ���������� rotate �Լ��� �ֱ� ������ �ϳ��� �����) */
	int temp[20][20];

	for (int x = 0; x < n; x++)
	{
		// temp�� ������ �־����� üũ�ϴ� �÷���
		int flag = 0, target = -1;
		for (int y = 0; y < n; y++)
		{
			if (k->map[y][x] == 0)
			{
				continue;
			}
			// temp�� ���� �ѹ� �Ű�������, �ű���� ���� �տ��� �Ű����� ��(Ÿ���õ� ��)�� ������ ������Ʈ
			if (flag == 1 && k->map[y][x] == temp[target][x])
			{
				temp[target][x] *= 2, flag = 0;
			}
			else
			{
				temp[++target][x] = k->map[y][x], flag = 1;
			}
		}
		// ���� �������� ���� target�� ������ ���� �ʰ� �����Ƿ� ���鼭 0���� ä���ֱ�
		for (++target; target < n; target++)
		{
			temp[target][x] = 0;
		}
	}
	// temp�� ���� �� map�� ����
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			k->map[y][x] = temp[y][x];
		}
	}
}

void dfs(BOARD cur, int count, int n)
{
	if (count == 5)
	{ /* 5���� ��� �����ߴٸ� get_max �Լ��� ���� �ִ� Ȯ�� �� �Լ� ���� */
		get_max(&cur, n);
		return;
	}

	for (int dir = 0; dir < 4; dir++)     // 4���� Ȯ��
	{
		BOARD next = cur;
		up(&next, n);
		dfs(next, count + 1, n);
		rotate(&cur, n);
	}
}

int main()
{
	int n;  // ������ ũ��
	BOARD board;
	scanf("%d", &n);
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			scanf("%d", &board.map[y][x]);
		}
	}
	dfs(board, 0, n);
	printf("%d\n", ret);

	return 0;
}

