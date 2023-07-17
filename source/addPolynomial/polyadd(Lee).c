#define _CRT_SECURE_NO_WARNINGS/*�װ�����Ʈ������а� 202000974 ������*/
#include<stdio.h>
#include<stdlib.h>
#define MALLOC(p, s) \
if(!((p)=malloc(s)))	{ \
fprintf(stderr, "Insufficient memory"); \
exit(EXIT_FAILURE); \
}
#define COMPARE(a, b) ((a) < (b)) ? -1 : ((a)==(b)) ? 0 : 1//�� �� �Լ� 
typedef struct _polyNode* polyPointer;
typedef struct _polyNode
{/*���׽� ����ü*/
	int coef;
	int expon;
	polyPointer link;
}polyNode;
polyPointer a, b;//���׽� a, b
void attach(int coefficient, int exponent, polyPointer* ptr)//���׽� C�� �߰��ϴ� �Լ�
{
	/*coef = coefficient�̰� expon = exponent�� ���ο� ��带 �����ϰ�,
	�װ��� ptr�� ���� �����Ǵ� ��忡 ÷���Ѵ�. ptr�� �����Ͽ� �� ���ο� ��带 �����ϵ��� �Ѵ�.*/

	polyPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;

}
polyPointer padd(polyPointer a, polyPointer b)//���׽� a�� b�� ���ϴ� �Լ�
{/*a��b�� �ջ�� ���׽��� ��ȯ*/

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

	/* ����Ʈa�� ����Ʈb�� ������ ����*/
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
void ab_create(void)//���׽� a�� b�� �޸� ������ �����ϴ� �Լ�
{
	MALLOC(a, sizeof(*a));
	MALLOC(b, sizeof(*b));
}
void p_create(polyPointer* x)//���׽��� �Է¹޴� �Լ�
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
void erase(polyPointer* ptr)//���׽��� �޸� �Ҵ��� �����ϴ� �Լ�
{
	polyPointer temp;
	while (*ptr)
	{
		temp = *ptr;
		*ptr = (*ptr)->link;
		free(temp);
	}
}
void p_print(polyPointer x)//���׽��� ����ϴ� �Լ�
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
	printf("���׽� A�� �Է��ϼ���: ");
	p_create(&a);
	printf("������� ���׽�(A): ");
	p_print(a);

	printf("���׽� B�� �Է��ϼ���: ");
	p_create(&b);
	printf("������� ���׽�(B): ");
	p_print(b);
	c = padd(a, b);
	printf("���׽� A�� ���׽� B�� ���� ���׽� C: ");
	p_print(c);

	erase(&a);
	erase(&b);
	erase(&c);

	return 0;
}