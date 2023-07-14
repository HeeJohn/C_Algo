#define _CRT_SECURE_NO_WARNINGS/*항공소프트웨어공학과 202000974 이재혁*/
#include<stdio.h>
#include<stdlib.h>
#define MALLOC(p, s) \
if(!((p)=malloc(s)))	{ \
fprintf(stderr, "Insufficient memory"); \
exit(EXIT_FAILURE); \
}
#define COMPARE(a, b) ((a) < (b)) ? -1 : ((a)==(b)) ? 0 : 1//값 비교 함수 
typedef struct _polyNode* polyPointer;
typedef struct _polyNode
{/*다항식 구조체*/
	int coef;
	int expon;
	polyPointer link;
}polyNode;
polyPointer a, b;//다항식 a, b
void attach(int coefficient, int exponent, polyPointer* ptr)//다항식 C에 추가하는 함수
{
	/*coef = coefficient이고 expon = exponent인 새로운 노드를 생성하고,
	그것을 ptr에 의해 참조되는 노드에 첨가한다. ptr을 갱신하여 이 새로운 노드를 참조하도록 한다.*/

	polyPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;

}
polyPointer padd(polyPointer a, polyPointer b)//다항식 a와 b를 더하는 함수
{/*a와b가 합산된 다항식을 반환*/

	polyPointer c, rear, temp;
	int sum;
	MALLOC(rear, sizeof(*rear));
	c = rear;
	while (a && b)
		switch (COMPARE(a->expon, b->expon))
		{
		case -1:
			attach(b->coef, b->expon, &rear);
			b = b->link;
			break;
		case 0:
			sum = a->coef + b->coef;
			if (sum) attach(sum, a->expon, &rear);
			a = a->link;b = b->link;
			break;
		case 1:
			attach(a->coef, a->expon, &rear);
			a = a->link;
		}

	/* 리스트a와 리스트b의 나머지 복사*/
	for (;a;a = a->link)
		attach(a->coef, a->expon, &rear);
	for (;b;b = b->link)
		attach(b->coef, b->expon, &rear);
	rear->link = NULL;
	temp = c;
	c = c->link;
	free(temp);

	return c;
}
void ab_create(void)//다항식 a와 b의 메모리 공간을 생성하는 함수
{
	MALLOC(a, sizeof(*a));
	MALLOC(b, sizeof(*b));
}
void p_create(polyPointer* x)//다항식을 입력받는 함수
{
	polyPointer fp;
	int coef, expon;

	fp = *x;
	do
	{
		scanf("%d %d", &coef, &expon);
		attach(coef, expon, x);
	} while (expon);
	(*x)->link = NULL;
	*x = fp->link;
	free(fp);
}
void erase(polyPointer* ptr)//다항식의 메모리 할당을 해제하는 함수
{
	polyPointer temp;
	while (*ptr)
	{
		temp = *ptr;
		*ptr = (*ptr)->link;
		free(temp);
	}
}
void p_print(polyPointer x)//다항식을 출력하는 함수
{
	polyPointer p;
	p = x;
	while (p)
	{
		if (p->link)
			printf(" %dx^%d +", p->coef, p->expon);
		else
			printf(" %d\n", p->coef);
		p = p->link;
	}
}
int main()
{
	polyPointer c;

	ab_create();
	printf("다항식 A를 입력하세요: ");
	p_create(&a);
	printf("만들어진 다항식(A): ");
	p_print(a);

	printf("다항식 B를 입력하세요: ");
	p_create(&b);
	printf("만들어진 다항식(B): ");
	p_print(b);
	c = padd(a, b);
	printf("다항식 A와 다항식 B를 더한 다항식 C: ");
	p_print(c);

	erase(&a);
	erase(&b);
	erase(&c);

	return 0;
}