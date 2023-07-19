#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#define MAX_ROW 12
#define MAX_COL 12
void gotoxy(int x, int y, const char* s) { //x���� 2x�� ����, ��ǥ���� �ٷ� ���ڿ��� �Է��� �� �ֵ��� printf�Լ� ����  
	COORD pos = { (2 * x),y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("%s", s);
}
int maze[MAX_COL][MAX_ROW] = {
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,1,0,0,0,1,1,1,0,1,1},
	{1,1,0,1,1,1,0,1,0,1,1,1},
	{1,0,1,0,1,1,1,0,1,1,1,1},
	{1,0,1,1,1,1,1,0,1,1,1,1},
	{1,0,1,1,1,1,0,1,0,1,1,1},
	{1,1,1,1,1,0,1,1,1,0,1,1},
	{1,1,1,1,1,0,1,1,1,0,1,1},
	{1,1,1,1,0,1,1,1,1,1,1,1},
	{1,1,1,0,1,0,1,1,1,1,1,1},
	{1,1,0,1,1,1,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
}; // �̷�

int visited[MAX_COL][MAX_ROW]; // �湮 ���θ� �����ϴ� �迭
int exitRow = 10; // �ⱸ ��ġ
int exitCol = 10;
int found = 0; // ��θ� ã�Ҵ��� ���θ� �����ϴ� ����

// �����¿� �� �밢�� �̵��� ������ 8����
int move[8][2] = {
	{-1, -1}, // �»�
	{-1, 0}, // ��
	{-1, 1}, // ���
	{0, -1}, // ��
	{0, 1}, // ��
	{1, -1}, // ����
	{1, 0}, // ��
	{1, 1} // ����
};

void findPath(int row, int col) {
	if (row == exitRow && col == exitCol) {
		found = 1; // �ⱸ�� ������ ��� ��θ� ã������ ǥ��
		visited[row][col] = 1; // �ⱸ ��ġ�� �湮�� ������ ǥ��
		return;
	}

	visited[row][col] = 1; // ���� ��ġ�� �湮�� ������ ǥ��

	// 8�������� �̵��ϸ� ��� Ž��
	for (int i = 0; i < 8; i++) {
		int nextRow = row + move[i][0];
		int nextCol = col + move[i][1];

		if (maze[nextRow][nextCol] == 0 && visited[nextRow][nextCol] == 0) {
			findPath(nextRow, nextCol);
			if (found) { // �ⱸ�� �̾����� ��θ� ã���� ���
				return;
			}
		}
	}
	visited[row][col] = 2; // �ٸ� ��ο��� �湮�� �� �ֵ��� ���� ��ġ �湮 ���� �ʱ�ȭ
	
}

void print_path() {
	for (int i = 0;i <= MAX_ROW;i++)
		for(int j=0;j<MAX_COL;j++)
		if(visited[i][j]==2)
			gotoxy(j, i+20, "��");
	
}//���ÿ� ���� ��ġ�� ��, Ż�� ��θ� ��ǥ�� ��� ���� �����ش�

int main(void) {
	int startRow = 1; // ���� ��ġ
	int startCol = 1;

	findPath(startRow, startCol);

	if (found) {
		printf("The path is:\n");
		printf("row col\n");
		for (int i = 0; i < MAX_COL; i++) {
			for (int j = 0; j < MAX_ROW; j++) {
				if (visited[i][j] ==2)
					printf("%2d%5d\n", i, j);
			}
		}
		printf("%2d%5d\n", exitRow, exitCol);
		print_path();
	}
	else {
		printf("The maze does not have a path\n");
	}

	return 0;
}