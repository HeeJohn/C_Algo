#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 100	// ������ �ִ� ũ��
#define MAX_EXPR_SIZE 100	// ���� �ִ� ũ��
typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;
/* lparen, rparen, plus, minus, time, divide, mod, eos, operand */

int isp[] = { 0,19,12,12,13,13,13,0 };
int icp[] = { 20,19,12,12,13,13,13,0 };

int i = 0;
int top = -1;
int stack[MAX_STACK_SIZE];		// ������ ����
char infix[MAX_STACK_SIZE];		// ������ ����

void postfix(void);			// ���������� ��ȯ�ϴ� �Լ�
int eval(void);				// ���� ������ �Ǿ��ִ� �������� �����ϴ� �Լ�
void push(int item);		// push �Լ�
int pop();					// pop �Լ�
char change(int token);		// �����ڸ� �ٽ� ���������� ��ȯ�ϴ� �Լ�
precedence getToken(char* symbol, int* n);		// ����ǥ����� �ϳ��� �о�鿩 operand�� operator(������ ������)�� �и� �Լ�

int main() {
	printf("���� ǥ������� ���� �Է��ϼ���. : ");
	scanf("%s", infix);
	printf("�Է¹��� ���� ǥ����� %s\n", infix);
	postfix();
	printf("��ȯ�� ���� ǥ����� : %s\n", infix);
	printf("����� ��� ==> %d", eval());
}
void postfix() {
	/* ������ ���� ǥ������� ����Ѵ�. ���� ��Ʈ��, ����, top�� �������̴� */
	char symbol;
	precedence token;
	int n = 0;
	push(eos);
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand)
			infix[i++] = symbol;	// operand�� post�� ����
		else if (token == rparen) {
			/*��ū�� ������ ��ȣ�̸� ���� ��ȣ�� ���� ������ ��ū�� ���Ͽ� ����*/
			while (stack[top] != lparen) {	// �ް�ȣ�̸� ���� 
				if (stack[top] != operand)	// ��ȣ�ȿ� �ִ°� operator�� ���
					infix[i++] = change(pop());
				else
					infix[i++] = pop();		// operand�� ���
			}
			pop();	// ���ʰ�ȣ ���� 
		}
		else {
			/* symbol�� isp�� token�� icp���� ũ�ų� ������ symbol�� �����ϰ� ��½�Ŵ */
			while (isp[stack[top]] >= icp[token]) {
				infix[i++] = change(pop());
			}
			push(token);
		}
	}
	while (stack[top] != eos) {
		/*���ÿ� ���� ��ū���� ������ ���·� ��ȯ���� post�� ����*/
		infix[i++] = change(pop());
	}
	infix[i] = '\0';	// ������ �ΰ��� �־���
}
precedence getToken(char* symbol, int* n) {
	/* ���� ǥ����� ���� ǥ������� ��ȯ�ϱ� ���� ��ū���� �и��ϸ�
	   ���� ��ū�� ���Ѵ�. symbol�� ���� ǥ���̸�, token�� �װ��� ���ŵ� ������ ǥ���ǰ�, �Լ��̸����� ��ȯ�ȴ�. */

	*symbol = infix[(*n)++];

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
		return 0;
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


int eval(void) {
	/* ���� ǥ��� �����ϴ� �Լ� */
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	top = 0;

	token = getToken(&symbol, &n);

	while (token != eos) {
		if (token == operand)
			push(symbol - '0');
		else {
			/* �� �ǿ����ڸ� �����Ͽ� �������� ������ ��, �� ����� ���ÿ� ������ */
			op2 = pop();
			op1 = pop();
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
		token = getToken(&symbol, &n);	// �ٷ� ���� ��ū ���� 
	}
	return pop();
}
