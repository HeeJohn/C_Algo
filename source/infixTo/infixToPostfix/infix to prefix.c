#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 100	// 스택의 최대 크기
#define MAX_EXPR_SIZE 100	// 식의 최대 크기
typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, black, operand
}precedence;
/* lparen, rparen, plus, minus, time, divide, mod, eos, operand */

int isp[] = { 19,0,12,12,13,13,13,0,0 };		// prefix를 위해서 왼쪽 괄호와 오른쪽 괄호의 우선순위를 바꿔준다.
int icp[] = { 19,20,12,12,13,13,13,0,0 };		// prefix를 위해서 왼쪽 괄호와 오른쪽 괄호의 우선순위를 바꿔준다.

int top = -1;
int stack[MAX_STACK_SIZE];		// 스택을 저장
char infix[MAX_STACK_SIZE];		// 중위식 저장	->  전위식 저장
char pre[MAX_EXPR_SIZE];		// 계산을 위하여 뒤집은 전위식 저장 

void print_pre(void);		// 뒤집은 전위식을 다시 뒤집어 출력해주는 함수 -- 추가 
void prefix(void);			// 후위식으로 변환하는 함수
int eval(void);				// 전역 변수로 되어있는 전위식을 연산하는 함수
void push(int item);		// push 함수
int pop();					// pop 함수
char change(int token);		// 연산자를 다시 문자형으로 변환하는 함수
precedence getToken(char* symbol, int* n);		// 중위표기식을 뒤부터 읽어들여서 전위 표기식에 맞게 만든다. 
precedence getToken_2(char* symbol, int* n);	// 전위표기식을 하나씩 읽어들여 operrand와 operator(각각의 연산자)로 분리 함수 -- 추가

int main() {
	printf("중위 표기식으로 식을 입력하세요. : ");
	scanf("%s", infix);
	printf("입력받은 중위 표기식은 %s\n", infix);
	prefix();
	print_pre();	// 전위 표기식 출력 
	printf("계산한 결과 ==> %d", eval());
}
void prefix() {
	/* 수식을 전위 표기식으로 출력한다. 수식 스트링, 스택, top은 전역적이다 */
	char symbol;
	int i = 0;
	int start, end;	// 연속적인 숫자열의 시작과 끝을 가르키는 위치 
	precedence token;
	int n = strlen(infix) - 1;	// 토큰을 뒤에서부터 불러온다.
	push(eos);
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand) {
			/* 2자리 수 이상의 오퍼랜드인가 확인하고 저장 */
			end = n + 1;
			for (; token == operand; token = getToken(&symbol, &n)) {
				start = n + 1;
			}
			n++;	// 횟수보정 
			while (start <= end) 		// 값을 전달해주기 
				pre[i++] = infix[start++];
			pre[i++] = ' ';
		}

		else if (token == lparen) {
			/*토큰이 왼쪽 괄호이면 왼쪽 괄호가 나올 때까지 토큰을 팝하여 저장*/
			while (stack[top] != rparen) {	// 오른쪽 괄호이면 멈춤 
				pre[i++] = change(pop());
			}
			pop();	// 왼쪽괄호 제거 
		}
		else {
			/* symbol의 isp가 token의 icp보다 크면 symbol을 제거하고 출력시킴 */
			while (isp[stack[top]] > icp[token]) {
				pre[i++] = change(pop());
			}
			push(token);
		}
	}
	while (stack[top] != eos) {
		/*스택에 남은 토큰들을 연산자 형태로 변환한후 post에 저장*/
		pre[i++] = change(pop());
	}
}
void print_pre(void) {
	/* pre에 저장한 값을 뒤집어주면 전위표기식 */
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
			infix[count++] = ' ';	// 숫자간 혼동 방지를 위해 괄호 추가 
		}
		else {
			infix[count++] = pre[i];
		}
	}
	infix[count] = '\0'; // 문자열의 끝을 표시해야 합니다.
	printf("변환한 전위 표기식은: %s\n", infix);
}

precedence getToken(char* symbol, int* n) {
	/* 중위 표기식을 전위 표기식으로 변환하기 위해 토큰으로 분리하며
	   다음 토큰을 취한다. symbol은 문자 표현이며, token은 그것의 열거된 값으로 표현되고, 함수이름으로 반환된다. */

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
		exit(EXIT_FAILURE);
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
precedence getToken_2(char* symbol, int* n) {
	/* 전위 표기식을 계산하기 위한 함수
	다음 토큰을 취한다. symbol은 문자 표현이며, token은 그것의 열거된 값으로 표현되고, 함수이름으로 반환된다. */
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
	case  ' ':			// 공백일 경우를 추가
		return black;
	default:
		return operand;
	}
}

int eval(void) {
	/* 전위 표기식 연산하는 함수 */
	precedence token;
	char symbol;
	char temp[MAX_EXPR_SIZE];	// 2자리 수 이상의 수를 저장할 임시 공간
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
			temp[i] = '\0';		// 문자열 정수의 끝을 인식시킴 
			push(atoi(temp));	// 정수형으로 푸쉬해줌 
		}
		else {
			/* 두 피연산자를 삭제하여 연산자을 수행한 후, 그 결과를 스택에 삽입함 */
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
		token = getToken_2(&symbol, &n);	// 바로 다음 토큰 삽입 
	}
	return pop();
}