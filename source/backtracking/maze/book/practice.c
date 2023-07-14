//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#define MAX 180
//#define TRUE 1
//#define FALSE 0
//typedef struct {
//	short int vert;
//	short int horiz;
//} offsets;
//offsets move[8] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };
//
//typedef struct {
//	short int row;
//	short int col;
//	short int dir;
//} element;
//
//
//element stack[MAX];
//int top = 0;
//int maze[14][17];
//int mark[14][17] = { 0 };
//int EXIT_ROW = 12;
//int EXIT_COL = 15;
//
//void path();
//element pop(int *a);
//void push(element item);
//void stackFull();
//void stackEmpty();
//void main() {
//
//	for (int i = 1; i < 14; i++)
//		for (int j = 1; j < 17; j++)
//			maze[i][j] = rand() % 2;
//	
//	maze[1][1] = 0;
//	maze[12][15] = 0;
//	for (int i = 0; i < 14; i++)
//	{
//		maze[i][0] = 1;
//		maze[i][16] = 1;;
//		for (int j = 0; j < 17; j++)
//		{
//			maze[0][j] = 1;
//			maze[13][j] = 1;
//		}
//	}
//
//	for (int i = 0; i < 14; i++)
//	{
//		for (int j = 0; j < 17; j++)
//			printf("%d   ", maze[i][j]);
//		printf("\n");
//	}
//
//	path();
//}
//
//void path() {
//	int i, row, col, nextRow, nextCol, dir, found = FALSE;
//	element position;
//	mark[1][1] = 1; top = 0;
//	stack[0].row = 1;
//	stack[0].col = 1;
//	stack[0].dir = 1;
//
//	while (top > -1 && !found) {
//		position = pop(&top);
//		row = position.row;
//		col = position.col;
//		dir = position.dir;
//		while (dir < 8 && !found) {
//			nextRow = row + move[dir].vert;
//			nextCol = col + move[dir].horiz;
//			if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
//				found = TRUE;
//			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol])
//			{
//				mark[nextRow][nextCol] = 1;
//				position.row = row;
//				position.col = col;
//				position.dir = ++dir;
//				push(position);
//				row = nextRow;
//				col = nextCol;
//				dir = 0;
//			}
//			else ++dir;
//
//		}
//	}
//
//	if (found) {
//		printf("The path is:\n");
//		printf("row col\n");
//		for (i = 0; i <= top; i++)
//			printf("(%2d,%5d)\n", stack[i].row, stack[i].col);
//		printf("(%2d,%5d)\n", row, col);
//		printf("(%2d,%5d)\n", EXIT_ROW, EXIT_COL);
//	}
//	else printf("The maze does not have a path\n");
//
//}
//void push(element item)
//{
//	if (top >= MAX - 1)
//		stackFull();
//	stack[++top] = item;
//}
//element pop(int* a)
//{
//	if (top == -1)
//		stackEmpty();
//	return stack[top--];
//}
//
//void stackFull() {
//	fprintf(stderr, "Stack is full,cannot add element");
//	exit(1);
//}
//void stackEmpty() {
//	fprintf(stderr, "stack is Empty, cannot delete element");
//	exit(1);
//}