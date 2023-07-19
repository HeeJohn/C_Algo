#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 100

char expr[MAX_SIZE];//중위식을 입력받을 변수
char another_expr[MAX_SIZE];//중위식으로 입력받은 함수를 후위식으로 저장할 변수

typedef enum precedence {
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;//enum 구조체로 연산자들 ,피연산자 초기화

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };//스택에 쌓일때 연산자들의 우선순위
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };//스택에서 나올때 연산자들의 우선순위

int stack[MAX_SIZE];//중위식->후위식변환 할 때 연산자들이 쌓일, 후위식에서 계산할때 피연산자가 쌓일 스택
int top = -1;//스택의 시작을 -1로 초기화

void push(int item) {
    stack[++top] = item;
}//스택에 item을 쌓는 함수

int pop() {
    return stack[top--];
}//스택에서 값을 빼내고 그 값을 반환하는 함수

precedence gettoken(char* symbol, int* n, char* exprr) {
    *symbol = exprr[(*n)++];
    switch (*symbol) {
    case '(': return lparen;
    case ')': return rparen;
    case '+': return plus;
    case '-': return minus;
    case '*': return times;
    case '/': return divide;
    case '%': return mod;
    case '\0': return eos;
    default: return operand;
    }//문자형의 연산자(symbol)를 수치화해서 반환하는 함수, 단 피연산자일경우 그대로 반환
}

char printToken(int tOken) {
    switch (tOken) {
    case lparen:return'(';
    case rparen:return')';
    case plus:return'+';
    case minus:return'-';
    case times:return'*';
    case divide:return'/';
    case mod:return'%';
    case eos:return'\0';
    }//precedence형으로 받은 파라미터를 문자형으로 출력해주는 함수
}

void postfix() {//중위식->후위식으로 바꾸는 함수
    char symbol;
    precedence token;
    int n = 0;
    top = 0;
    stack[0] = eos;//맨처음 스택을 빈칸으로 쌓는다
    int i = 0;
    for (token = gettoken(&symbol, &n, expr); token != eos; token = gettoken(&symbol, &n, expr)) {
        if (token == operand) {//피연산자일때

            expr[i++] = symbol;
        }//피연산자들을 문자열 변수에 저장한다
        else if (token == rparen) {//  ")"일 때 
            while (stack[top] != lparen) {
                expr[i++] = printToken(pop());
            }// 스택에 빼내는 연산자가 "(" 일때 까지 스택의 연산자들을 계속 빼면서 문자열 변수에 저장한다
            pop();
        }
        else {
            while (isp[stack[top]] >= icp[token]) {
                expr[i++] = printToken(pop());
            }//나머지 연산자들 중에서 우선순위 높은 연산자들을 스택에서 빼면서 문자열 변수에 저장한다
            push(token);
        }
    }

    while ((token = (precedence)pop()) != eos) {//스택에 있는 나머지 연산자들을 스택에서 빼면서 문자열 변수에 저장한다
        expr[i++] = printToken(token);
    }

    printf("\n");
}

int eval() {//후위식을 계산하는 함수
    precedence token;
    char symbol;
    int op1, op2;
    int n = 0;

    token = gettoken(&symbol, &n, expr);//문자형의 연산자(symbol)를 수치화하는 함수를 이용해서 토큰 변수 초기화
    while (token != eos) {
        if (token == operand) {//피연산자일경우 문자형으로 되있는 숫자를 정수형 숫자로 만든뒤 스택에 넣는다
            push(symbol - '0');
        }
        else {
            op2 = pop();//스택에서 꺼낸 피연산자
            op1 = pop();//스택에서 꺼낸 피연산자
            switch (token) {//토큰이 어떤 연산자인지에 따라서 op1과op2를 계산해서 스택에 넣는다 
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
            default:
                break;
            }
        }
        token = gettoken(&symbol, &n, expr);//문자형의 연산자(symbol)를 수치화하는 함수를 이용해서 토큰 변수 초기화
    }
    return pop();//계산 결과를 반환한다.
}

int main() {
    printf("Enter the infix expression: ");
    scanf_s("%s", expr, 100);//중위식을 입력받는다

    postfix();//중위식->후위식 변환 함수
    printf("postfix = %s \n", expr);
    printf("The answer is %d \n", eval());
    return 0;
}
/*#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack* stack) {
    stack->top = -1;
}

bool isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, char item) {
    if (isFull(stack)) {
        printf("Stack overflow!\n");
        exit(EXIT_FAILURE);
    }
    stack->items[++stack->top] = item;
}

char pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow!\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top--];
}

char peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top];
}

int precedence(char operator_) {
    if (operator_ == '+' || operator_ == '-')
        return 1;
    else if (operator_ == '*' || operator_ == '/')
        return 2;
    else if (operator_ == '^')
        return 3;
    else
        return 0;
}

bool isOperator(char symbol) {
    return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^');
}

void reverseString(char* str) {
    int length = strlen(str);
    int i, j;
    char temp;

    for (i = 0, j = length - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

void infixToPrefix(char* expression, char* prefix) {
    Stack stack;
    initialize(&stack);
    int i, j;
    char symbol, topSymbol;

    reverseString(expression);

    for (i = 0, j = 0; expression[i] != '\0'; i++) {
        symbol = expression[i];

        if (isdigit(symbol)) {
            prefix[j++] = symbol;
        }
        else if (symbol == ')') {
            push(&stack, symbol);
        }
        else if (symbol == '(') {
            while ((topSymbol = pop(&stack)) != ')')
                prefix[j++] = topSymbol;
        }
        else if (isOperator(symbol)) {
            while (!isEmpty(&stack) && precedence(peek(&stack)) > precedence(symbol))
                prefix[j++] = pop(&stack);
            push(&stack, symbol);
        }
    }

    while (!isEmpty(&stack))
        prefix[j++] = pop(&stack);

    prefix[j] = '\0';

    reverseString(prefix);
}

int main() {
    char infix[MAX_SIZE];
    char prefix[MAX_SIZE];

    printf("Enter an infix expression: ");
    fgets(infix, sizeof(infix), stdin);

    infixToPrefix(infix, prefix);

    printf("Prefix expression: %s\n", prefix);

    return 0;
}*/