#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<windows.h>

#define EXIT_ROW 10 // 미로 크기
#define	EXIT_COL 10
#define MAX_COL EXIT_COL+2 //벽을 포함한 미로 크기
#define MAX_ROW EXIT_ROW+2
#define MAX_SIZE MAX_COL*MAX_ROW

void gotoxy(int x, int y, const char* s) { //x값을 2x로 변경, 좌표값에 바로 문자열을 입력할 수 있도록 printf함수 삽입  
	COORD pos = { (2 * x),y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("%s", s);
}
typedef struct {
	short int vert;
	short int horiz;
} offsets;
offsets move[8];
typedef struct {
	short int row;// 행
	short int col;// 렬
	short int dir;//방향	
}element;

element stack[MAX_SIZE];//미로 탈출 경로 스택
int top = -1;
int mark[MAX_COL][MAX_ROW];//지나간 표시
int maze[MAX_COL][MAX_ROW] = {
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,1,0,0,0,1,1,1,0,1,1},
	{1,1,0,1,1,1,0,1,0,1,1,1} ,
	{1,0,1,0,1,1,1,0,1,1,1,1} ,
	{1,0,1,1,1,1,1,0,1,1,1,1} ,
	{1,0,1,1,1,1,0,1,0,1,1,1} ,
	{1,1,1,1,1,0,1,1,1,0,1,1} ,
	{1,1,1,1,1,0,1,1,1,0,1,1} ,
	{1,1,1,1,0,1,1,1,1,1,1,1} ,
	{1,1,1,0,1,0,1,1,1,1,1,1} ,
	{1,1,0,1,1,1,0,0,0,0,0,1} ,
	{1,1,1,1,1,1,1,1,1,1,1,1} };//미로
typedef enum {
	north, northeast, east, southeast, south, southwest, west, northwest
};//책에 나온 순서대로 북=0,북동=1,동=2....

void reset_move() {//이동방향 설정

	move[north].vert = -1; move[north].horiz = 0;
	move[northeast].vert = -1; move[northeast].horiz = 1;
	move[east].vert = 0; move[east].horiz = 1;
	move[southeast].vert = 1; move[southeast].horiz = 1;
	move[south].vert = 1; move[south].horiz = 0;
	move[southwest].vert = 1; move[southwest].horiz = -1;
	move[west].vert = 0; move[west].horiz = -1;
	move[northwest].vert = -1; move[northwest].horiz = -1;
}

void stackIsFull()
{
	fprintf(stderr, "스택에 공간이 없습니다.");
	exit(EXIT_FAILURE);
}

element stackIsEmpty()
{
	fprintf(stderr, "스택이 비어있습니다.");
	exit(EXIT_FAILURE);
}

void push(element ele)
{
	if (top == MAX_SIZE - 1) stackIsFull();
	else stack[++top] = ele;
}

element pop()
{
	if (top == -1)	stackIsEmpty();
	else return stack[top--];
}


void path(void)
{
	int i, row, col, nextRow, nextCol, dir, found = false;
	element position;
	mark[1][1] = 1; top = 0; //좌표 1,1 즉 시작하는 부분을 1로 초기화 즉 지나간 좌표라고 초기화
	stack[0].row = 1;//스택에 처음 좌표 행,렬,방향을 집어넣는다
	stack[0].col = 1;
	stack[0].dir = 1;
	while (top > -1 && !found) //미로를 탈출할 때 까지 무한반복
	{
		position = pop();//스택에서 빼낸 위치를 현재 위치로 초기화
		row = position.row;
		col = position.col;
		dir = position.dir;
		while (dir < 8 && !found) //현재위치에서 모든 방향으로 접근해보면서 0인 위치, 즉 알맞은 위치를 찾는다
		{
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL) //탈출 위치를 찾았다면 found를 true로 초기화
				found = true;
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol])//알맞은 경로이면서 지나가지않은 경로이면 스택에 삽입한다
			{
				mark[nextRow][nextCol] = 1;
				position.row = row;
				position.col = col;
				position.dir = ++dir;
				push(position);
				row = nextRow;
				col = nextCol;
				dir = north;
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
void print_path() {
	for (int i = 0;i <= top;i++)gotoxy(stack[i].col, stack[i].row + 20, "●");
}//스택에 쌓인 위치들 즉, 탈출 경로를 좌표를 찍어 길을 보여준다

int main() {
	reset_move();
	path();
	print_path();
}