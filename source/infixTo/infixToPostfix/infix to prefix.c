#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 100	// ������ �ִ� ũ��
#define MAX_EXPR_SIZE 100	// ���� �ִ� ũ��
typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, black, operand
}precedence;
/* lparen, rparen, plus, minus, time, divide, mod, eos, operand */

int isp[] = { 19,0,12,12,13,13,13,0,0 };		// prefix�� ���ؼ� ���� ��ȣ�� ������ ��ȣ�� �켱������ �ٲ��ش�.
int icp[] = { 19,20,12,12,13,13,13,0,0 };		// prefix�� ���ؼ� ���� ��ȣ�� ������ ��ȣ�� �켱������ �ٲ��ش�.

int top = -1;
int stack[MAX_STACK_SIZE];		// ������ ����
char infix[MAX_STACK_SIZE];		// ������ ����	->  ������ ����
char pre[MAX_EXPR_SIZE];		// ����� ���Ͽ� ������ ������ ���� 

void print_pre(void);		// ������ �������� �ٽ� ������ ������ִ� �Լ� -- �߰� 
void prefix(void);			// ���������� ��ȯ�ϴ� �Լ�
int eval(void);				// ���� ������ �Ǿ��ִ� �������� �����ϴ� �Լ�
void push(int item);		// push �Լ�
int pop();					// pop �Լ�
char change(int token);		// �����ڸ� �ٽ� ���������� ��ȯ�ϴ� �Լ�
precedence getToken(char* symbol, int* n);		// ����ǥ����� �ں��� �о�鿩�� ���� ǥ��Ŀ� �°� �����. 
precedence getToken_2(char* symbol, int* n);	// ����ǥ����� �ϳ��� �о�鿩 operrand�� operator(������ ������)�� �и� �Լ� -- �߰�

int main() {
	printf("���� ǥ������� ���� �Է��ϼ���. : ");
	scanf("%s", infix);
	printf("�Է¹��� ���� ǥ����� %s\n", infix);
	prefix();
	print_pre();	// ���� ǥ��� ��� 
	printf("����� ��� ==> %d", eval());
}
void prefix() {
	/* ������ ���� ǥ������� ����Ѵ�. ���� ��Ʈ��, ����, top�� �������̴� */
	char symbol;
	int i = 0;
	int start, end;	// �������� ���ڿ��� ���۰� ���� ����Ű�� ��ġ 
	precedence token;
	int n = strlen(infix) - 1;	// ��ū�� �ڿ������� �ҷ��´�.
	push(eos);
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand) {
			/* 2�ڸ� �� �̻��� ���۷����ΰ� Ȯ���ϰ� ���� */
			end = n + 1;
			for (; token == operand; token = getToken(&symbol, &n)) {
				start = n + 1;
			}
			n++;	// Ƚ������ 
			while (start <= end) 		// ���� �������ֱ� 
				pre[i++] = infix[start++];
			pre[i++] = ' ';
		}

		else if (token == lparen) {
			/*��ū�� ���� ��ȣ�̸� ���� ��ȣ�� ���� ������ ��ū�� ���Ͽ� ����*/
			while (stack[top] != rparen) {	// ������ ��ȣ�̸� ���� 
				pre[i++] = change(pop());
			}
			pop();	// ���ʰ�ȣ ���� 
		}
		else {
			/* symbol�� isp�� token�� icp���� ũ�� symbol�� �����ϰ� ��½�Ŵ */
			while (isp[stack[top]] > icp[token]) {
				pre[i++] = change(pop());
			}
			push(token);
		}
	}
	while (stack[top] != eos) {
		/*���ÿ� ���� ��ū���� ������ ���·� ��ȯ���� post�� ����*/
		pre[i++] = change(pop());
	}
}
void print_pre(void) {
	/* pre�� ������ ���� �������ָ� ����ǥ��� */
	int i;
	int n = strlen(pre);
	int count = 0;

	for (i = n - 1; i >= 0; i--) {
		if (pre[i] >= '0' && pre[i] <= '9') {
			int start = i;
			while (i >= 0 && pre[i] != ' ')
				i--;
			int end = i + 1;
			while (end <= start)
				infix[count++] = pre[end++];
			infix[count++] = ' ';	// ���ڰ� ȥ�� ������ ���� ��ȣ �߰� 
		}
		else {
			infix[count++] = pre[i];
		}
	}
	infix[count] = '\0'; // ���ڿ��� ���� ǥ���ؾ� �մϴ�.
	printf("��ȯ�� ���� ǥ�����: %s\n", infix);
}

