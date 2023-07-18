/*
	program : Maze_2
	name : YeongJin Kim
	last_edit: 23.07.17
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS
#define ROW 7
#define COL 7
#define EXIT_ROW 5
#define EXIT_COL 5
#define MAX_QUEUE ROW*COL

typedef struct
{
	short int vert;
	short int horiz;

}offset;
offset move[4] = { {-1,0},{0,1},{1,0},{0,-1} };

typedef struct
{
	short int row;
	short int col;
}element;
element queue[MAX_QUEUE];
int front;
int rear;

void queueFull()
{
	fprintf(stderr, "Queue is full\n");
	exit(EXIT_FAILURE);
}
void queueEmpty()
{
	fprintf(stderr, "Queue is empty\n");
	exit(EXIT_FAILURE);
}
void addq(element item)
{
	if (rear == MAX_QUEUE - 1)
		queueFull();
	queue[++rear] = item;
}
element deleteq()
{
	if (front == rear)
		queueEmpty();
	return queue[++front];
}

short int maze[ROW][COL] = {

	{1,1,1,1,1,1,1},
	{1,0,1,0,0,0,1},
	{1,0,1,0,1,0,1},
	{1,0,1,0,0,0,1},
	{1,0,0,0,1,0,1},
	{1,1,1,0,0,0,1},
	{1,1,1,1,1,1,1}
};
short int mark[ROW][COL];

void maze_path()
{
	int i, curr_row, curr_col, nextrow, nextcol, found = false;
	element position, temp;
	mark[1][1] = true;
	front = -1;
	rear = 0;
	queue[0].col = 1, queue[0].row = 1;
	while (!(front==rear) && !found)
	{
		position = deleteq();
		curr_row = position.row;
		curr_col = position.col;
		for (i = 0; i < 4; i++)
		{
			nextrow = curr_row + move[i].vert;
			nextcol = curr_col + move[i].horiz;
			if (!maze[nextrow][nextcol] && !mark[nextrow][nextcol])
			{
				mark[nextrow][nextcol] = true;
				maze[nextrow][nextcol] = maze[curr_row][curr_col] + 1;
				temp.row = nextrow;
				temp.col = nextcol;
				addq(temp);
			}
			if (nextcol == EXIT_COL && nextrow == EXIT_ROW)
			{
				printf("Found the path\n");
				found = true;
				break;
			}
		}
	}
	if (found)
		printf("경로 탐색에 성공했습니다. 최단 경로 : %d\n", maze[nextrow][nextcol]);
	else
		printf("경로 탐색에 실패했습니다.\n");
}
void main()
{
	maze_path();
}