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
void initailize(MAP data[]); // MAP �ʱ�ȭ
void remove_spaces(char* s); // ���� ����
void separate_feild(char* s, char* token, MAP* data); // �ҷ��� ������ MAP�� �̸�, �ð�, ���, ��, �� �� �����ϴ� �Լ�
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

			if (i > D) break; // i�� R�� �ѱ�� ���� ������
			fgets(arr[i].str_tmp, 1024, pFile); // ������ �� �� �ҷ��ͼ� str_tmp�� �����Ѵ�.

			//remove_spaces(arr[i].str_tmp);

			token = strtok(arr[i].str_tmp, ","); // str_tmp�� ','�� ���е� �����͵��� �и��Ѵ�.

			//if (i < D) { // i�� 0�� ���� ������ �� �� ������ ���� �ֱ� ������ �ǳ� �ڴ�.
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
			data->row = atoi(token); // �࿡ �ش��ϴ� �κ��� ����
		}
		else if (i == 2)
		{
			data->col = atoi(token); // ���� �ش��ϴ� �κ��� ����
		}
		else if (i > 2 && i % 2 == 1) {
			data->cost[j++] = atoi(token); // ����� ����
		}
		else {
			data->time[t++] = atoi(token); // �ɸ��� �ð��� ����
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