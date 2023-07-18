#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 100	// 스택의 최대 크기
#define MAX_EXPR_SIZE 100	// 식의 최대 크기
typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;
/* lparen, rparen, plus, minus, time, divide, mod, eos, operand */

int isp[] = { 0,19,12,12,13,13,13,0 };
int icp[] = { 20,19,12,12,13,13,13,0 };

int i = 0;
int top = -1;
int stack[MAX_STACK_SIZE];		// 스택을 저장
char infix[MAX_STACK_SIZE];		// 중위식 저장

void postfix(void);			// 후위식으로 변환하는 함수
int eval(void);				// 전역 변수로 되어있는 후위식을 연산하는 함수
void push(int item);		// push 함수
int pop();					// pop 함수
char change(int token);		// 연산자를 다시 문자형으로 변환하는 함수
precedence getToken(char* symbol, int* n);		// 중위표기식을 하나씩 읽어들여 operand와 operator(각각의 연산자)로 분리 함수

int main() {
	printf("중위 표기식으로 식을 입력하세요. : ");
	scanf("%s", infix);
	printf("입력받은 중위 표기식은 %s\n", infix);
	postfix();
	printf("변환한 후위 표기식은 : %s\n", infix);
	printf("계산한 결과 ==> %d", eval());
}
void postfix() {
	/* 수식을 후위 표기식으로 출력한다. 수식 스트링, 스택, top은 전역적이다 */
	char symbol;
	precedence token;
	int n = 0;
	push(eos);
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand)
			infix[i++] = symbol;	// operand면 post에 저장
		else if (token == rparen) {
			/*토큰이 오른쪽 괄호이면 왼쪽 괄호가 나올 때까지 토큰을 팝하여 저장*/
			while (stack[top] != lparen) {	// 왼괄호이면 멈춤 
				if (stack[top] != operand)	// 괄호안에 있는게 operator인 경우
					infix[i++] = change(pop());
				else
					infix[i++] = pop();		// operand인 경우
			}
			pop();	// 왼쪽괄호 제거 
		}
		else {
			/* symbol의 isp가 token의 icp보다 크거나 같으면 symbol을 제거하고 출력시킴 */
			while (isp[stack[top]] >= icp[token]) {
				infix[i++] = change(pop());
			}
			push(token);
		}
	}
	while (stack[top] != eos) {
		/*스택에 남은 토큰들을 연산자 형태로 변환한후 post에 저장*/
		infix[i++] = change(pop());
	}
	infix[i] = '\0';	// 마지막 널값을 넣어줌
}
precedence getToken(char* symbol, int* n) {
	/* 중위 표기식을 후위 표기식으로 변환하기 위해 토큰으로 분리하며
	   다음 토큰을 취한다. symbol은 문자 표현이며, token은 그것의 열거된 값으로 표현되고, 함수이름으로 반환된다. */

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
		/* 스택이 FULL일 경우 오류 문구 출력 */
		fprintf(stderr, "Stack if full, cannat add element\n");
		exit(EXIT_FAILURE);
	}
	stack[++top] = item;
}
int pop() {
	if (top < -1) {
		/* 스택이 Empty일 경우 오류 문구 출력 */
		fprintf(stderr, "Stack is Empty, cannot remove element");
		return 0;
	}
	return stack[top--];
}
char change(int token) {
	/* 정수형으로 저장되어있는 연산자를 다시 문자형으로 변환한다. */
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
	/* 후위 표기식 연산하는 함수 */
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
			/* 두 피연산자를 삭제하여 연산자을 수행한 후, 그 결과를 스택에 삽입함 */
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
		token = getToken(&symbol, &n);	// 바로 다음 토큰 삽입 
	}
	return pop();
}
