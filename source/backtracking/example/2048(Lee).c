#define _CRT_SECURE_NO_WARNINGS/*항공소프트웨어공학과 202000974 이재혁*/
#include <stdio.h>

int ret = 0;  // 5번 이동 후 얻을 수 있는 가장 큰 블록의 크기

typedef struct
{ /* 보드 배열 구조체 */
	int map[20][20];
}BOARD;

void rotate(BOARD *k, int n)
{ /* 보드 90도 돌리는 함수 */
	int temp[20][20];

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			temp[y][x] = k->map[n - x - 1][y];
		}
	}
	// temp에 넣은 것 map에 복사
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			k->map[y][x] = temp[y][x];
		}
	}
}

void get_max(BOARD *k, int n)
{ /* 최댓값 찾고 저장하는 함수 */

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
{ /* 위로 이동시키는 경우의 함수(원래 상, 하, 좌, 우 4 방향이지만 rotate 함수가 있기 때문에 하나만 만든다) */
	int temp[20][20];

	for (int x = 0; x < n; x++)
	{
		// temp에 갱신이 있었는지 체크하는 플래그
		int flag = 0, target = -1;
		for (int y = 0; y < n; y++)
		{
			if (k->map[y][x] == 0)
			{
				continue;
			}
			// temp에 값이 한번 옮겨졌었고, 옮기려는 값과 앞에서 옮겨졌던 값(타겟팅된 값)이 같으면 업데이트
			if (flag == 1 && k->map[y][x] == temp[target][x])
			{
				temp[target][x] *= 2, flag = 0;
			}
			else
			{
				temp[++target][x] = k->map[y][x], flag = 1;
			}
		}
		// 값이 합쳐지고 나면 target이 끝까지 돌지 않고 끝나므로 돌면서 0으로 채워주기
		for (++target; target < n; target++)
		{
			temp[target][x] = 0;
		}
	}
	// temp에 넣은 것 map에 복사
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
	{ /* 5번을 모두 수행했다면 get_max 함수를 통해 최댓값 확인 후 함수 종료 */
		get_max(&cur, n);
		return;
	}

	for (int dir = 0; dir < 4; dir++)     // 4방향 확인
	{
		BOARD next = cur;
		up(&next, n);
		dfs(next, count + 1, n);
		rotate(&cur, n);
	}
}

int main()
{
	int n;  // 보드의 크기
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

