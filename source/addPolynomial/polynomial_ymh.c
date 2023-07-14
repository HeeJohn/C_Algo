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
    int coef; //���׽��� ���
    int expon;//���׽��� ����
    polyPointer link; //����Ʈ�� ��ũ
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
    printf("���׽��� ������������ �����Ͽ� �Է����ּ���.\n");
    printf("A ���׽�\n");
    insert(&a);
    printf("B ���׽�\n");
    insert(&b);

    printlist(a);
    printf(" + ");
    printlist(b);
    printf("\n= ");
    c = padd(a, b);
    printlist(c);
}

void insert(polyPointer* num) //�Է� �޴� �Լ�
{
    polyPointer rear, temp;
    int coef;
    int expon = 1;

    MALLOC(rear, sizeof(*rear));
    *num = rear;

    while (expon != 0)
    {
        printf("���׽��� ����� �Է����ּ���(����)-> ");
        scanf_s("%d", &coef);
        printf("���׽��� ������ �Է����ּ���(����/0�Է½� ����� �Ǵ��Ͽ� ����-> ");
        scanf_s("%d", &expon);
        attach(coef, expon, &rear);
    }

    rear->link = NULL;
    temp = *num;
    *num = (*num)->link; //num�� ������ NULL�� �����Ƿ� �� ĭ �ڷ� ����
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

    while (a) //�����ִ� ���� ���� �о���
    {
        attach(a->coef, a->expon, &rear);
        a = a->link;
    }

    while (b) //�����ִ� ���� ���� �о���
    {
        attach(b->coef, b->expon, &rear);
        b = b->link;
    }

    rear->link = NULL;
    temp = c;
    c = c->link; //c�� �ִ� NULL�� ������ �� ĭ �ڷ� ����
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
            printf(" + "); //�������� �ƴϰų� ����� 0�� �ƴ϶�� +�� �߰��� ���
    }
    printf(")");
}