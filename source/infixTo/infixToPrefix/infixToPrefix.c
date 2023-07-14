/*
    program : prefix
    name : 이창범
    last_edit : 23.07.14
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
typedef enum {
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

char expr[MAX_STACK_SIZE];
precedence stack[MAX_STACK_SIZE];
int top = -1;
int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };
void push(int token);
precedence pop();
precedence getToken(char* symbol, int* n);
char printToken(precedence token);
void reverseString(char* str);
void prefix();
int eval();
void main() {
    printf("중위 표기법으로 수식을 입력하세요: ");
    scanf_s("%s", expr, sizeof(expr) * 2);

    printf("전위 표기법: ");
    prefix();
    printf("\n계산 결과: %d", eval());
}

void push(int token) {
    if (top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "스택이 꽉 찼습니다.\n");
        exit(EXIT_FAILURE);
    }
    stack[++top] = (precedence)token;
}
precedence pop() {
    if (top < 0) {
        fprintf(stderr, "스택이 비었습니다.\n");
        exit(EXIT_FAILURE);
    }
    return stack[top--];
}
precedence getToken(char* symbol, int* n) {
    *symbol = expr[(*n)++];
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
    }
}
char printToken(precedence token) {
    switch (token) {
    case lparen:
        return '(';
    case rparen:
        return ')';
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
    default:
        return '\0';
    }
}
void reverseString(char* str) {
    int left = 0;
    int right = strlen(str) - 1;
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}
void prefix() {
    char symbol;
    precedence token;
    int n = 0;
    int num = 0;
    bool isNumber = false;
    top = 0;
    stack[0] = eos;

    // 입력된 중위 표기식을 뒤집음
    reverseString(expr);

    for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
        if (token == operand) {
            if (isNumber) {
                expr[num++] = symbol;
            }
            else {
                isNumber = true;
                expr[num++] = symbol;
            }
        }
        else if (token == rparen) {
            push(token);
        }
        else if (token == lparen) {
            while (stack[top] != rparen) {
                expr[num++] = printToken(pop());
            }
            pop();
        }
        else {
            while (isp[stack[top]] > icp[token]) {
                expr[num++] = printToken(pop());
            }
            push(token);
            isNumber = false;
        }
    }

    while (top != -1) {
        expr[num++] = printToken(pop());
    }

    // 변환된 전위 표기식을 다시 뒤집음
    reverseString(expr);
    expr[num] = '\0'; // 문자열 종료 문자 추가

    printf("%s", expr);
}
int eval() {
    char symbol;
    int op1, op2;
    int n = 0;
    top = -1;

    for (int i = strlen(expr) - 1; i >= 0; i--) {
        symbol = expr[i];
        if (symbol >= '0' && symbol <= '9') {
            push(symbol - '0');
        }
        else if (symbol == ' ') {
            continue;
        }
        else {
            op1 = pop();
            op2 = pop();

            switch (symbol) {
            case '+':
                push(op1 + op2);
                break;
            case '-':
                push(op1 - op2);
                break;
            case '*':
                push(op1 * op2);
                break;
            case '/':
                push(op1 / op2);
                break;
            case '%':
                push(op1 % op2);
                break;
            default:
                fprintf(stderr, "잘못된 연산자입니다.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    return pop();
}