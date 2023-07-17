/*
    name : 중위식->후위식
    last_edit : 23.07.11
*/
#include <stdio.h>
#include <stdlib.h>

#define CRT_SECURE_NO_WARNINGS
#define MAX_STACK 100

//중위 표기식, 스택 배열 및 인덱스 전역변수 
typedef char element;
element infix[MAX_STACK];
element stack[MAX_STACK];
int top;

// 스택 함수
void stackfull()
{
    fprintf(stderr, "stack is full\n");
    exit(EXIT_FAILURE);
}
void stackempty()
{
    fprintf(stderr, "stack is empty\n");
    exit(EXIT_FAILURE);
}
void push(element item)
{
    if (top >= MAX_STACK)
        stackfull();
    stack[++top] = item;
}
element pop()
{
    if (top == -1)
        stackempty();
    return stack[top--];
}

int isp[] = { 0,19,12,12,13,13,13,0 };
int icp[] = { 20,19,12,12,13,13,13,0 };

typedef enum
{
    lparen,
    rparen,
    plus,
    minus,
    times,
    devides,
    mod,
    eos,
    operand
}precedence;

void printtoken(element s, int p)    // postfix에서 index를 받아와서 저장
{
    switch (s)
    {
    case 2: printf("+"); infix[p] = '+'; break;     
    case 3: printf("-"); infix[p] = '-'; break;
    case 4: printf("*"); infix[p] = '*'; break;
    case 5: printf("/"); infix[p] = '/'; break;
    case 6: printf("%%"); infix[p] = '%'; break;
    default:
        break;
    }
}

precedence gettoken(char* symbol, int* n)
{
    *symbol = infix[(*n)++];
    switch (*symbol)
    {
    case'(': return lparen;
    case')': return rparen;
    case'+': return plus;
    case'-': return minus;
    case'*': return times;
    case'/': return devides;
    case'%': return mod;
    case'\0': return eos;
    default: return operand;
    }
}

void postfix()
{
    char symbol;
    precedence token;
    int n = 0;
    int p = 0;  // infix를 postfix로 변환하는 index
    top = 0;
    stack[0] = eos;
    for (token = gettoken(&symbol, &n); token != eos; token = gettoken(&symbol, &n))
    {
        if (token == operand)
        {
            printf("%c", symbol);
            infix[p++] = symbol;    // infix의 첫 번째 배열에 symbol 저장
        }
        else if (token == rparen)
        {
            while (stack[top] != lparen)
                printtoken(pop(), p++);     
            pop();
        }
        else
        {
            while (isp[stack[top]] >= icp[token])
                printtoken(pop(), p++);
            push(token);
        }
    }
    while ((token = pop()) != eos)
        printtoken(token, p++);
    for (p; p < MAX_STACK; p++)     // 괄호를 포함하였을 때 남아있는 값들을 지우기 위한 반복문
        infix[p] = '\0';
    printf("\n");
}

int eval()
{
    precedence token;
    char symbol;
    int op1, op2;
    int n = 0;
    top = 0;
    token = gettoken(&symbol, &n);
    while (token != eos)
    {
        if (token == operand)
            push(symbol - '0');
        else
        {
            op2 = pop();
            op1 = pop();
            switch (token)
            {
            case plus: push(op1 + op2); break;
            case minus: push(op1 - op2); break;
            case times: push(op1 * op2); break;
            case devides:push(op1 / op2); break;
            case mod:push(op1 % op2); break;
            }
        }
        token = gettoken(&symbol, &n);
    }
    return pop();
}

void main()
{
    int sum;
    printf("Input infix : ");
    scanf_s("%s", infix, MAX_STACK);
    postfix();
    sum = eval();
    printf("Result is %d\n", sum);
}