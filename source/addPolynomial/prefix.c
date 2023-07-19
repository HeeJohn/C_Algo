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

void postfix() {//후위식
    char symbol;
    precedence token;
    int n = 0;
    top = 0;
    stack[0] = eos;
    int i = 0;
    for (token = gettoken(&symbol, &n); token != eos; token = gettoken(&symbol, &n)) {// 식을 더 보기 좋게 띄어쓰기를 넣어준다.
        if (token == rparen) {//토큰이 오른쪽 소괄호라면
            while (stack[top] != lparen) {//스택에서 왼쪽 소괄호가 나올때 까지 스택에 있는 것들을 빼낸다
                another_expr[i++] = printToken(pop());
                another_expr[i++] = ' ';
            }
            pop();
        }
        else if (token != operand) {
            while (isp[stack[top]] >= icp[token]) {//현재 읽은 토근이 스택 탑에있는 연산자보다
                another_expr[i++] = printToken(pop());
                another_expr[i++] = ' ';
            }
            push(token);
        }
        else {//피연산자 즉, 숫자일때 중위식에서 연산자가 피연산자를 구분해준다. 그러나 후위식이든 전위식으로 바뀔때 구분이 안될수 있으므로 띄어쓰기를 넣어준다
            another_expr[i++] = symbol;
            if (expr[n] == '+' || expr[n] == '-' || expr[n] == '*' || expr[n] == '/' ||
                expr[n] == ')' || expr[n] == '\0')//숫자가 끝나면 띄어쓰기를 넣어줌으로써 구분해준다.
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

    for (int i = length - 1; i > -1; i--) {//반대로 시작한다.
        symbol = another_expr[i];

        if (symbol >= '0' && symbol <= '9') {
            while (another_expr[i - count] != ' ') {
                count++;
            }
            value = atoi(&another_expr[i - count + 1]);//반대로 가면서 띄어쓰기 바로 오른쪽에있는 숫자를 정수형으로 바꾼뒤에 스택에 넣는다.
            i -= count;
            count = 0;
            push(value);
        }

        else {
            if (symbol != ' ') {//symbol이 연산자일 때
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
void reverseString(char* str) {//문자열 뒤집는 함수
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void reverseExpr(char* str) {
    reverseString(str);

    int len = strlen(str);// 중위식에 괄호가 있는 상태로 뒤집을때 괄호의 방향이 바뀌므로 괄호를 바꿔준다
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
    reverseExpr(expr);// 중위식을 뒤집는다
    postfix();//뒤집은 중위식을 후위식으로 바꾸어 준다
    reverseString(another_expr);//다시 뒤집으면 전위식이 된다

    printf("prefix = %s\n", another_expr);
    printf("Result = %d\n", eval());

    return 0;
}