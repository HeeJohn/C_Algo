#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 100

char expr[MAX_SIZE];//�������� �Է¹��� ����
char another_expr[MAX_SIZE];//���������� �Է¹��� �Լ��� ���������� ������ ����

typedef enum precedence {
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;//enum ����ü�� �����ڵ� ,�ǿ����� �ʱ�ȭ

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };//���ÿ� ���϶� �����ڵ��� �켱����
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };//���ÿ��� ���ö� �����ڵ��� �켱����

int stack[MAX_SIZE];//������->�����ĺ�ȯ �� �� �����ڵ��� ����, �����Ŀ��� ����Ҷ� �ǿ����ڰ� ���� ����
int top = -1;//������ ������ -1�� �ʱ�ȭ

void push(int item) {
    stack[++top] = item;
}//���ÿ� item�� �״� �Լ�

int pop() {
    return stack[top--];
}//���ÿ��� ���� ������ �� ���� ��ȯ�ϴ� �Լ�

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
    }//�������� ������(symbol)�� ��ġȭ�ؼ� ��ȯ�ϴ� �Լ�, �� �ǿ������ϰ�� �״�� ��ȯ
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
    }//precedence������ ���� �Ķ���͸� ���������� ������ִ� �Լ�
}

void postfix() {//������->���������� �ٲٴ� �Լ�
    char symbol;
    precedence token;
    int n = 0;
    top = 0;
    stack[0] = eos;//��ó�� ������ ��ĭ���� �״´�
    int i = 0;
    for (token = gettoken(&symbol, &n, expr); token != eos; token = gettoken(&symbol, &n, expr)) {
        if (token == operand) {//�ǿ������϶�

            expr[i++] = symbol;
        }//�ǿ����ڵ��� ���ڿ� ������ �����Ѵ�
        else if (token == rparen) {//  ")"�� �� 
            while (stack[top] != lparen) {
                expr[i++] = printToken(pop());
            }// ���ÿ� ������ �����ڰ� "(" �϶� ���� ������ �����ڵ��� ��� ���鼭 ���ڿ� ������ �����Ѵ�
            pop();
        }
        else {
            while (isp[stack[top]] >= icp[token]) {
                expr[i++] = printToken(pop());
            }//������ �����ڵ� �߿��� �켱���� ���� �����ڵ��� ���ÿ��� ���鼭 ���ڿ� ������ �����Ѵ�
            push(token);
        }
    }

    while ((token = (precedence)pop()) != eos) {//���ÿ� �ִ� ������ �����ڵ��� ���ÿ��� ���鼭 ���ڿ� ������ �����Ѵ�
        expr[i++] = printToken(token);
    }

    printf("\n");
}

int eval() {//�������� ����ϴ� �Լ�
    precedence token;
    char symbol;
    int op1, op2;
    int n = 0;

    token = gettoken(&symbol, &n, expr);//�������� ������(symbol)�� ��ġȭ�ϴ� �Լ��� �̿��ؼ� ��ū ���� �ʱ�ȭ
    while (token != eos) {
        if (token == operand) {//�ǿ������ϰ�� ���������� ���ִ� ���ڸ� ������ ���ڷ� ����� ���ÿ� �ִ´�
            push(symbol - '0');
        }
        else {
            op2 = pop();//���ÿ��� ���� �ǿ�����
            op1 = pop();//���ÿ��� ���� �ǿ�����
            switch (token) {//��ū�� � ������������ ���� op1��op2�� ����ؼ� ���ÿ� �ִ´� 
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
        token = gettoken(&symbol, &n, expr);//�������� ������(symbol)�� ��ġȭ�ϴ� �Լ��� �̿��ؼ� ��ū ���� �ʱ�ȭ
    }
    return pop();//��� ����� ��ȯ�Ѵ�.
}

int main() {
    printf("Enter the infix expression: ");
    scanf_s("%s", expr, 100);//�������� �Է¹޴´�

    postfix();//������->������ ��ȯ �Լ�
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