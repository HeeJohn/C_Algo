#include<stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define FALSE 0;
#define TRUE 1;
#define EXIT_ROW 11
#define EXIT_COL 15

typedef struct {
	int vert;	// ����	��ǥ
	int horiz;	// ���� ��ǥ
}offsets;
offsets move[8] = { {-1,0 },{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,1} }; // ���� ǥ��
// ��   , �ϵ� , ��  , ���� , �� , ���� ,  ��  , �ϼ�
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
int maze[13][17] = {	// �̷� 
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

	mark[1][1] = 1;	// ��� ��ġ 
	top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;

	while (top > -1 && !found) {
		/* �ⱸ�� ã�������� �ݺ� */
		position = pop(&top);
		row = position.row;
		col = position.col;
		dir = position.dir;
		while (dir < 8 && !found) {
			/*���� ��ġ���� 8������ Ž���ϸ鼭 ��θ� ã��*/
			// dir �������� ���� ��ġ�� ���
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;


			if (nextRow == EXIT_ROW && nextCol == EXIT_COL) {
				/* ���� ��ġ�� �ⱸ�� ���*/
				found = TRUE;
			}
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
				/* ���� ��ġ�� ���� �ƴϰ�, �湮���� ���� ���� ���*/
				// ���� ��ġ�� �湮�� ������ ǥ���ϰ�, ���ÿ� ����
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
		/* ��ΰ� ���� */
		printf("The path is : \n");
		printf("row col\n");


		for (i = 0; i <= top; i++)
			/* ��� ��� */
			printf("%2d%5d\n", stack[i].row, stack[i].col);

		/*���������� ������ ��ġ�� �ⱸ ��ġ�� ���*/
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
	}
	// ��ΰ� �������� �ʴ� ���
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

