﻿/*
	program: maze search
	name: kimminwoo
	last_edit:23.07.17
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define MAZE_SIZE 20

typedef struct Pos {
	short x;
	short y;
}Pos;

typedef struct Stack
{
	Pos data[MAX_SIZE];
	int top;

}Stack;

char maze[MAZE_SIZE][MAZE_SIZE] = { {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
								{'e', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0'},
								{'0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0'},
								{'0', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0'},
								{'0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0'},
								{'0', '1', '1', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0'},
								{'0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0'},
								{'0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0'},
								{'0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '0', '0', '1', '0'},
								{'0', '1', '0', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0'},
								{'0', '1', '0', '1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0'},
								{'0', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '1', '1', '0'},
								{'0', '0', '0', '0', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0'},
								{'0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0'},
								{'0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1', '0'},
								{'0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', 'x'},
								{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'} };

void Init(Stack* p)
{
	p->top = -1;
}

int Is_full(Stack* p)
{
	return (p->top == MAX_SIZE - 1);
}

int Is_empty(Stack* p)
{
	return (p->top == -1);
}

void Push(Stack* p, Pos data)
{
	if (Is_full(p))
	{
		printf("스택이 꽉찼습니다\n"); return;
	}
	else
	{
		p->top++;
		p->data[p->top].x = data.x;
		p->data[p->top].y = data.y;

	}
}

Pos Pop(Stack* p)
{
	if (Is_empty(p))
	{
		printf("스택이 비어있습니다\n");
		exit(1);
	}

	return p->data[(p->top)--];
}

void Findway(Stack* s, int x, int y)
{
	if (x < 0 || y < 0 || x > MAZE_SIZE || y > MAZE_SIZE) return;

	if (maze[x][y] != '1' && maze[x][y] != '.')
	{
		Pos tmp;
		tmp.x = x;
		tmp.y = y;


		Push(s, tmp);
	}
}

int main()
{
	Stack s;
	Pos here;
	int i, j, x, y;

	Init(&s);

	// 시작점 탐색
	for (i = 0; i < MAZE_SIZE; i++)
	{
		for (j = 0; j < MAZE_SIZE; j++)
		{
			if (maze[i][j] == 'e')
			{
				here.x = i;
				here.y = j;
			}
		}
	}

	printf("시작 점 (%d,%d) \n", here.x, here.y);

	while (maze[here.x][here.y] != 'x')
	{
		x = here.x;
		y = here.y;

		maze[x][y] = '.'; // 방문한 곳을 표시

		// 좌,우,위,아래중 이동 가능한 곳을 탐색
		Findway(&s, x + 1, y);
		Findway(&s, x - 1, y);
		Findway(&s, x, y + 1);
		Findway(&s, x, y - 1);

		if (Is_empty(&s))
		{
			printf("실패\n");
			return 0;
		}
		else
		{
			here = Pop(&s); // 현재 좌표를 변경
			printf("(%d,%d)\n", here.x, here.y);
		}
	}

	printf("도착 점 (%d,%d)\n", here.x, here.y);
	printf("탐색 성공\n");

	return 0;
}