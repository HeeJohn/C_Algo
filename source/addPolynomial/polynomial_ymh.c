/*
    program : polynomial_ymh
    name : minhyuck yun
    last_edit : 23.07.09
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MALLOC(p, s)\
   if (!((p) = (polyPointer)malloc(s))) {\
   fprintf(stderr, "Insufficient memory");\
   exit(EXIT_FAILURE);\
   }\
   memset(p, 0, s);
#define COMPARE(a,b) ((a) > (b) ? 1 : (a) == (b) ? 0 : -1)

typedef struct polyNode* polyPointer;
typedef struct polyNode {
    int coef; //다항식의 계수
    int expon;//다항식의 지수
    polyPointer link; //리스트의 링크
} polyNode;

polyPointer padd(polyPointer a, polyPointer b);
void attach(int co, int ex, polyPointer* ptr);
void printlist(polyPointer first);
void insert(polyPointer* num);

int main(void)
{
    polyPointer a, b, c;
    MALLOC(a, sizeof(*a));
    MALLOC(b, sizeof(*b));
    MALLOC(c, sizeof(*c));
    printf("다항식을 내림차순으로 정리하여 입력해주세요.\n");
    printf("A 다항식\n");
    insert(&a);
    printf("B 다항식\n");
    insert(&b);

    printlist(a);
    printf(" + ");
    printlist(b);
    printf("\n= ");
    c = padd(a, b);
    printlist(c);
}

void insert(polyPointer* num) //입력 받는 함수
{
    polyPointer rear, temp;
    int coef;
    int expon = 1;

    MALLOC(rear, sizeof(*rear));
    *num = rear;

    while (expon != 0)
    {
        printf("다항식의 계수를 입력해주세요(정수)-> ");
        scanf_s("%d", &coef);
        printf("다항식의 지수를 입력해주세요(정수/0입력시 상수로 판단하여 종료-> ");
        scanf_s("%d", &expon);
        attach(coef, expon, &rear);
    }

    rear->link = NULL;
    temp = *num;
    *num = (*num)->link; //num의 값에는 NULL이 있으므로 한 칸 뒤로 물림
    free(temp);
}

polyPointer padd(polyPointer a, polyPointer b)
{
    polyPointer c, rear, temp;
    int sum;
    MALLOC(rear, sizeof(*rear));
    c = rear;
    while (a && b)
    {
        switch (COMPARE(a->expon, b->expon))
        {
        case -1: // a < b
            attach(b->coef, b->expon, &rear);
            b = b->link;
            break;
        case 0: //a = b
            sum = a->coef + b->coef;
            if (sum)
                attach(sum, a->expon, &rear);
            a = a->link;
            b = b->link;
            break;
        case 1: //a > b
            attach(a->coef, a->expon, &rear);
            a = a->link;
            break;
        }
    }

    while (a) //남아있는 식을 전부 털어줌
    {
        attach(a->coef, a->expon, &rear);
        a = a->link;
    }

    while (b) //남아있는 식을 전부 털어줌
    {
        attach(b->coef, b->expon, &rear);
        b = b->link;
    }

    rear->link = NULL;
    temp = c;
    c = c->link; //c에 있는 NULL값 때문에 한 칸 뒤로 물림
    free(temp);
    return c;
}

void attach(int co, int ex, polyPointer* ptr)
{
    polyPointer temp;
    MALLOC(temp, sizeof(*temp));
    temp->coef = co;
    temp->expon = ex;
    (*ptr)->link = temp;
    *ptr = temp;
}

void printlist(polyPointer first)
{
    printf("(");
    while (first)
    {
        if (first->coef != 0 && first->expon == 0)
            printf("%d", first->coef);
        else if (first->coef && first->expon)
            printf("%dX^%d", first->coef, first->expon);
        first = first->link;

        if (first != NULL && first->coef != 0)
            printf(" + "); //마지막이 아니거나 계수가 0이 아니라면 +가 추가로 출력
    }
    printf(")");
}