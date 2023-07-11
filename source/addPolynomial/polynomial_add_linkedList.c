#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MALLOC(p,s)\
	if(!((p)= malloc(s)))\
	{	fprintf(stderr,"Insufficient memory");\
		exit(EXIT_FAILURE);\
	}

/*positive coefficient, put '+' sign, for negative put escape sequence "back space". */
#define SIGN(x) (((x)>0) ? '+' : '\b' )
#define COMPARE(x,y) (((x)<(y))?-1:((x)==(y))?0:1) // smaller x<y: -1 , same x==y: 0, bigger x>y: 1.

typedef struct {
	float coef;
	int expon;
}polynomial;
typedef struct node* polyPointer;
typedef struct node {
	polynomial poly;
	polyPointer link;
}polyNode;

polyPointer padd(polyPointer a, polyPointer b);
void attach(float coefficient, int exponent, polyPointer* ptr);
void printPoly(polyPointer target);
void inputPoly(polyPointer* front);
//void freeSpace(polyPointer target);

int main()
{
	polyPointer firstA, firstB, firstD;

	/* =========== input A(x) & B(x) polynomial ===========*/
	puts(" !!If coefficient of term is <zero>, stop taking input !! ");
	puts("< Input the coefficient and exponent of Polynomial A(x) in turn >"); inputPoly(&firstA);
	puts("\n< Input the coefficient and exponent of Polynomial B(x) in turn >"); inputPoly(&firstB);

	/* === Addition of polynomial === */
	firstD = padd(firstA, firstB);

	/* ====================== result =======================*/
	puts("\n\n====================== result display =======================\n");
	printf("polynomial A(x) = "); printPoly(firstA); puts("\n\t+");
	printf("polynomial B(x) = "); printPoly(firstB); puts("\n\t=");
	printf("polynomial D(x) = "); printPoly(firstD);

	return 0;
}

polyPointer padd(polyPointer a, polyPointer b)
{
	polyPointer firstD, rear, temp;
	float sum;
	MALLOC(rear, sizeof(*rear));

	firstD = rear; // save the first node of polynomial D(x)

	while (a && b) /* repeat until either A(x)polynomial or the other is finished adding*/
	{
		switch (COMPARE(a->poly.expon, b->poly.expon))
		{
		case -1: /*(a->poly.expon) < (b->poly.expon)*/
			attach(b->poly.coef, b->poly.expon, &rear);
			b = b->link; break;

		case 0: /*(a->poly.expon) == (b->poly.expon)*/
			sum = a->poly.coef + b->poly.coef;
			if (sum) attach(sum, b->poly.expon, &rear);
			a = a->link; b = b->link; break;

		case 1: /*(a->poly.expon) > (b->poly.expon)*/
			attach(a->poly.coef, a->poly.expon, &rear);
			a = a->link; break;
		}
	}
	/*if number of terms between A(x),B(x) is different
	and they are left, put the rest into D(x) */
	for (; a; a = a->link)
		attach(a->poly.coef, a->poly.expon, &rear);
	for (; b; b = b->link)
		attach(b->poly.coef, b->poly.expon, &rear);
	rear->link = NULL; // mark that latest rear points the last term of D polynomial

	/*deleting unnecessary first node*/
	temp = firstD; firstD = firstD->link;
	free(temp);

	return firstD;
}

void inputPoly(polyPointer* front)
{
	float coefficient; int exponent;
	polyPointer rear;
	MALLOC(rear, sizeof(*rear));
	int exPre;

	/* ============ input ============= */
	*front = rear; // save the first node.

	printf("type the coefficient and exponent of term : ");
	scanf("%f %d", &coefficient, &exponent); exPre = exponent + 1;

	while (coefficient != 0 && exponent < exPre) // invalid condition
	{
		attach(coefficient, exponent, &rear);

		printf("type the coefficient and exponent of term : ");
		exPre = exponent; scanf("%f %d", &coefficient, &exponent);
	}
	rear->link = NULL; //  last node.

	/* deleting unnecessary first node */
	rear = *front;
	*front = (*front)->link; // move to the valid term(second node).
	free(rear);
}

void attach(float coefficient, int exponent, polyPointer* ptr)
{
	polyPointer temp;
	MALLOC(temp, sizeof(*temp));

	/*put delivered values in the allocated space.*/
	temp->poly.coef = coefficient;
	temp->poly.expon = exponent;

	/*linking*/
	(*ptr)->link = temp;
	*ptr = temp;
}

void printPoly(polyPointer target)
{
	polyPointer temp;

	if (!target)
		return;

	while (target->link) //print except for last term
	{	/*  polynomial  */
		printf(" %.fx^%d ", target->poly.coef, target->poly.expon);

		/*-- free space --*/
		temp = target->link;
		free(target);
		target = temp;

		putchar(SIGN(target->poly.coef)); // put '+' or '\b' after each terms
	}

	if (target->poly.expon == 0) // last term has 0 expon, which is constant.
		printf(" %.f", target->poly.coef);
	else
		printf(" %.fx^%d", target->poly.coef, target->poly.expon);

	free(target);
}

/*void freeSpace(polyPointer target)
{
	polyPointer temp;

	while (target != NULL)
	{
		temp = target->link;
		free(target);
		target = temp;
	}

	puts("\n>>successfully returned \"allocated memories for a polynomial\"");
}*/
