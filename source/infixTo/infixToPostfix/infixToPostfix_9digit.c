/*
    program: 9digit infix
    name: minwookim
    last_edit: 23.07.14
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand }precedence;//�����ڵ��� ������ ����Ÿ�� ����ü precedence
int isp[] = { 0,19,12,12,13,13,13,0 };
int icp[] = { 20,19,12,12,13,13,13,0 };
typedef struct {
    char key;
}element;
char stack[MAX_STACK_SIZE];//stack �迭�̴�.
char expr[MAX_STACK_SIZE];//�������� ���� �迭�̴�.
int top = 0;

int eval();
precedence getToken(char* symbol, int* n);
void push(unsigned char item);
char pop();
void stackFull();
void stackEmpty();
void postfix();
char printToken(precedence item);

int main() {

    printf("����ǥ����� �Է��Ͻÿ�.");
    scanf_s("%[^\n]s", expr, sizeof(expr));
    printf("����ǥ����� ����ϼ���\n");
    printf("%s", expr);//���� ���� �Է¹ޱ� ���ؼ� �������� �Է¹޴� expr �迭�� �Է¹޴´�.
    postfix();//���������� ��ȯ�ϴ� �Լ�
    printf("����ǥ����� ����ϼ���\n");
    printf("%s\n", expr);//������ ��� 
    printf("\n%4d", eval());//��� ��� ��� eval �Լ��� ��ȯ���� int �̹Ƿ� %d�� �Ͽ� printf���ش�.

}
int eval()//�������� ����ϴ� �Լ� 
{
    char temp[MAX_STACK_SIZE];
    precedence token;
    char symbol;
    int op1, op2;
    char value;
    int n = 0;
    int i = 0;
    int front=0, rear = 0;
    token = getToken(&symbol, &n);// token�� temp �迭�� ����ִ� ������ ���Ҹ� �����Ѵ�. getToken2 ������ �������� temp�� �迭 ���ҵ��� �ϳ��ϳ� token�� �ְ� while ���� �ִ´�.
    while (token != eos)//token�� eos�� �ƴϸ� �� ���� ������ �ʾ����� while���� �����Ѵ�. 
    {
        if (token == operand)//token�� �����ڰ� �ƴ� �ǿ����� �ϰ�� 
        {
            if (expr[n-1] != ' ')
                temp[rear++] = expr[n-1];
            else {
                value = atoi(temp+front);
                push(value);
                front = rear;
            }
        }
        else//�������� ��� 
        {
            op2 = pop();//�����Ŀ��� �ǿ����ڸ� ���� �� op1�� op2�� ���� 
            op1 = pop();
            switch (token)//getToken���� ��ȯ�Ǵ� ���� ���� ������� �޶����� swtich case ������ ���� 
            {
            case  plus:push(op1 + op2);//��ȯ�Ǵ� ���� plus�̸� op1�� op2�� ���� ���� ���ÿ� push
                break;
            case minus:push(op1 - op2);//��ȯ�Ǵ� ���� minus�̸� op1�� op2�� �� ���� ���ÿ� push
                break;
            case times:push(op1 * op2);//��ȯ�Ǵ� ���� times�̸� op1�� op2�� ���� ���� ���ÿ� push
                break;
            case divide:push(op1 / op2);//��ȯ�Ǵ� ���� divide�̸� op1�� op2�� ���� ���� ���ÿ� push
                break;
            case mod: push(op1 % op2);//��ȯ�Ǵ� ���� mod�̸� op1�� op2�� �������� ���� ������ ���� ���ÿ� push
            }
        }
        token = getToken(&symbol, &n);//���� token�� eos�� �� ����������� getToken �Լ����� eos�� ��ȯ 
    }
    return pop();//��� ���� ��ȯ 
}

precedence getToken(char* symbol, int* n)//expr �� �����Ŀ����� ������ �ǿ����ڸ� �����ϱ� ���� �Լ� 
{
    *symbol = expr[(*n)++];//expr �迭�� n��° �� ��  0��° ����� n�� ������Ű�� epxr�迭�� �ִ� ���ҵ��� �����ϱ� ���� ���� 
    switch (*symbol)
    {
    case'(':return lparen;
    case ')':return rparen;
    case '+': return plus;
    case '-':return minus;
    case'/':return divide;
    case '*':return times;
    case '%': return mod;
    case '.':return eos;
    default:return operand;
    }
}
void postfix()//���������� ��ȯ�ϱ� ���� �Լ�  
{
    char symbol;
    precedence token;
    int n = 0;
    int i = 0;
    stack[0] = eos;
    for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))//expr �迭�� �ִ� ���ҵ��� getToken�� �̿��� eos�� ������ ������ �ݺ��ؼ� �����Ѵ�.
    {
        if (token == operand)//�ǿ������̸� 
        {
            expr[i++] = symbol;//������ �迭�� temp �迭�� ���Ҹ� �����ϰ� i++�� ���־� ���� �� ���Ұ� �� ��ġ�� �������ش�.
        }
        else if (token == ' ')
            i++;
        else if (token == rparen)//������ ��ȣ �ϰ��  
        {
            while (stack[top] != lparen) //���� ��ȣ�� ���ö� ���� ��ū���� �����ؼ� ��½�Ų��.
            {
                expr[i++] = printToken(pop());

            }
            expr[i++] = pop();//���� ��ȣ�� �����Ѵ�.
        }
        else {
            while (isp[stack[top]] >= icp[token])//symbol�� isp(���� ���ο����� �켱����)�� token�� icp(���Ŀ����� �켱����)���� ũ�ų� ������ symbol�� �����ϰ� ��½�Ų��.
            {
                expr[i++] = printToken(pop());//top�� �ִ� �����ڰ� incoming �����ں��� �켱������ ������ ������ ���
            }
            push(token);
        }
    }
    while ((token = pop()) != eos)
    {
        expr[i++] = printToken(token);//�������� token���� temp �迭�� �����Ŵ 
    }
    printf("\n");
}

void push(char item)//stack �����Լ�
{
    if (top >= MAX_STACK_SIZE)
        stackFull();
    stack[++top] = item;
}

char pop()//stack ���� �Լ� 
{
    if (top == -1)
        stackEmpty();
    return stack[top--];
}

void stackFull() {
    fprintf(stderr, "stack is full, cannot add element");
    exit(1);
}
void stackEmpty() {
    fprintf(stderr, "stack is Empty, cannot delete element");
    exit(1);

}
char printToken(precedence item)//token�� ����ϴ� �Լ�
{
    switch (item) {
    case plus: return '+';
    case minus: return '-';
    case times: return '*';
    case divide: return '/';
    case mod: return '%';
    case eos:return ' ';
    }
}