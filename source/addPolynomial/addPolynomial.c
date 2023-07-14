/*
    program :addpolynomial
    name: minwookim
    last_edit: 23.07.14
*/
#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x,y) (((x)<(y)) ? -1 : (((x)==(y))? 0: 1))//padd �Լ����� �������� COMPARE ��ũ�� �Լ� ����
#define MALLOC(p,s)\
    if (!((p) = (polypointer)malloc(s))) {\
         fprintf(stderr, "Insufficient memory.");\
        exit(1);\
    }//�����Ҵ��� ���� MALLOC ��ũ�� �Լ� ����


typedef struct polyNode* polypointer;//polypointer ���Ḯ��Ʈ ���� 
typedef struct polyNode {
    float coef;
    int expon;
    polypointer link;
}polyNode;

polypointer a, b, c;//A(x) B(x)�� ���� ���� ����� C(x)

polypointer create();
void attach(float coefficient, int exponent, polypointer* ptr);
polypointer padd(polypointer a, polypointer b);

void main() {
    polypointer x,z;//a���� �ٷ� temp���� ������ ��� 2�� �̻��� ��� ������ ���� �ʱ⶧���� x��� ������ ��带 �����Ͽ� ��������ش�.
    MALLOC(z, sizeof(*z));//C(x)�� ���� ��� z����
    
    printf("A(x) ���׽��� �Է��Ͻÿ�\n");
    a = create();
    printf("B(x) ���׽��� �Է��Ͻÿ�.\n");
    b = create();
    z = padd(a, b);
    for (; z; z = z->link)
    {
        printf("%.fx^%d", z->coef, z->expon);
        if (z->link != 0)
            printf("+");
    }
}

polypointer create() {
    polypointer x,temp;
    MALLOC(x, sizeof(*x));
    MALLOC(temp, sizeof(*temp));
    temp = x;
    int i = 1;
    while (1)
    {
        printf("%d��° ����� ������ �Է��ϼ���.\n",i);
        scanf_s("%f %d", &x->coef,&x->expon);
        if (x->expon == 0)
        {
            x->link = NULL;
            break;
        }
        else
            attach(x->coef, x->expon, &x);
        i++;
    }
    return temp;
}
void attach(float coefficient, int exponent, polypointer* ptr)
{
    polypointer temp;
    MALLOC(temp, sizeof(*temp));//temp ��� ��带 �����ϰ� A(x)+B(x)���� ������ ���ο� ���� �߰����� �ش�.
    temp->coef = coefficient;
    temp->expon = exponent;
    (*ptr)->link = temp;//rear�� ��ũ �ʵ�� temp����Ų��.
    *ptr = temp;//rear�� temp�� ���� ������ ������ �����ߵ��� queue ������ ������ ������ rear�� ��ġ�� ��������ش�.
}
polypointer padd(polypointer a, polypointer b)
{
    polypointer c, rear, temp;
    int sum;
    MALLOC(rear, sizeof(*rear));
    c = rear;//c�� rear�� �����Ҵ�� ����.
    while (a && b)//a�� b ��ü�� ���Ѵ�.
        switch (COMPARE(a->expon, b->expon))//a�� b�� ������ ���Ѵ�.
        {
        case -1:attach(b->coef, b->expon, &rear);//a�� ������ b�� �������� �۴�.
            b = b->link;//b�� ���� �̵������ش� .
            break;
        case 0: sum = a->coef + b->coef;//a�� ������ b�� ������ ����.(a�� ����� b�� ����� �����ش�)
            if (sum)
                attach(sum, a->expon, &rear);
            a = a->link; //a�� ���� �̵������ش�.
            b = b->link;//b�� ���� �̵������ش�.
            break;
        case 1:attach(a->coef, a->expon, &rear);//a�� ������ b�� �������� ũ��.
            a = a->link;//a�� ���� �̵������ش�.
        }

    for (; a; a = a->link)//������ �׵��� �߰������ش�
        attach(a->coef, a->expon, &rear);
    for (; b; b = b->link)//������ �׵��� �߰������ش�.
        attach(b->coef, b->expon, &rear);
    rear->link = NULL;//������ ����� link �ʵ带 NULL������ ��������ش�.
    temp = c;
    c = c->link;
    free(temp);//temp��� ������ ��带 ��ȯ�Ѵ�.
    return c;//���� C(x)�� ��ȯ�Ѵ�.

}


