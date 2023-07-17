/*
	name : 다항식 입력
	last_edit : 23.07.11
*/
#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p,s) \
	if(!((p)=malloc(s))){\
		fprintf(stderr,"Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}
#define COMPARE(x,y) (((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1)



typedef struct polynode* polypointer;
typedef struct polynode
{
	int coef;
	int expon;
	polypointer link;
};
polypointer a, b;

void attach(int coefficient, int exponent, polypointer* ptr)
{
	polypointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;
}

polypointer padd(polypointer a, polypointer b)
{
	polypointer c, rear, temp;
	int sum;
	MALLOC(rear, sizeof(*rear));
	c = rear;
	while (a && b)
		switch (COMPARE(a->expon, b->expon))
		{
		case -1: attach(b->coef, b->expon, &rear);
			b = b->link;
			break;
		case 0: sum = a->coef + b->coef;
			if (sum)attach(sum, a->expon, &rear);
			a = a->link;
			b = b->link;
			break;
		case 1: attach(a->coef, a->expon, &rear);
			a = a->link;
			break;
		}
	for (; a; a = a->link)
		attach(a->coef, a->expon, &rear);
	for (; b; b = b->link)
		attach(b->coef, b->expon, &rear);

	rear->link = NULL;
	temp = c;
	c = c->link;
	free(temp);

	return c;
}

polypointer newpoly()
{
	polypointer first, c;
	MALLOC(first, sizeof(*first));
	c = first;
	int b;
	while (1)
	{
		printf("Input coef and exponent of Polynomial (exponent < 0 is quit) : ");
		scanf_s("%d %d", &first->coef, &first->expon);
		if (first->expon < 0)
			exit(EXIT_FAILURE);
		printf("Add B input 1, or not input 0 : ");
		scanf_s("%d", &b);
		if (b == 0)
			break;
		attach(first->coef, first->expon, &first);
	}
	first->link = NULL;
	printf("Stop create polynomial\n");
	return c;
}

int main()
{
	polypointer result;
	a = b = NULL;
	a = newpoly();
	b = newpoly();
	result = padd(a, b);
	for (; result; result = result->link)
	{
		printf("%d X^%d ", result->coef, result->expon);
		if ((result->link) != NULL)
			printf("+ ");
	}
}