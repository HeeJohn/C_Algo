#define _CRT_SECURE_NO_WARNINGS/*항공소프트웨어공학과 202000974 이재혁*/
#include<stdio.h>
#include<stdlib.h>
#define MALLOC(p, s) \
if(!((p)=malloc(s)))   {\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}
#define MAX_ROW 12
#define MAX_COL 12
#define EXIT_ROW 10
#define EXIT_COL 10
#define MAX_STACK_SIZE EXIT_ROW*EXIT_COL
const int FALSE = 0;
const int TRUE = 1;
typedef struct
{ /*  좌표 구조체  */
	short int vert;    // 수직
	short int horiz;   // 수평
}offsets;
offsets move[8];  // 8방향 이동 배열
typedef struct
{ /*  스택 구조체 */
	short int row;  // 행
	short int col;  // 열
	short int dir;  // 위치
}element;
element stack[MAX_STACK_SIZE];
int top = -1;
void push(element item)
{ /* 스택 삽입 함수 */
	if (top >= MAX_STACK_SIZE - 1)
	{
		fprintf(stderr, "overflow");
		exit(EXIT_FAILURE);
	}
	stack[++top] = item;
}
element pop(void)
{ /* 스택 삭제 함수 */
	if (top == -1)
	{
		fprintf(stderr, "underflow");
		exit(EXIT_FAILURE);
	}
	return stack[top--];
}
int mark[MAX_ROW][MAX_COL];  // 방문 여부를 기록하는 마크 배열
int maze[MAX_ROW][MAX_COL] =  // 미로 배열
{ { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};
void init_move()
{/* move 배열 초기화 함수 */
	move[0].vert = -1; move[0].horiz = 0;
	move[1].vert = -1; move[1].horiz = 1;
	move[2].vert = 0; move[2].horiz = 1;
	move[3].vert = 1; move[3].horiz = 1;
	move[4].vert = 1; move[4].horiz = 0;
	move[5].vert = 1; move[5].horiz = -1;
	move[6].vert = 0; move[6].horiz = -1;
	move[7].vert = -1; move[7].horiz = -1;
}
void path(void)
{/* 미로 알고리즘(출력 포함) */
	int i, row, col, nextRow, nextCol, dir, found = FALSE;
	element position;
	mark[1][1] = 1; top = 0;
	stack[0].row = 1;
	stack[0].col = 1;
	stack[0].dir = 1;
	while (top > -1 && !found)
	{
		position = pop();
		row = position.row;
		col = position.col;
		dir = position.dir;
		while (dir < 8 && !found)
		{
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
				found = TRUE;
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol])
			{
				mark[nextRow][nextCol] = 1;
				position.row = row;
				position.col = col;
				position.dir = ++dir;
				push(position);
				row = nextRow;
				col = nextCol;
				dir = 0;
			}
			else
				++dir;
		}
	}
	if (found)
	{
		printf("The path is:\n");
		printf("row   col\n");
		for (i = 0;i <= top;i++)
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
	}
	else
		printf("The maze does not have a path\n");
}
int main()
{
	init_move();
	path();

	return 0;
}


