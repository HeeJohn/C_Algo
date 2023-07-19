#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<windows.h>

#define EXIT_ROW 10 // �̷� ũ��
#define	EXIT_COL 10
#define MAX_COL EXIT_COL+2 //���� ������ �̷� ũ��
#define MAX_ROW EXIT_ROW+2
#define MAX_SIZE MAX_COL*MAX_ROW

void gotoxy(int x, int y, const char* s) { //x���� 2x�� ����, ��ǥ���� �ٷ� ���ڿ��� �Է��� �� �ֵ��� printf�Լ� ����  
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
	short int row;// ��
	short int col;// ��
	short int dir;//����	
}element;

element stack[MAX_SIZE];//�̷� Ż�� ��� ����
int top = -1;
int mark[MAX_COL][MAX_ROW];//������ ǥ��
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
	{1,1,1,1,1,1,1,1,1,1,1,1} };//�̷�
typedef enum {
	north, northeast, east, southeast, south, southwest, west, northwest
};//å�� ���� ������� ��=0,�ϵ�=1,��=2....

void reset_move() {//�̵����� ����

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
	fprintf(stderr, "���ÿ� ������ �����ϴ�.");
	exit(EXIT_FAILURE);
}

element stackIsEmpty()
{
	fprintf(stderr, "������ ����ֽ��ϴ�.");
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
	mark[1][1] = 1; top = 0; //��ǥ 1,1 �� �����ϴ� �κ��� 1�� �ʱ�ȭ �� ������ ��ǥ��� �ʱ�ȭ
	stack[0].row = 1;//���ÿ� ó�� ��ǥ ��,��,������ ����ִ´�
	stack[0].col = 1;
	stack[0].dir = 1;
	while (top > -1 && !found) //�̷θ� Ż���� �� ���� ���ѹݺ�
	{
		position = pop();//���ÿ��� ���� ��ġ�� ���� ��ġ�� �ʱ�ȭ
		row = position.row;
		col = position.col;
		dir = position.dir;
		while (dir < 8 && !found) //������ġ���� ��� �������� �����غ��鼭 0�� ��ġ, �� �˸��� ��ġ�� ã�´�
		{
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL) //Ż�� ��ġ�� ã�Ҵٸ� found�� true�� �ʱ�ȭ
				found = true;
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol])//�˸��� ����̸鼭 ������������ ����̸� ���ÿ� �����Ѵ�
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
	for (int i = 0;i <= top;i++)gotoxy(stack[i].col, stack[i].row + 20, "��");
}//���ÿ� ���� ��ġ�� ��, Ż�� ��θ� ��ǥ�� ��� ���� �����ش�

int main() {
	reset_move();
	path();
	print_path();
}