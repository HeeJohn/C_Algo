/*
    program : addpoly
    name : 이창범
    last_edit : 23.07.14
*/
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
    if (!((p) = (polyPointer)malloc(s))) {\
        fprintf(stderr, "Insufficient memory");\
        exit(EXIT_FAILURE);\
}
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
typedef struct polyNode* polyPointer;
typedef struct polyNode {
    int coef;
    int expon;
    polyPointer link;
} polyNode;
polyPointer create();
void attach(polyPointer plist, int coefficient, int exponent);
void input(polyPointer inform);
void padd(polyPointer plist1, polyPointer plist2, polyPointer plist3);
void print_poly(polyPointer plist);
void main() {
    int count = 1;
    polyPointer list1 = create();
    polyPointer list2 = create();
    polyPointer addlist = create();

    input(list1);
    input(list2);

    padd(list1, list2, addlist);

    printf("덧셈 결과: ");
    print_poly(addlist);
    printf("\n");

}
polyPointer create() {
    polyPointer plist;
    MALLOC(plist, sizeof(*plist));
    plist->link = NULL;
    return plist;
}
void input(polyPointer inform) {
    int n;
    printf("다항식의 항의 개수를 입력하세요 ");
    scanf_s("%d", &n);
    printf("다항식의 항을 계수-차수의 순서로 입력하세요.\n");
    for (int i = 0; i < n; i++)
    {
        scanf_s("%d %d", &inform->coef, &inform->expon);
        attach(inform, inform->coef, inform->expon);
    }
}
void attach(polyPointer plist, int coefficient, int exponent) {
    polyPointer temp;
    MALLOC(temp, sizeof(*temp));
    temp->coef = coefficient;
    temp->expon = exponent;
    temp->link = NULL;
    if (plist->link)
        while (plist->link != NULL) {
            plist = plist->link;
        }
    plist->link = temp;
}
void padd(polyPointer plist1, polyPointer plist2, polyPointer plist3) {
    polyPointer a = plist1->link;
    polyPointer b = plist2->link;
    int sum;

    while (a && b) {
        switch (COMPARE(a->expon, b->expon))
        {
        case -1:
            attach(plist3, b->coef, b->expon);
            b = b->link;
            break;
        case 0:
            sum = a->coef + b->coef;
            if (sum)
                attach(plist3, sum, a->expon);
            a = a->link;
            b = b->link;
            break;
        case 1:
            attach(plist3, a->coef, a->expon);
            a = a->link;
            break;
        }
    }
    while (a) {
        attach(plist3, a->coef, a->expon);
        a = a->link;
    }
    while (b) {
        attach(plist3, b->coef, b->expon);
        b = b->link;
    }
}
void print_poly(polyPointer plist) {
    polyPointer p = plist->link;
    for (; p; p = p->link) {
        printf("%dX^%d ", p->coef, p->expon);
        if (p->link) {
            printf("+ ");
        }
    }
    printf("\n");
}
