#define _CRT_SECURE_NO_WARNINGS/*항공소프트웨어공학과 202000974 이재혁*/
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#define MAZE_SIZE 19
#define ROBOT 2
enum direction { UP = 1, RIGHT = 2, DOWN = 4, LEFT = 8 };                // 4방향 열거형
int maze[MAZE_SIZE][MAZE_SIZE] =                                        // 미로 배열(0: 길, 1: 벽)
{ { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
  { 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1 },
  { 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
  { 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };
int sx = MAZE_SIZE - 2, sy = MAZE_SIZE - 2;                           // 생쥐 출발 위치
int GetShape(int x, int y)
{ /* 벽 모양의 코드(숫자합)를 리턴하는 함수 */
	static int shape[] =
	{ 32, 179, 196, 192, 179, 179, 218, 195, 196, 217, 196,
		193, 191, 180, 194, 197 };
	int s = 0;
	if (maze[y][x]) { // 벽이 있는 경우에만 경우의 수를 따진다.
		if (y > 0 && maze[y - 1][x]) // 위쪽에 벽이 있는가?
			s |= UP;
		if (y < MAZE_SIZE - 1 && maze[y + 1][x]) // 아랫쪽에 벽이 있는가?
			s |= DOWN;
		if (x > 0 && maze[y][x - 1]) // 왼쪽에 벽이 있는가?
			s |= LEFT;
		if (x < MAZE_SIZE - 1 && maze[y][x + 1]) // 오른쪽에 벽이 있는가?
			s |= RIGHT;
	}
	return shape[s];
}
void gotoxy(int x, int y)
{ /* 좌표 이동 함수 */
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void draw_maze(void)
{ /* 미로 그리는 함수 */
	int i, j;
	for (j = 0;j < MAZE_SIZE;j++)
		for (i = 0;i < MAZE_SIZE;i++)
		{
			gotoxy(i, j);
			printf("%c", GetShape(i, j));
		}
}
void forward(int* x, int* y, int dir)
{ /* 앞으로 가는 함수 */

	gotoxy(*x, *y);
	putch(' ');       // 현재 위치를 지움 

	*x = (dir == LEFT) ? --(*x) :                      // 방향이 왼쪽이면 x를 1 감소
		(dir == RIGHT) ? ++(*x) : *x;                 // 방향이 오른쪽이면 x를 1 증가. 둘 다 해당사항 없으면 움직이지 않음
	*y = (dir == UP) ? --(*y) :                      // 방향이 위쪽이면 y를 1 감소
		(dir == DOWN) ? ++(*y) : *y;                // 방향이 아래쪽이면 y를 1 증가. 둘 다 해당사항 없으면 움직이지 않음

	gotoxy(*x, *y);
	putch(ROBOT);    // 이동한 위치에 출력
}
int WallAhead(int x, int y, int dir)
{ /* 벽이 앞에 있는지 알려주는 함수 */
	x = (dir == LEFT) ? --x :                  // 방향이 왼쪽이면 x를 1 감소
		(dir == RIGHT) ? ++x : x;             // 방향이 오른쪽이면 x를 1 증가. 둘 다 해당사항 없으면 움직이지 않음
	y = (dir == UP) ? --y :                  // 방향이 위쪽이면 y를 1 감소
		(dir == DOWN) ? ++y : y;            // 방향이 아래쪽이면 y를 1 증가. 둘 다 해당사항 없으면 움직이지 않음
	return maze[y][x];                     // 이동시킨 위치의 값을 반환(벽이 있다면 1을 반환할 것이고 없으면 0을 반환)
}
void right(int* dir)
{ /* 오른쪽 방향으로 회전하는 함수 */
	*dir <<= 1;                              // 비트 연산자를 통해 값 2배 증가
	*dir = (*dir > LEFT) ? UP : *dir;       //  2배 증가한 값이 LEFT를 넘을 경우 UP으로 넘어가야 함, 나머지의 경우 그대로 저장
}
void left(int* dir)
{ /* 왼쪽 방향으로 회전하는 함수 */
	*dir >>= 1;                              // 비트 연산자를 통해 값 2배 감소
	*dir = (*dir == 0) ? LEFT : *dir;       //  2배 감소한 값이 0일 경우 LEFT로 넘어가야 함, 나머지의 경우 그대로 저장
}
int still_in_maze(int x, int y)
{ /* 아직 미로에 있는지 */
	if (x > 0 && x < MAZE_SIZE - 1 && y>0 && y < MAZE_SIZE - 1)
		return 1;
	else
		return 0;
}
void right_hand(int x, int y, int dir)
{/* 우선법 함수 */
	gotoxy(x, y);
	putch(ROBOT);

	while (still_in_maze(x, y))
	{
		Sleep(100);                         // 눈으로 보기 위한 딜레이 함수
		right(&dir);                       // 먼저 오른쪽으로 돈다
		while (WallAhead(x, y, dir))
			left(&dir);                  // 벽이 있을 경우, 앞에 벽이 없을 때까지 왼쪽으로 돈다
		forward(&x, &y, dir);           // 앞으로 간다
	}
}
int main()
{
	SetConsoleOutputCP(437);          // 확장 아스키코드를 사용하기 위한 OEM 437
	draw_maze();
	right_hand(sx, sy, LEFT);

	return 0;
}