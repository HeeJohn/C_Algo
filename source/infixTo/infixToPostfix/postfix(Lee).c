#define _CRT_SECURE_NO_WARNINGS/*�װ�����Ʈ������а� 202000974 ������*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_TERM 100
#define MALLOC(p, s) \
if(!((p)=malloc(s)))	{ \
fprintf(stderr, "Insufficient memory"); \
exit(EXIT_FAILURE); \
}
int isp[] = { 0, 20, 12, 12, 13, 13, 13, 0 };
int icp[] = { 19, 20, 12, 12, 13, 13, 13, 0 };
typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;
typedef int element;
typedef struct _stack* stackPointer;
typedef struct _stack
{
	element data;
	stackPointer link;
}stack;
stackPointer top = NULL;// ������ top
char expr[MAX_TERM];
element stackEmpty(void)// ������ ����� ��
{
	element r1 = { -1 };
	fprintf(stderr, "Stack underflow");

	return r1;
}
void push(element item)// ���� ���� �Լ�
{
	stackPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = item;
	temp->link = top;
	top = temp;
}
element pop()// ���� ���� �Լ�
{
	stackPointer temp = top;
	element item;
	if (!temp)
		return stackEmpty();
	item = temp->data;
	top = temp->link;
	free(temp);
	return item;
}
precedence getToken(char* symbol, int* n)// ��ū�� ��� �Լ�
{/* ���� ��ū�� ���Ѵ�. symbol�� ���� ǥ���̸�, token�� �װ��� ���ܵ� ����
	�� ǥ���ǰ�, �Լ��̸����� ��ȯ�ȴ�. */
	*symbol = expr[(*n)++];
	switch (*symbol)
	{
	case'(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand; /* ���� �˻�� ���� �ʰ�
								�⺻ ���� �ǿ�����*/
	}
}
void saveToken(element item, int* cnt)// ��ū�� �����ϴ� �Լ�
{
	switch (item)
	{
	case plus:
		expr[(*cnt)++] = '+';
		break;
	case minus:
		expr[(*cnt)++] = '-';
		break;
	case divide:
		expr[(*cnt)++] = '/';
		break;
	case times:
		expr[(*cnt)++] = '*';
		break;
	case mod:
		expr[(*cnt)++] = '%';
		break;
	}
}
void translate(int n) // ��ȣ ��ȯ �Լ�
{
	if (expr[n] == '(')
		expr[n] = ')';
	else
		expr[n] = '(';
}
void reverse(void)   // ���ڿ� ���� �Լ�
{
	int i;
	int len = strlen(expr);
	char temp;

	for (i = 0;i < len / 2;i++)
	{

		temp = expr[i];
		expr[i] = expr[len - 1 - i];
		expr[len - 1 - i] = temp;

		if (expr[i] == '(' || expr[i] == ')')
			translate(i);

		if (expr[len - i - 1] == '(' || expr[len - i - 1] == ')')
			translate(len - i - 1);
	}

	if (expr[i] == '(' || expr[i] == ')')
		translate(i);
}
void prefix(void)// ����ǥ��� -> ����ǥ��� ��ȯ �Լ�
{
	char symbol;
	precedence token;
	int n = 0;
	int cnt = 0;
	push(eos);

	for (token = getToken(&symbol, &n); token != eos;token = getToken(&symbol, &n))
	{
		if (token == operand)
			expr[cnt++] = symbol;
		else if (token == rparen)
		{/* ���� ��ȣ�� ���� ������ ��ū���� �����Ͽ� ��½�Ŵ*/
			while (top->data != lparen)
				saveToken(pop(), &cnt);
			pop();
		}
		else
		{/* symbol�� isp�� token�� icp���� ũ�ų� ������ symbol�� �����ϰ�
			��½�Ŵ. */
			while (isp[top->data] >= icp[token])
				saveToken(pop(), &cnt);

			push(token);
		}
	}
	while ((token = pop()) != eos)
		saveToken(token, &cnt);

	expr[cnt] = NULL;
	reverse();
}
int eval(void)// ����ǥ��� ��� �Լ�
{/* ���� ������ �Ǿ� �ִ� ���� ǥ��� expr�� �����Ѵ�. '\0'�� ������ ���� ��Ÿ
	����. stack�� top�� ���� �����̴�. �Լ� getToken�� ��ū�� Ÿ�԰� ����
	�ɺ��� ��ȯ�Ѵ�. �ǿ����ڴ� �� ���ڷ� �� �������� �����Ѵ�. */
	reverse();
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;/* ���� ��Ʈ���� ���� ī����*/
	token = getToken(&symbol, &n);
	while (token != eos)
	{
		if (token == operand)
			push(symbol - '0');/* ���� ����*/
		else
		{
			/* �� �ǿ����ڸ� �����Ͽ� ������ ������ ��,
			   �� ����� ���ÿ� ������*/
			op2 = pop();
			op1 = pop();
			switch (token)
			{
			case plus: push(op1 + op2);
				break;
			case minus: push(op1 - op2);
				break;
			case times: push(op1 * op2);
				break;
			case divide: push(op1 / op2);
				break;
			case mod: push(op1 % op2);
			}
		}
		token = getToken(&symbol, &n);
	}
	reverse();
	return pop();
}

int main()
{
	int n;
	scanf("%s", expr);
	printf("���� ǥ���: %s\n", expr);
	reverse();
	printf("������ ���ڿ� %s\n", expr);
	printf("���� ǥ���: ");
	prefix();
	printf("%s", expr);

	n = eval();

	printf("\n���� ǥ������� ����� ��: %d\n", n);
	printf("�� ��� ��: %s\n", expr);

	return 0;
}