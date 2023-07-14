/*
    name : ������->������
    last_edit : 23.07.11
*/
#include <stdio.h>
#include <stdlib.h>

#define CRT_SECURE_NO_WARNINGS
#define MAX_STACK 100

//���� ǥ���, ���� �迭 �� �ε��� �������� 
typedef char element;
element infix[MAX_STACK];
element stack[MAX_STACK];
int top;

// ���� �Լ�
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

int isp[] = { 19,0,12,12,13,13,13,0 };  // ������ ���ʰ�ȣ�� ������ ��ȣ�� ������ �켱������ ����
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

void reverse()  // infix �������� �����ϴ� �Լ�
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
        else if (token == lparen)   // ���� ��ȣ�� ������ ��ȣ�� ���ö����� ���þ��� �����ڸ� pop
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
    for (p; p < MAX_STACK; p++)     // ��ȣ�� �����Ͽ��� �� �����ִ� ������ ����� ���� �ݺ���
        infix[p] = '\0';
    printf("\n");
}

void main()
{
    printf("Input infix : ");
    scanf_s("%s", infix, MAX_STACK);
    prefix();
    reverse();  // �ѹ��� reverse
    printf("%s\n", infix);  
}