#define _CRT_SECURE_NO_WARNINGS/*항공소프트웨어공학과 202000974 이재혁*/
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
stackPointer top = NULL;// 스택의 top
char expr[MAX_TERM];
element stackEmpty(void)// 스택이 비었을 때
{
	element r1 = { -1 };
	fprintf(stderr, "Stack underflow");

	return r1;
}
void push(element item)// 스택 삽입 함수
{
	stackPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = item;
	temp->link = top;
	top = temp;
}
element pop()// 스택 삭제 함수
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
precedence getToken(char* symbol, int* n)// 토큰을 얻는 함수
{/* 다음 토큰을 취한다. symbol은 문자 표현이며, token은 그것의 열겨된 값으
	로 표현되고, 함수이름으로 반환된다. */
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
	default: return operand; /* 에러 검사는 하지 않고
								기본 값은 피연산자*/
	}
}
void saveToken(element item, int* cnt)// 토큰을 저장하는 함수
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
void translate(int n) // 괄호 변환 함수
{
	if (expr[n] == '(')
		expr[n] = ')';
	else
		expr[n] = '(';
}
void reverse(void)   // 문자열 역순 함수
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
void prefix(void)// 중위표기법 -> 전위표기법 변환 함수
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
		{/* 왼쪽 괄호가 나올 때까지 토큰들을 제거하여 출력시킴*/
			while (top->data != lparen)
				saveToken(pop(), &cnt);
			pop();
		}
		else
		{/* symbol의 isp가 token의 icp보다 크거나 같으면 symbol을 제거하고
			출력시킴. */
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
int eval(void)// 후위표기법 계산 함수
{/* 전역 변수로 되어 있는 후위 표기식 expr을 연산한다. '\0'은 수식의 끝을 나타
	낸다. stack과 top은 전역 변수이다. 함수 getToken은 토큰의 타입과 문자
	심볼을 반환한다. 피연산자는 한 문자로 된 숫자임을 가정한다. */
	reverse();
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;/* 수식 스트링을 위한 카운터*/
	token = getToken(&symbol, &n);
	while (token != eos)
	{
		if (token == operand)
			push(symbol - '0');/* 스택 삽입*/
		else
		{
			/* 두 피연산자를 삭제하여 연산을 수행한 후,
			   그 결과를 스택에 삽입함*/
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
	printf("중위 표기법: %s\n", expr);
	reverse();
	printf("뒤집은 문자열 %s\n", expr);
	printf("전위 표기법: ");
	prefix();
	printf("%s", expr);

	n = eval();

	printf("\n전위 표기법으로 계산한 값: %d\n", n);
	printf("식 계산 후: %s\n", expr);

	return 0;
}