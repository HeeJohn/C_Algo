/*
    program : postfix
    name : 이창범
    last_edit : 23.07.14
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef enum {
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

char expr[MAX_STACK_SIZE];
char ppt[MAX_STACK_SIZE];
precedence stack[MAX_STACK_SIZE];
int top = -1;

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

void push(int num);
precedence pop();
precedence getToken(char* symbol, int* n);
precedence getToken1(char* symbol, int* n);
char printToken(precedence token);
void postfix();
int eval();

int main() {
    printf("중위 표기법으로 수식을 입력하세요: ");
    scanf_s("%s", expr, sizeof(expr));

    printf("후위 표기법: ");
    postfix();
    printf("결과: %s", ppt);
    int result = eval();
    printf("결과2: %d", result);

    return 0;
}

int eval() {
    char symbol;
    precedence token;
    int op1, op2;
    int n = 0;
    int top = -1;

    token = getToken1(&symbol, &n);
    while (token != eos) {
        if (token == operand) {
            push(symbol - '0');
        }
        else {
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
            default:
                fprintf(stderr, "잘못된 연산자입니다.\n");
                exit(EXIT_FAILURE);
            }
        }
        token = getToken1(&symbol, &n);
    }

    return pop();
}
void push(int num) {
    if (top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "스택이 꽉 찼습니다.\n");
        exit(EXIT_FAILURE);
    }
    stack[++top] = (precedence)num;
}

precedence pop() {
    if (top < 0) {
        fprintf(stderr, "스택이 비었습니다.\n");
        //exit(EXIT_FAILURE);
    }
    return stack[top--];
}

precedence getToken1(char* symbol, int* n) {
    *symbol = ppt[(*n)++];
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

void postfix() {
    char symbol;
    precedence token;
    int n = 0;
    char ans;
    int num = 0;
    top = 0;
    stack[0] = eos;

    for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
        if (token == operand) {
            printf("%c", symbol);
            ans = symbol;
            ppt[num] = ans;
            num++;
        }
        else if (token == rparen) {
            while (stack[top] != lparen) {
                ans = printToken(pop());
                printf("%c", ans);
                ppt[num] = ans;
                num++;
            }
            pop();
        }
        else {
            while (isp[stack[top]] >= icp[token]) {
                ans = printToken(pop());
                printf("%c", ans);
                ppt[num] = ans;
                num++;
            }
            push(token);
        }
    }
    while ((token = pop()) != eos) {
        ans = printToken(token);
        printf("%c", ans);
        ppt[num] = ans;
        num++;
    }

    printf("\n");
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