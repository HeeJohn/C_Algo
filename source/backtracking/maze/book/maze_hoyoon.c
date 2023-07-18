#include<stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define FALSE 0;
#define TRUE 1;
#define EXIT_ROW 11
#define EXIT_COL 15

typedef struct {
	int vert;	// 수직	좌표
	int horiz;	// 수평 좌표
}offsets;
offsets move[8] = { {-1,0 },{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,1} }; // 방향 표시
// 북   , 북동 , 동  , 남동 , 남 , 남서 ,  서  , 북서
typedef struct {
	short int row;
	short int col;
	short int dir;
} element;
element stack[MAX_STACK_SIZE];

void path(void);
void push(element position);
element pop(int* top);

int top;
int maze[13][17] = {	// 미로 
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1},
	{1,1,0,0,0,1,1,0,1,1,1,0,0,1,1,1,1},{1,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1},
	{1,1,1,0,1,1,1,1,0,1,1,0,1,1,0,0,1},{1,1,1,0,1,0,0,1,0,1,1,1,1,1,1,1,1},
	{1,0,0,1,1,0,1,1,1,0,1,0,0,1,0,1,1},{1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1},{1,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,1},
	{1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,1},{1,0,1,0,0,1,1,1,1,1,0,1,1,1,1,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
int mark[13][17] = { 0 };

int main() {
	path();
	return 0;
}
void path(void) {
	int i, row, col, nextRow, nextCol, dir, found = FALSE;
	element position;

	mark[1][1] = 1;	// 출발 위치 
	top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;

	while (top > -1 && !found) {
		/* 출구를 찾을때까지 반복 */
		position = pop(&top);
		row = position.row;
		col = position.col;
		dir = position.dir;
		while (dir < 8 && !found) {
			/*현재 위치에서 8방향을 탐색하면서 경로를 찾음*/
			// dir 방향으로 다음 위치를 계산
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;


			if (nextRow == EXIT_ROW && nextCol == EXIT_COL) {
				/* 다음 위치가 출구일 경우*/
				found = TRUE;
			}
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
				/* 다음 위치가 벽이 아니고, 방문하지 않은 곳인 경우*/
				// 다음 위치를 방문한 것으로 표시하고, 스택에 저장
				mark[nextRow][nextCol] = 1;
				position.row = row;	position.col = col;
				position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol; dir = 0;
			}
			else ++dir;
		}
	}
	if (found) {
		/* 경로가 존재 */
		printf("The path is : \n");
		printf("row col\n");


		for (i = 0; i <= top; i++)
			/* 경로 출력 */
			printf("%2d%5d\n", stack[i].row, stack[i].col);

		/*마지막으로 도착한 위치와 출구 위치를 출력*/
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
	}
	// 경로가 존재하지 않는 경우
	else
		printf("The maze does not have a path\n");
}
void push(element position) {
	top++;
	stack[top].row = position.row;
	stack[top].col = position.col;
	stack[top].dir = position.dir;
}
element pop(int* top) {
	if (*top < 0) {
		fprintf(stderr, "Stack is Empty");
		exit(1);
	}
	return stack[(*top)--];
}

