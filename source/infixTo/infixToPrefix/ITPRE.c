/*
    name : 중위식->전위식
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

int isp[] = { 19,0,12,12,13,13,13,0 };  // 기존의 왼쪽괄호와 오른쪽 괄호의 연산자 우선순위를 변경
int icp[] = { 19,20,12,12,13,13,13,0 };

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

void printtoken(element s, int p)    
{
    switch (s)
    {
    case 2: /*printf("+");*/ infix[p] = '+'; break;
    case 3: /*printf("-");*/ infix[p] = '-'; break;
    case 4: /*printf("*");*/ infix[p] = '*'; break;
    case 5: /*printf("/");*/ infix[p] = '/'; break;
    case 6: /*printf("%%");*/ infix[p] = '%'; break;
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

void reverse()  // infix 역순으로 저장하는 함수
{
    int i = 0;
    element temp;
    for (i; i < MAX_STACK, infix[i] != '\0'; i++);
    i--;
    for (int j = 0; j < i; j++)
    {
        temp = infix[j];
        infix[j] = infix[i];
        infix[i--] = temp;
    }
}
void prefix()
{
    reverse();
    char symbol;
    precedence token;
    int n = 0;
    int p = 0;  
    top = 0;
    stack[0] = eos;
    for (token = gettoken(&symbol, &n); token != eos; token = gettoken(&symbol, &n))
    {
        if (token == operand)
        {
            //printf("%c", symbol);
            infix[p++] = symbol;    
        }
        else if (token == lparen)   // 왼쪽 괄호면 오른쪽 괄호가 나올때까지 스택안의 연산자를 pop
        {
            while (stack[top] != rparen)
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

void main()
{
    printf("Input infix : ");
    scanf_s("%s", infix, MAX_STACK);
    prefix();
    reverse();  // 한번더 reverse
    printf("%s\n", infix);  
}