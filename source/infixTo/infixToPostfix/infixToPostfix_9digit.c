/*
    program: 9digit infix
    name: minwookim
    last_edit: 23.07.14
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand }precedence;//연산자들을 열거한 열거타입 구조체 precedence
int isp[] = { 0,19,12,12,13,13,13,0 };
int icp[] = { 20,19,12,12,13,13,13,0 };
typedef struct {
    char key;
}element;
char stack[MAX_STACK_SIZE];//stack 배열이다.
char expr[MAX_STACK_SIZE];//중위식을 받을 배열이다.
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

    printf("중위표기식을 입력하시오.");
    scanf_s("%[^\n]s", expr, sizeof(expr));
    printf("중위표기식을 출력하세요\n");
    printf("%s", expr);//중위 식을 입력받기 위해서 중위식을 입력받는 expr 배열에 입력받는다.
    postfix();//후위식으로 변환하는 함수
    printf("후위표기식을 출력하세요\n");
    printf("%s\n", expr);//후위식 출력 
    printf("\n%4d", eval());//계산 결과 출력 eval 함수의 반환형은 int 이므로 %d로 하여 printf해준다.

}
int eval()//후위식을 계산하는 함수 
{
    char temp[MAX_STACK_SIZE];
    precedence token;
    char symbol;
    int op1, op2;
    char value;
    int n = 0;
    int i = 0;
    int front=0, rear = 0;
    token = getToken(&symbol, &n);// token에 temp 배열에 들어있는 각각의 원소를 저장한다. getToken2 에서는 후위식인 temp의 배열 원소들을 하나하나 token에 넣고 while 문에 넣는다.
    while (token != eos)//token이 eos가 아니면 즉 식이 끝나지 않았으면 while문을 실행한다. 
    {
        if (token == operand)//token이 연산자가 아닌 피연산자 일경우 
        {
            if (expr[n-1] != ' ')
                temp[rear++] = expr[n-1];
            else {
                value = atoi(temp+front);
                push(value);
                front = rear;
            }
        }
        else//연산자일 경우 
        {
            op2 = pop();//후위식에서 피연산자를 삭제 후 op1과 op2에 저장 
            op1 = pop();
            switch (token)//getToken에서 반환되는 값에 따라 계산방식이 달라지게 swtich case 문으로 실행 
            {
            case  plus:push(op1 + op2);//반환되는 값이 plus이면 op1과 op2를 더한 값을 스택에 push
                break;
            case minus:push(op1 - op2);//반환되는 값이 minus이면 op1과 op2를 뺀 값을 스택에 push
                break;
            case times:push(op1 * op2);//반환되는 값이 times이면 op1과 op2를 곱한 값을 스택에 push
                break;
            case divide:push(op1 / op2);//반환되는 값이 divide이면 op1과 op2를 나눈 값을 스택에 push
                break;
            case mod: push(op1 % op2);//반환되는 값이 mod이면 op1과 op2를 나눴을때 나온 나머지 값을 스택에 push
            }
        }
        token = getToken(&symbol, &n);//이후 token이 eos에 다 도착했을경우 getToken 함수에서 eos를 반환 
    }
    return pop();//결과 값을 반환 
}

precedence getToken(char* symbol, int* n)//expr 즉 중위식에서의 연산자 피연산자를 구분하기 위한 함수 
{
    *symbol = expr[(*n)++];//expr 배열의 n번째 방 즉  0번째 방부터 n을 증가시키며 epxr배열에 있는 원소들을 구분하기 위한 선언 
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
void postfix()//후위식으로 변환하기 위한 함수  
{
    char symbol;
    precedence token;
    int n = 0;
    int i = 0;
    stack[0] = eos;
    for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))//expr 배열에 있는 원소들을 getToken을 이용해 eos가 나오기 전까지 반복해서 실행한다.
    {
        if (token == operand)//피연산자이면 
        {
            expr[i++] = symbol;//후위식 배열인 temp 배열에 원소를 저장하고 i++를 해주어 다음 번 원소가 들어갈 위치를 지정해준다.
        }
        else if (token == ' ')
            i++;
        else if (token == rparen)//오른쪽 괄호 일경우  
        {
            while (stack[top] != lparen) //왼쪽 괄호가 나올때 까지 토큰들을 제거해서 출력시킨다.
            {
                expr[i++] = printToken(pop());

            }
            expr[i++] = pop();//왼쪽 괄호를 제거한다.
        }
        else {
            while (isp[stack[top]] >= icp[token])//symbol의 isp(스택 내부에서의 우선순위)가 token의 icp(수식에서의 우선순위)보다 크거나 같으면 symbol을 제거하고 출력시킨다.
            {
                expr[i++] = printToken(pop());//top에 있는 연산자가 incoming 연산자보다 우선순위가 낮아질 때까지 출력
            }
            push(token);
        }
    }
    while ((token = pop()) != eos)
    {
        expr[i++] = printToken(token);//후위식의 token들을 temp 배열에 저장시킴 
    }
    printf("\n");
}

void push(char item)//stack 삽입함수
{
    if (top >= MAX_STACK_SIZE)
        stackFull();
    stack[++top] = item;
}

char pop()//stack 삭제 함수 
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
char printToken(precedence item)//token을 출력하는 함수
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