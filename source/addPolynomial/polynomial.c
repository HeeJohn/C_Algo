/*
	program : Polynomial
	name : Tae Min
	Last_edit : 2023-07-14
*/

#include <stdio.h>
#include <stdlib.h>
#define compare(x,y) (((x) < (y)) ? -1: ((x) == (y)) ? 0 : 1)
#define malloc(p,s)\
	if(!((p)=malloc(s))) {\
		fprintf(stderr,"insufficient memory");\
		exit(1);\
	}

typedef struct polynode* polypointer;
typedef struct polynode {
	float coef;
	int expon;
	polypointer link;
}polynode;

polypointer padd(polypointer a1, polypointer b1);
void attach(float coefficient, int exponent, polypointer* ptr);
void printpolynomial(polypointer c);
void input(polypointer ptr); // ���׽��� �Է¹ޱ� ���� �Լ�

void main() {
	polypointer a, b, rear;
	polypointer c;
	malloc(a, sizeof(*a));
	malloc(b, sizeof(*b));
	malloc(c, sizeof(*c));

	rear = a; // a�� �ּҸ� ��Ű�� ���� rear�� a�� �ּ� ���� �ְ� rear�� Ȱ���Ѵ�.
	printf("input first polynomial\n");
	input(rear); // ù ��° ���׽� �Է�
	a = a->link;

	rear = b; // b�� �ּҸ� ��Ű�� ���� rear�� b�� �ּ� ���� �ְ� rear�� Ȱ���Ѵ�.
	printf("input second polynomial\n");
	input(rear); // �� ��° ���׽� �Է�
	b = b->link;

	c = padd(a, b);
	printpolynomial(c);


	free(c);
	free(a);
	free(b);
	free(rear);
}

polypointer padd(polypointer a1, polypointer b1) {
	polypointer c, rear1, temp;
	int sum;
	malloc(rear1, sizeof(*rear1));
	c = rear1;
	while (a1 && b1)
		switch (compare(a1->expon, b1->expon)) {
		case -1:
			attach(b1->coef, b1->expon, &rear1);
			b1 = b1->link;
			break;
		case 0:
			sum = a1->coef + b1->coef;
			if (sum) attach(sum, a1->expon, &rear1);
			a1 = a1->link;
			b1 = b1->link;
			break;
		case 1:
			attach(a1->coef, a1->expon, &rear1);
			a1 = a1->link;
		}

	for (; a1; a1 = a1->link) attach(a1->coef, a1->expon, &rear1);
	for (; b1; b1 = b1->link) attach(b1->coef, b1->expon, &rear1);

	rear1->link = NULL;
	temp = c;
	c = c->link;
	free(temp);
	return c;
}

void attach(float coefficient, int exponent, polypointer* ptr) {
	polypointer temp;
	malloc(temp, sizeof(*temp));
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;
}

void printpolynomial(polypointer c) {
	for (; c; c = c->link) {
		printf(" %.1fx^%d ", c->coef, c->expon);
		if (c->link != NULL) {
			printf(" + ");
		}
	}
}

void input(polypointer ptr) { // ���׽��� �Է¹ޱ� ���� �Լ�
	int _expon; // ���� �κ�
	float _coef; // ��� �κ�
	while (1) { // ���� �κа� ��� �κ��� �Է¹ް� attach�Լ��� �̿��Ͽ� �����Ѵ�.
		scanf_s("%f %d", &_coef, &_expon);
		attach(_coef, _expon, &ptr);
		if (_expon == 0) break;
	}
	ptr->link = NULL;
}