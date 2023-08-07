/*
	program : activity select problem
	name : yeongjin kim
	last edited : 23.08.07
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int start, finish;
}activity;

int compare_finish(const void* a, const void* b) 
{
	return  ((activity *)a)->finish - ((activity*)b)->finish;
}

void printMaxActivities(activity act[], int n)
{
	int i, j;

	printf("Following activities are selected\n");


	i = 0;
	printf("activity times %d ~ %d", act[i].start,act[i].finish);


	for (j = 1; j < n; j++) 
	{
		if (act[j].start >= act[i].finish) 
		{
			printf(" %d ~ %d", act[j].start,act[j].finish);
			i = j;
		}
	}
}

int main()
{
	activity* act;
	int n;
	printf("Input activity number :");
	scanf_s("%d", &n);
	
	act = malloc(sizeof(activity) * n);

	for (int i = 0; i < n; i++)
	{
		printf("Input %d activity start and finish time : ",i+1);
		scanf_s("%d %d", &act[i].start, &act[i].finish);
	}

	qsort(act, n, sizeof(activity), compare_finish);
	
	printMaxActivities(act,n);
	free(act);
	return 0;
}
