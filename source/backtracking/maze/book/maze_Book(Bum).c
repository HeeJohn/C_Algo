/*
* program: 미로 찾기(책)
* name: 이창범
* date: 2023.07.18
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#define MALLOC(p, s) \
if(!((p)=malloc(s)))   {\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}
#define MAX_ROW 13
#define MAX_COL 17
#define EXIT_ROW 11
#define EXIT_COL 15
#define MAX_STACK_SIZE 100
bool F = false;
bool T = true;

typedef struct
{
	short int vert;    // 수직
	short int horiz;   // 수평
}offsets;
offsets move[8] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };
typedef struct {
	short int row;  // 행
	short int col;  // 열
	short int dir;  // 위치
}element;
element stack[MAX_STACK_SIZE];
int top = -1;

void push(element item);
element pop(void);

int mark[MAX_ROW][MAX_COL];//방문여부
int maze[MAX_ROW][MAX_COL];//미로
void buildMaze();//미로 만는 함수
void path();//미로 길찾는 알고리즘

int main()
{
	buildMaze();
	printf("미로:\n");
	for (int i = 0;i < MAX_ROW;i++) {
		for (int j = 0;j < MAX_COL;j++)
			printf("%d   ", maze[i][j]);
		printf("\n");
	}
	path();

	return 0;
}
void push(element item)
{
	if (top >= MAX_STACK_SIZE - 1)
	{
		fprintf(stderr, "overflow");
		exit(EXIT_FAILURE);
	}
	stack[++top] = item;
}
element pop(void)
{
	if (top == -1)
	{
		fprintf(stderr, "underflow");
		exit(EXIT_FAILURE);
	}
	return stack[top--];
}
void buildMaze() {
	srand(time(NULL));
	for (int i = 0;i < MAX_ROW;i++) {
		for (int j = 0;j < MAX_COL;j++) {
			if (i == 0 || i == 12 || j == 0 || j == 16)
				maze[i][j] = 1;
			else if ((i == 1 && j == 1) || (i == 15 && j == 11))
				maze[i][j] = 0;
			else
				maze[i][j] = rand() % 2;
		}
	}
}
void path()
{
	int i, row, col, nextRow, nextCol, dir, found = F;
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
				found = T;
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