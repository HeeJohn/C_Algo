#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#define MAX_ROW 12
#define MAX_COL 12
void gotoxy(int x, int y, const char* s) { //x값을 2x로 변경, 좌표값에 바로 문자열을 입력할 수 있도록 printf함수 삽입  
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
}; // 미로

int visited[MAX_COL][MAX_ROW]; // 방문 여부를 저장하는 배열
int exitRow = 10; // 출구 위치
int exitCol = 10;
int found = 0; // 경로를 찾았는지 여부를 저장하는 변수

// 상하좌우 및 대각선 이동을 포함한 8방향
int move[8][2] = {
	{-1, -1}, // 좌상
	{-1, 0}, // 상
	{-1, 1}, // 우상
	{0, -1}, // 좌
	{0, 1}, // 우
	{1, -1}, // 좌하
	{1, 0}, // 하
	{1, 1} // 우하
};

void findPath(int row, int col) {
	if (row == exitRow && col == exitCol) {
		found = 1; // 출구에 도착한 경우 경로를 찾았음을 표시
		visited[row][col] = 1; // 출구 위치를 방문한 것으로 표시
		return;
	}

	visited[row][col] = 1; // 현재 위치를 방문한 것으로 표시

	// 8방향으로 이동하며 경로 탐색
	for (int i = 0; i < 8; i++) {
		int nextRow = row + move[i][0];
		int nextCol = col + move[i][1];

		if (maze[nextRow][nextCol] == 0 && visited[nextRow][nextCol] == 0) {
			findPath(nextRow, nextCol);
			if (found) { // 출구로 이어지는 경로를 찾았을 경우
				return;
			}
		}
	}
	visited[row][col] = 2; // 다른 경로에서 방문할 수 있도록 현재 위치 방문 여부 초기화
	
}

void print_path() {
	for (int i = 0;i <= MAX_ROW;i++)
		for(int j=0;j<MAX_COL;j++)
		if(visited[i][j]==1)
			gotoxy(j, i+20, "●");
	
}//스택에 쌓인 위치들 즉, 탈출 경로를 좌표를 찍어 길을 보여준다

int main(void) {
	int startRow = 1; // 시작 위치
	int startCol = 1;

	findPath(startRow, startCol);

	if (found) {
		printf("The path is:\n");
		printf("row col\n");
		for (int i = 0; i < MAX_COL; i++) {
			for (int j = 0; j < MAX_ROW; j++) {
				if (visited[i][j] ==1)
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
