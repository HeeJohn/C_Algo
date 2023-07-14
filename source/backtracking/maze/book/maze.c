/*
	program : maze(book)
	name : HuiJun Seo
	last_edit: 23.07.14
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define EXIT_ROW 10
#define	EXIT_COL 10
#define MAX_SIZE EXIT_ROW*EXIT_COL
#define TRUE 1
#define FALSE 0
#define MAX_COL EXIT_COL+2
#define MAX_ROW EXIT_ROW+2

/*------struct & enum type definition--------*/

typedef enum {
	N, NE, E, SE, S, SW, W, NW
}direction;

typedef struct {
	short int vert;
	short int horiz;
}offsets;

typedef struct {
	short int row;
	short int col;
	short int dir;
}element;

/*------ global declaration ------*/

offsets move[8];
element stack[MAX_SIZE];
int top = -1;
short int mark[MAX_ROW][MAX_COL];
short int maze[MAX_ROW][MAX_COL] = {
	// 1 2 3 4 5 6 7 8 9 10 11 12
		{1,1,1,1,1,1,1,1,1,1,1,1 } , // 1
		{1,0,1,1,0,0,1,1,1,1,1,1 } , // 2
		{1,0,1,0,0,1,0,0,1,1,1,1 } , // 3
		{1,1,0,1,1,1,0,1,0,1,1,1 } , // 4
		{1,1,0,1,1,1,0,0,1,1,1,1 } , // 5
		{1,1,0,1,0,0,1,1,0,0,0,1 } , // 6
		{1,0,1,1,1,1,1,1,1,1,1,1 } , // 7
		{1,0,1,1,0,1,1,1,0,1,1,1 } , // 8
		{1,0,0,0,1,0,1,0,1,0,1,1 } , // 9
		{1,1,1,1,1,1,0,1,1,1,0,1 } , // 10
		{1,1,1,1,0,0,1,1,1,1,0,1 } , // 11
		{1,1,1,1,1,1,1,1,1,1,1,1 }   // 12 
};


/*------ funtions prototype declaration ------*/

element stackIsEmpty();
void stackIsFull();
void push(element loc);
element pop();
void initOffset();
void path();
void createMaze();


int main()
{
	initOffset();
	createMaze();
	path();

	return 0;
}

/*------ funtions ------*/


/*------ stack function ------*/


void stackIsFull()
{
	fprintf(stderr, "stack is full");
	exit(EXIT_FAILURE);
}

element stackIsEmpty()
{
	fprintf(stderr, "stack is empty");
	exit(EXIT_FAILURE);
}

void push(element loc)
{
	if (top == MAX_SIZE - 1)
		stackIsFull();
	else
		stack[++top] = loc;
}

element pop()
{
	if (top == -1)
		stackIsEmpty();
	else
		return stack[top--];
}

/*------ initializing ------*/

void createMaze()
{

	for (int i = 0; i < MAX_ROW; i++, puts(""))
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			if (i == 0 || i == MAX_ROW - 1 || j == 0 || j == MAX_COL - 1)
				mark[i][j] = 1;
			else
				mark[i][j] = 0;
			printf("%d ", maze[i][j]);
		}
	}
}


void initOffset()
{
	move[N].vert = -1;
	move[N].horiz = 0;

	move[NE].vert = -1;
	move[NE].horiz = 1;

	move[E].vert = 0;
	move[E].horiz = 1;

	move[SE].vert = 1;
	move[SE].horiz = 1;

	move[S].vert = 1;
	move[S].horiz = 0;

	move[SW].vert = 1;
	move[SW].horiz = -1;

	move[W].vert = 0;
	move[W].horiz = -1;

	move[NW].vert = -1;
	move[NW].horiz = -1;
}


/*------ find & print ------*/

void path()
{
	int i, row, col, nextRow, nextCol, dir, found = FALSE;
	element position;

	mark[1][1] = 1; // start point 
	top = 0; stack[0].row = 1; stack[0].col = 1; stack[0].dir = E;

	while (top > -1 && !found)
	{
		position = pop();
		row = position.row; col = position.col;
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
				position.row = row;		position.col = col;
				position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol;	dir = N;
			}
			else ++dir;
		}
	}
	if (found)
	{
		printf("\nThe path is : \n");
		printf("row   col\n");
		for (i = 0; i <= top; i++)
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
	}
	else printf("The maze does not have a path\n");
}
