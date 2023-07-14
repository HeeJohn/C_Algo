//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h> // value 함수의 pow를 사용하기 위한 헤더파일
//#include <string.h> // strlen 함수를 사용하기 위한 헤더파일
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
//int value(); // 배열의 문자열을 숫자로 바꿔 return 하는 함수
//int eval();
//char pop();
//void push(char item);
//void stackFull();
//void stackEmpty();
//void prefix(); // 중위식을 전위식으로 바꿔주는 함수
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
//			switch (token) { // 숫자들을 구분하기 위해 숫자 앞에 .을 stack에 쌓는다.
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
//int value() { // 일의 자리 숫자 뿐만아니라 여러 자리 숫자도 계산하기 위해 string 을 int 형으로 바꿔주는 함수
//	int op = 0;
//	int i = 0, j = 0;
//	char temp[5], q;
//	while (1) { // .이 나오기 전까지 pop을 해서 char형 배열 p에 넣어준다. 결과값이 있다면 그 결과값만 return
//		q = pop();
//		if (q >= 0 && q < 10)
//			temp[i++] = q;
//		else if (q > 10 && q != '.') 
//			return q;
//		else break;
//	}
//	i--;
//	for (int t = i; t >= 0; t--) { // p에 있는 숫자들을 int형으로 바꿔주는 함수
//		op += pow(10, t) * temp[j++];
//	}
//	return op;
//}