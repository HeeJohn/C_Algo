//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h> // value �Լ��� pow�� ����ϱ� ���� �������
//#include <string.h> // strlen �Լ��� ����ϱ� ���� �������
//#define MAX_SIZE 100
//
//typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;
//
//int isp[] = { 0,19,12,12,13,13,13,0 };
//int icp[] = { 20,19,12,12,13,13,13,0 };
//
//char stack[MAX_SIZE];
//char expr[MAX_SIZE] = { 0, };
//int top = 0;
//
//int value(); // �迭�� ���ڿ��� ���ڷ� �ٲ� return �ϴ� �Լ�
//int eval();
//char pop();
//void push(char item);
//void stackFull();
//void stackEmpty();
//void prefix(); // �������� ���������� �ٲ��ִ� �Լ�
//char printToken(precedence item);
//precedence getToken(char* symbol, int* n);
//
//void main() {
//	int result, len;
//	printf("input data( !! first data must be a ' ' !! ) : ");
//	scanf_s("%[^\n]s", expr, sizeof(expr));
//	prefix();
//	printf("%s\n", expr);
//	result = eval();
//	printf("%4d\n", result);
//}
//
//void push(char item) {
//	if (top == MAX_SIZE)
//		stackFull();
//	stack[++top] = item;
//}
//
//char pop() {
//	if (top == -1)
//		stackEmpty();
//	return stack[top--];
//}
//
//void stackFull() {
//	fprintf(stderr, "Stack is Full");
//	exit(1);
//}
//
//void stackEmpty() {
//	fprintf(stderr, "Stack is Empty");
//	exit(1);
//}
//
//void prefix() {
//	char symbol;
//	precedence token;
//	int n = strlen(expr) - 1;
//	int _top = 0;
//	int i = n;
//	stack[0] = eos;
//	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
//		if (token == operand || token == '.') {
//			expr[i--] = symbol;
//		}
//		else if (token == rparen) {
//			while (stack[top] != lparen) {
//				expr[i--] = printToken(pop());
//			}
//			expr[i--] = printToken(pop());
//		}
//		else {
//			while (isp[stack[top]] > icp[token]) {
//				expr[i--] = printToken(pop());
//			}
//			push(token);
//		}
//	}
//	while ((token = pop()) != eos) {
//		expr[i--] = printToken(token);
//	}
//}
//
//char printToken(precedence item) {
//	switch (item) {
//	case plus: return '+';
//	case minus: return '-';
//	case times: return '*';
//	case divide: return '/';
//	case mod: return '%';
//	case lparen: return '(';
//	case rparen: return ')';
//	}
//}
//
//precedence getToken(char* symbol, int* n) {
//	*symbol = expr[(*n)--];
//	switch (*symbol) {
//	case '(': return lparen;
//	case ')': return rparen;
//	case '+': return plus;
//	case '-': return minus;
//	case '*': return times;
//	case '/': return divide;
//	case '%': return mod;
//	case ' ': return eos;
//	case '.': return '.';
//	default: return operand;
//	}
//}
//
//int eval() {
//	precedence token;
//	char symbol;
//	int op1, op2;
//	int n = strlen(expr);
//	token = getToken(&symbol, &n);
//	while (token != eos) {
//		if (token == operand || token == '.')
//			if (token == '.')
//				push('.');
//			else
//				push(symbol - '0');
//		else {
//			op1 = value();
//			op2 = value();
//			switch (token) { // ���ڵ��� �����ϱ� ���� ���� �տ� .�� stack�� �״´�.
//			case plus:
//				push('.');
//				push(op1 + op2);
//				break;
//			case minus:
//				push('.');
//				push(op1 - op2);
//				break;
//			case times:
//				push('.');
//				push(op1 * op2);
//				break;
//			case divide:
//				push('.');
//				push(op1 / op2);
//				break;
//			case mod:
//				push('.');
//				push(op1 % op2);
//			}
//		}
//		token = getToken(&symbol, &n);
//	}
//	return pop();
//}
//
//int value() { // ���� �ڸ� ���� �Ӹ��ƴ϶� ���� �ڸ� ���ڵ� ����ϱ� ���� string �� int ������ �ٲ��ִ� �Լ�
//	int op = 0;
//	int i = 0, j = 0;
//	char temp[5], q;
//	while (1) { // .�� ������ ������ pop�� �ؼ� char�� �迭 p�� �־��ش�. ������� �ִٸ� �� ������� return
//		q = pop();
//		if (q >= 0 && q < 10)
//			temp[i++] = q;
//		else if (q > 10 && q != '.') 
//			return q;
//		else break;
//	}
//	i--;
//	for (int t = i; t >= 0; t--) { // p�� �ִ� ���ڵ��� int������ �ٲ��ִ� �Լ�
//		op += pow(10, t) * temp[j++];
//	}
//	return op;
//}