#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_SIZE 100

char expr[MAX_SIZE]; // Infix expression input
char another_expr[MAX_SIZE]; // Converted prefix expression

typedef enum precedence {
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

int stack[MAX_SIZE];
int top = -1;
char operatorstack[MAX_SIZE];
int opertop = -1;
void push(int item) {
    stack[++top] = item;
}
int pop() {
    return stack[top--];
}

precedence gettoken(char* symbol, int* n) {
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

char printToken(int tOken) {
    switch (tOken) {
    case lparen: return '(';
    case rparen: return ')';
    case plus: return '+';
    case minus: return '-';
    case times: return '*';
    case divide: return '/';
    case mod: return '%';
    case eos: return '\0';
    }
}

void postfix() {//������
    char symbol;
    precedence token;
    int n = 0;
    top = 0;
    stack[0] = eos;
    int i = 0;
    for (token = gettoken(&symbol, &n); token != eos; token = gettoken(&symbol, &n)) {// ���� �� ���� ���� ���⸦ �־��ش�.
        if (token == rparen) {//��ū�� ������ �Ұ�ȣ���
            while (stack[top] != lparen) {//���ÿ��� ���� �Ұ�ȣ�� ���ö� ���� ���ÿ� �ִ� �͵��� ������
                another_expr[i++] = printToken(pop());
                another_expr[i++] = ' ';
            }
            pop();
        }
        else if (token != operand) {
            while (isp[stack[top]] >= icp[token]) {//���� ���� ����� ���� ž���ִ� �����ں���
                another_expr[i++] = printToken(pop());
                another_expr[i++] = ' ';
            }
            push(token);
        }
        else {//�ǿ����� ��, �����϶� �����Ŀ��� �����ڰ� �ǿ����ڸ� �������ش�. �׷��� �������̵� ���������� �ٲ� ������ �ȵɼ� �����Ƿ� ���⸦ �־��ش�
            another_expr[i++] = symbol;
            if (expr[n] == '+' || expr[n] == '-' || expr[n] == '*' || expr[n] == '/' ||
                expr[n] == ')' || expr[n] == '\0')//���ڰ� ������ ���⸦ �־������ν� �������ش�.
            {
                another_expr[i++] = ' ';
            }
        }
    }

    while ((token = (precedence)pop()) != eos) {
        another_expr[i++] = printToken(token);
        another_expr[i++] = ' ';
    }
    another_expr[i] = '\0';
}

int eval() {
    precedence token;
    char symbol;
    int op1, op2;
    int value;
    int count = 0;
    top = -1;
    int length = strlen(another_expr);

    for (int i = length - 1; i > -1; i--) {//�ݴ�� �����Ѵ�.
        symbol = another_expr[i];

        if (symbol >= '0' && symbol <= '9') {
            while (another_expr[i - count] != ' ') {
                count++;
            }
            value = atoi(&another_expr[i - count + 1]);//�ݴ�� ���鼭 ���� �ٷ� �����ʿ��ִ� ���ڸ� ���������� �ٲ۵ڿ� ���ÿ� �ִ´�.
            i -= count;
            count = 0;
            push(value);
        }

        else {
            if (symbol != ' ') {//symbol�� �������� ��
                op1 = pop();
                op2 = pop();

                switch (symbol) {
                case '+': push(op1 + op2); break;
                case '-': push(op1 - op2); break;
                case '*': push(op1 * op2); break;
                case '/': push(op1 / op2); break;
                }
            }


        }
    }return pop();
}
void reverseString(char* str) {//���ڿ� ������ �Լ�
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void reverseExpr(char* str) {
    reverseString(str);

    int len = strlen(str);// �����Ŀ� ��ȣ�� �ִ� ���·� �������� ��ȣ�� ������ �ٲ�Ƿ� ��ȣ�� �ٲ��ش�
    for (int i = 0; i < len; i++) {
        if (str[i] == '(')
            str[i] = ')';
        else if (str[i] == ')')
            str[i] = '(';
    }
}

int main() {
    printf("Enter the infix expression: ");
    scanf_s("%s", expr, 100);
    reverseExpr(expr);// �������� �����´�
    postfix();//������ �������� ���������� �ٲپ� �ش�
    reverseString(another_expr);//�ٽ� �������� �������� �ȴ�

    printf("prefix = %s\n", another_expr);
    printf("Result = %d\n", eval());

    return 0;
}