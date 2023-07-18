/*
	program : Maze_1
	name : YeongJin Kim
	last_edit: 23.07.15
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
#define ROW 14
#define COL 17
#define EXIT_ROW 13
#define EXIT_COL 16
#define MAX_STACK ROW*COL

typedef struct
{
	short int vert;
	short int horiz;

}offset;
offset move[8] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} }; 
// move[dir].vert, mover[dir].horiz have to initialization <3.10>
// N, NE, E, SE, S, SW, W, NW

typedef struct
{
	short int row;
	short int col;
	short int dir;
}element;
element stack[MAX_STACK];
int top;
void stackfull()
{
	fprintf(stderr, "stack is full\n");
	exit(EXIT_FAILURE);
}
void stackempty()
{
	fprintf(stderr, "stack is empty\n");
	exit(EXIT_FAILURE);
}
void push(element item)
{
	if (top >= MAX_STACK)
		stackfull();
	stack[++top] = item;
}
element pop()
{
	if (top == -1)
		stackempty();
	return stack[top--];
}

short int maze[ROW][COL] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1},
		{1,1,0,0,0,1,1,0,1,1,1,0,0,1,1,1,1},
		{1,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1},
		{1,1,1,0,1,1,1,1,0,1,1,0,1,1,0,0,1},
		{1,1,1,0,1,0,0,1,0,1,1,1,1,1,1,1,1},
		{1,0,0,1,1,0,1,1,1,0,1,0,0,1,0,1,1},
		{1,0,0,1,1,0,1,1,1,0,1,0,0,1,0,1,1},
		{1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
		{1,0,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1},
		{1,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,1},
		{1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,1},
		{1,0,1,0,0,1,1,1,1,1,0,1,1,1,1,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
short int mark[ROW][COL];

void maze_path()
{
	int i, row, col, nextrow, nextcol, dir, found = false;
	element position;
	mark[1][1] = true;
	top = 0;
	stack[0].row = 1, stack[0].col = 1, stack[0].dir = 1;
	while (top > -1 && !found)		// EXIT_POINT면 반복문 탈출
	{
		position = pop(&top);		
		row = position.row;
		col = position.col;
		dir = position.dir;
		while (dir < 8 && !found)	// EXIT_POINT를 만났거나 모든 move[dir]값을 해도 element 0이 없다면 탈출
		{
			nextrow = row + move[dir].vert;
			nextcol = col + move[dir].horiz;
			if (nextrow == EXIT_ROW && nextcol == EXIT_COL)	// found EXIT
				found = true;
			else if (!maze[nextrow][nextcol] && !mark[nextrow][nextcol])	// found next element of 0
			{
				mark[nextrow][nextcol] = 1;
				position.row = row;
				position.col = col;
				position.dir = ++dir;
				push(position);	// 현재 POSITION 값 , 행렬 정보를 PUSH
				row = nextrow; col = nextcol; dir = 0;
			}
			else  // there is no way
				++dir;
		}
	}
	if (found)
	{
		printf("The path is:\n");
		printf("Row\tCol\n");
		for (i = 0; i <= top; i++)
			printf("%2d%7d\n", stack[i].row, stack[i].col);	//스택에 쌓았던 미로 탈출 경로를 출력
		printf("%2d%7d\n", row, col);
		printf("%2d%7d\n", EXIT_ROW, EXIT_COL);
	}
	else
		printf("The maze does not have a path.\n");
}

void main()
{
	maze_path();
}