/*
	program : m_coloring
	name : YeongJin Kim
	last_edit: 23.07.17
*/
#define _CRT_SECURE_NO_WARNINGS
#define MAX_VERTEX 10

#include <stdio.h>
#include <stdbool.h>

int graph[MAX_VERTEX][MAX_VERTEX]; //그래프 인접행렬
int colors[MAX_VERTEX];
int vertex_number;
int color_number;

bool vaild(int v, int c);
void m_color(int v,int *c)
{
	if (v == vertex_number)
	{
		printf("case: %d\n", *c);
		for (int i = 0; i < vertex_number; i++)
			printf("color of vertex - %d : %d \n", i, colors[i]);
		printf("\n");
		(*c)++;
	}
	else
	{
		for (int color = 1; color <= color_number; color++)
		{
			if (vaild(v, color))
			{
				colors[v] = color;
				m_color(v + 1,c);
				colors[v] = 0;
			}
		}
	}
}

bool vaild(int v, int c)
{
	for (int i = 0; i < vertex_number; i++)
	{
		if (graph[v][i] && colors[i] == c)
			return false;
	}
	return true;
}

int main()
{
	printf("Enter the number of vertices: ");
	scanf("%d", &vertex_number);

	printf("Enter the number of colors: ");
	scanf("%d", &color_number);

	printf("Enter the number of matrix:\n");
	for (int i = 0; i < vertex_number; i++)
		for (int j = 0; j < vertex_number; j++)
		{
			scanf("%d", &graph[i][j]);
		}
	

	int casenumber=1;
	m_color(0,&casenumber);

	return 0;
}
