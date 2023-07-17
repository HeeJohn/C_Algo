/*
    program : intopo_ymh
    name : minhyuck yun
    last_edit : 23.07.09
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_STACK_SIZE 100

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand, back } precedence;

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

void push(int item);
int pop();
int eval();
precedence getToken(char* symbol, int* n);
void infixToPostfix();
void stackFull();
int stackEmpty();
void printToken(precedence token);
int changeint(int* index);

int top = -1;
int stack[MAX_STACK_SIZE];
char expr[MAX_STACK_SIZE];
int etop = 0;

int main(void)
{
    int a;
    printf("중위식 각 단위마다 공백을 포함하여 입력해주세요.\n-> ");
    scanf_s("%[^\n]s", expr, sizeof(expr));

    infixToPostfix();
    a = eval();
    printf("= %d\n", a);
}

void push(int item)
{
    if (top >= MAX_STACK_SIZE - 1)
        stackFull();
    stack[++top] = item;
}

void stackFull()
{
    fprintf(stderr, "Stack is full, cannot add element");
    exit(EXIT_FAILURE);
}

int pop()
{
    if (top == -1)
        stackEmpty();
    return stack[top--];
}

int stackEmpty()
{
    fprintf(stderr, "Stack is Empty, cannot pop element");
    exit(EXIT_FAILURE);
}

int eval()
{
    precedence token;
    char symbol;
    int value, op1, op2;
    int n = 0;
    etop = 0;
    top = -1;
    token = getToken(&symbol, &n);
    while (token != eos)
    {
        if (token == operand)
        {
            value = changeint(&n);
            push(value);
        }
        else if (token != back)
        {
            op2 = pop();
            op1 = pop();
            switch (token)
            {
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
        token = getToken(&symbol, &n);
    }
    return pop();
}

int changeint(int* index)
{
    precedence token;
    char symbol;
    int value = 0;
    int n;
    n = *index - 1; //처음 getToken에서 인덱스의 값을 늘린 상태로 왔으니 1 감소

    token = getToken(&symbol, &n);
    while (token == operand) //상수일 때만 반복
    {
        expr[etop++] = symbol; //상수를 그대로 expr에 다시 저장
        value = value * 10 + (symbol - '0'); //상수의 자릿수 만큼 10을 곱해준 뒤 value에 저장
        token = getToken(&symbol, &n);
    }

    *index = n - 1; //인덱스 갱신

    return value;
}

precedence getToken(char* symbol, int* n)
{
    *symbol = expr[(*n)++];
    switch (*symbol)
    {
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
    case ' ':
        return back; //공백을 입력 할 시 back 리턴
    default:
        return operand;
    }
}

void infixToPostfix()
{
    char symbol;
    precedence token;
    int n = 0;
    top = -1; // 스택 초기화
    push(eos); // 스택에 eos 값 추가
    token = getToken(&symbol, &n);

    while (token != eos)
    {
        if (token == operand)
        {
            printf("%d ", changeint(&n));
        }
        else if (token == back)
        {
            expr[etop++] = ' '; //공백일 시에 문자열에 공백 추가
        }
        else if (token == rparen)
        {
            while (stack[top] != lparen)
            {
                printToken((precedence)pop());
                etop++;
            }
            pop(); // 왼쪽 괄호 버림
        }
        else
        {
            while (isp[stack[top]] > icp[token] && stack[top] != lparen)
            {
                printToken((precedence)pop());
                etop++;
            }
            push(token);
        }

        token = getToken(&symbol, &n);
    }

    while ((token = (precedence)pop()) != eos)
    {
        printToken(token);
        etop++;
    }

    printf("\n");
}


void printToken(precedence token)
{
    switch (token)
    {
    case plus:
        printf("+ ");
        expr[etop] = '+';
        break;
    case minus:
        printf("- ");
        expr[etop] = '-';
        break;
    case times:
        printf("* ");
        expr[etop] = '*';
        break;
    case divide:
        printf("/ ");
        expr[etop] = '/';
        break;
    case lparen:
        printf("( ");
        expr[etop] = '(';
        break;
    case rparen:
        printf(") ");
        expr[etop] = ')';
        break;
    default:
        break;
    }
}