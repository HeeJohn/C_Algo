#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define D 57
#define TRUE 1
#define FALSE 0


typedef struct {
	char str_tmp[1024];
} data;

typedef struct {
	char name[10];
	int time[D];
	int cost[D];
	int row;
	int col;
} MAP;

data arr[D];

void shortest_path(int start, int n);
int choose(int distance[], int n, int found[]);
void printMap(MAP data[]);
void initailize(MAP data[]); // MAP 초기화
void remove_spaces(char* s); // 공백 제거
void separate_feild(char* s, char* token, MAP* data); // 불러온 파일을 MAP에 이름, 시간, 비용, 행, 열 에 저장하는 함수
void print(MAP data[]);


void main() {
	FILE* pFile = NULL;
	int i = 0;
	char* token;
	MAP data[D];
	initailize(data);
	pFile = fopen("test.csv", "r");

	if (pFile != NULL) {
		while (!feof(pFile)) {

			if (i > D) break; // i가 R을 넘기는 것을 방지함
			fgets(arr[i].str_tmp, 1024, pFile); // 파일을 한 줄 불러와서 str_tmp에 저장한다.

			//remove_spaces(arr[i].str_tmp);

			token = strtok(arr[i].str_tmp, ","); // str_tmp에 ','로 구분된 데이터들을 분리한다.

			//if (i < D) { // i가 0일 때는 엑셀에 맨 위 데이터 들이 있기 때문에 건너 뛴다.
				separate_feild(&arr[i].str_tmp, token, &data[i]);
			//}
			i++;
		}

	}
	else printf("fail\n");
	print(data);
	//printMap(data);
}

void remove_spaces(char* s) {
	const char* d = s;
	do {
		while (*d == ' ') {
			++d;
		}
	} while (*s++ = *d++);
}

void separate_feild(char* s, char* token, MAP* data) {
	int i = 0, j = 0, t = 0;

	while (token != NULL) {
		if (i == 0) strcpy(data->name, token);
		else if (i == 1)
		{
			data->row = atoi(token); // 행에 해당하는 부분을 저장
		}
		else if (i == 2)
		{
			data->col = atoi(token); // 열에 해당하는 부분을 저장
		}
		else if (i > 2 && i % 2 == 1) {
			data->cost[j++] = atoi(token); // 비용을 저장
		}
		else {
			data->time[t++] = atoi(token); // 걸리는 시간을 저장
		}
		i++;
		token = strtok(NULL, ",");
	}
}

void initailize(MAP data[]) {
	for (int i = 0; i < D; i++) {
		data[i].row = -1;
		data[i].col = -1;
		*data[i].name = " ";
		//data[i].cost[i] = 0;
		//data[i].time[i] = 0;
	}
}

void printMap(MAP data[]) {
	for (int i = 0; i < D; i++) {
		printf("ROW : %d, COL : %d, name : %s\n", data[i].row, data[i].col, data[i].name);
		for (int j = 0; j < D - 1; j++) {
			if (data[i].cost[j] != -1 && data[i].time[j] != -1)
				printf("cost : %d,\ttime : %d\n", data[i].cost[j], data[i].time[j]);
		}
	}
}

void print(MAP data[]) {
	for(int i = 0; i < D; i++)
	{
		for(int j = 0; j < D; j++)
		{
			if (i == data[j].row && j == data[j].col)
				printf("%s", data[j].name);
			else
				printf("  ");
		}
		printf("\n");
	}
}

int choose(int distance[], int n, int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void shortest_path(int start, int n) {
	int i, j, u, w;
	for (i = 0; i < n; i++) {
		if (weight[start][i] != -1) {
			record[i][0] = start;
			record[i][1] = i;
		}
		distance[i] = weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE;
	distance[start] = 0;
	for (i = 0; i < n - 2; i++) {
		u = choose(distance, n, found);
		found[u] = TRUE;
		for (w = 0; w < n; w++) {
			if(!found[w]) 
				if (distance[u] + weight[u][w] < distance[w]) {
					distance[w] = distance[u] + weight[u][w];
					for (j = 0; j < n, j++)
						record[w][j] = INT_MIN;
					for (j = 0; j < n; j++) {
						if (record[u][j] != INT_MIN)
							record[w][j] = record[u][j];
						else break;
					}
					record[w][j] = w;
				}
		}
	}
}