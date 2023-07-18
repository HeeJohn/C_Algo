/*
    program : maze_ymh
    name : minhyuck yun
    last_edit : 23.07.15
*/

#include <stdio.h>
#include <stdlib.h>

#define EXIT_ROW 12
#define EXIT_COL 15
#define TRUE 1
#define FALSE 0
#define MAX_STACK_SIZE 250
#define MAX_ROW 14
#define MAX_COL 17

int mark[MAX_ROW][MAX_COL] = {0};
int maze[MAX_ROW][MAX_COL] =
{ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
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

int top = -1;

typedef struct {
    short int vert;
    short int horiz;
} offsets;
offsets move[8] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} }; //각 방향에 대한 이동 배열

typedef struct {
    short int row;
    short int col;
    short int dir;
} element;

element stack[MAX_STACK_SIZE];

void path(void);
void push(element item);
element pop();
void stackFull();
int stackEmpty();


int main(void)
{
    path();
}

void push(element item)
{
    if (top >= MAX_STACK_SIZE - 1)
        stackFull();
    stack[++top] = item;
}

void stackFull()
{
    fprintf(stderr, "Stack is full, cannot add element");
    exit(EXIT_FAILURE);
}

element pop(int top)
{
    if (top == -1)
        stackEmpty();
    return stack[top--];
}

int stackEmpty()
{
    fprintf(stderr, "Stack is Empty, cannot pop element");
    exit(EXIT_FAILURE);
}

void path(void)
{
    int i, row, col, nextRow, nextCol, dir, found = FALSE;
    element position;
    mark[1][1] = 1;
    top = 0;
    stack[0].row = 1;
    stack[0].col = 1;
    stack[0].dir = 0;
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
                position.dir = dir;
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
        printf("row  col\n");
        for (i = 0; i <= top; i++)
            printf("%2d%5d\n", stack[i].row, stack[i].col);
        printf("%2d%5d\n", row, col);
        printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
    }
    else
        printf("the maze does not have a path\n");
}