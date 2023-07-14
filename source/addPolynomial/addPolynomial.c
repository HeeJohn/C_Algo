/*
    program :addpolynomial
    name: minwookim
    last_edit: 23.07.14
*/
#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x,y) (((x)<(y)) ? -1 : (((x)==(y))? 0: 1))//padd 함수에서 쓰여지는 COMPARE 매크로 함수 선언
#define MALLOC(p,s)\
    if (!((p) = (polypointer)malloc(s))) {\
         fprintf(stderr, "Insufficient memory.");\
        exit(1);\
    }//동적할당을 위한 MALLOC 매크로 함수 선언


typedef struct polyNode* polypointer;//polypointer 연결리스트 정의 
typedef struct polyNode {
    float coef;
    int expon;
    polypointer link;
}polyNode;

polypointer a, b, c;//A(x) B(x)와 둘의 덧셈 결과인 C(x)

polypointer create();
void attach(float coefficient, int exponent, polypointer* ptr);
polypointer padd(polypointer a, polypointer b);

void main() {
    polypointer x,z;//a에서 바로 temp으로 연결할 경우 2개 이상의 노드 연결이 되지 않기때문에 x라는 임의의 노드를 생성하여 연결시켜준다.
    MALLOC(z, sizeof(*z));//C(x)를 받을 노드 z생성
    
    printf("A(x) 다항식을 입력하시오\n");
    a = create();
    printf("B(x) 다항식을 입력하시오.\n");
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
        printf("%d번째 계수와 지수를 입력하세요.\n",i);
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
    MALLOC(temp, sizeof(*temp));//temp 라는 노드를 생성하고 A(x)+B(x)에서 생성된 새로운 항을 추가시켜 준다.
    temp->coef = coefficient;
    temp->expon = exponent;
    (*ptr)->link = temp;//rear의 링크 필드는 temp가르킨다.
    *ptr = temp;//rear는 temp의 값을 가진다 위에서 설명했듯이 queue 구조를 가지기 때문에 rear의 위치를 변경시켜준다.
}
polypointer padd(polypointer a, polypointer b)
{
    polypointer c, rear, temp;
    int sum;
    MALLOC(rear, sizeof(*rear));
    c = rear;//c는 rear의 동적할당과 같다.
    while (a && b)//a와 b 전체를 비교한다.
        switch (COMPARE(a->expon, b->expon))//a와 b의 지수를 비교한다.
        {
        case -1:attach(b->coef, b->expon, &rear);//a의 지수가 b의 지수보다 작다.
            b = b->link;//b의 항을 이동시켜준다 .
            break;
        case 0: sum = a->coef + b->coef;//a의 지수와 b의 지수가 같다.(a의 계수와 b의 계수를 더해준다)
            if (sum)
                attach(sum, a->expon, &rear);
            a = a->link; //a의 항을 이동시켜준다.
            b = b->link;//b의 항을 이동시켜준다.
            break;
        case 1:attach(a->coef, a->expon, &rear);//a의 지수가 b의 지수보다 크다.
            a = a->link;//a의 항을 이동시켜준다.
        }

    for (; a; a = a->link)//나머지 항들을 추가시켜준다
        attach(a->coef, a->expon, &rear);
    for (; b; b = b->link)//나머지 항들을 추가시켜준다.
        attach(b->coef, b->expon, &rear);
    rear->link = NULL;//마지막 노드의 link 필드를 NULL값으로 저장시켜준다.
    temp = c;
    c = c->link;
    free(temp);//temp라는 임의의 노드를 반환한다.
    return c;//계산된 C(x)를 반환한다.

}