precedence getToken(char* symbol, int* n) {
	/* ���� ǥ����� ���� ǥ������� ��ȯ�ϱ� ���� ��ū���� �и��ϸ�
	   ���� ��ū�� ���Ѵ�. symbol�� ���� ǥ���̸�, token�� �װ��� ���ŵ� ������ ǥ���ǰ�, �Լ��̸����� ��ȯ�ȴ�. */

	*symbol = infix[(*n)--];

	switch (*symbol) {
	case '(':
		return lparen;
	case ')':
		return rparen;
	case '+':
		return plus;
	case '-':
		return minus;
	case '/':
		return divide;
	case '*':
		return times;
	case '%':
		return mod;
	case '\0':
		return eos;
	default:
		return operand;
	}
}
void push(int item) {
	if (top >= MAX_STACK_SIZE - 1) {
		/* ������ FULL�� ��� ���� ���� ��� */
		fprintf(stderr, "Stack if full, cannat add element\n");
		exit(EXIT_FAILURE);
	}
	stack[++top] = item;
}
int pop() {
	if (top < -1) {
		/* ������ Empty�� ��� ���� ���� ��� */
		fprintf(stderr, "Stack is Empty, cannot remove element");
		exit(EXIT_FAILURE);
	}
	return stack[top--];
}
char change(int token) {
	/* ���������� ����Ǿ��ִ� �����ڸ� �ٽ� ���������� ��ȯ�Ѵ�. */
	switch (token) {
	case plus:
		return '+';
	case minus:
		return '-';
	case times:
		return '*';
	case divide:
		return '/';
	case mod:
		return '%';
	case eos:
		return '\0';
	}
}
precedence getToken_2(char* symbol, int* n) {
	/* ���� ǥ����� ����ϱ� ���� �Լ�
	���� ��ū�� ���Ѵ�. symbol�� ���� ǥ���̸�, token�� �װ��� ���ŵ� ������ ǥ���ǰ�, �Լ��̸����� ��ȯ�ȴ�. */
	*symbol = pre[(*n)++];

	switch (*symbol) {
	case '(':
		return lparen;
	case ')':
		return rparen;
	case '+':
		return plus;
	case '-':
		return minus;
	case '/':
		return divide;
	case '*':
		return times;
	case '%':
		return mod;
	case '\0':
		return eos;
	case  ' ':			// ������ ��츦 �߰�
		return black;
	default:
		return operand;
	}
}

int eval(void) {
	/* ���� ǥ��� �����ϴ� �Լ� */
	precedence token;
	char symbol;
	char temp[MAX_EXPR_SIZE];	// 2�ڸ� �� �̻��� ���� ������ �ӽ� ����
	int op1, op2;
	int n = 0;
	int start, end, i = 0;
	top = 0;

	token = getToken_2(&symbol, &n);

	while (token != eos) {
		if (token == operand) {
			i = 0;
			start = n - 1;
			for (; token == operand; token = getToken_2(&symbol, &n)) {
				temp[i++] = pre[start++];
			}
			temp[i] = '\0';		// ���ڿ� ������ ���� �νĽ�Ŵ 
			push(atoi(temp));	// ���������� Ǫ������ 
		}
		else {
			/* �� �ǿ����ڸ� �����Ͽ� �������� ������ ��, �� ����� ���ÿ� ������ */
			op1 = pop();
			op2 = pop();
			switch (token) {
			case plus:
				push(op1 + op2);
				break;
			case minus:
				push(op1 - op2);
				break;
			case times:
				push(op1 * op2);
				break;
			case divide:
				push(op1 / op2);
				break;
			case mod:
				push(op1 % op2);
				break;
			}
		}
		token = getToken_2(&symbol, &n);	// �ٷ� ���� ��ū ���� 
	}
	return pop();
}