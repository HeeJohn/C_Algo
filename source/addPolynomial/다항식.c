#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) if(!((p)=(polyPointer)malloc(s))){fprintf(stderr,"Insufficient memory");exit(EXIT_FAILURE);}//p에 메모리 할당을 해주는 매크로함수
#define COMPARE(x,y) (((x) < (y)) ? -1: ((x) == (y)) ? 0 : 1)//x<y면 -1,x=y면 0, 그렇지않으면 1을 반환하는 매크로 함수
typedef struct polyNode* polyPointer;//polyNode형의 포인터 자료형 polyPointer
typedef struct polyNode{
    float coef;
    int expon;
    polyPointer link;
};//계수, 지수, 링크필드 포함된 노드

void attach(float coefficient, int exponent, polyPointer* ptr) {//ptr노드에 계수와 지수를 넣는 함수
    polyPointer temp;
    MALLOC(temp, sizeof(*temp));//temp를 메모리할당해준다
    temp->coef = coefficient;//temp 노드의 계수를 초기화
    temp->expon = exponent;//temp 노드의 지수를 초기화
    (*ptr)->link = temp;//ptr노드의 링크를 temp로 연결
    *ptr = temp;//그 temp가 ptr이 된다 한마디로 다음 노드로 넘어간다
}
polyPointer padd(polyPointer a, polyPointer b) {
    polyPointer c, rear, temp;
    float sum;
    MALLOC(rear, sizeof(*rear));//rear를 메모리 할당해준다
    c = rear;//c를 rear로 초기화
    while (a && b)
        switch (COMPARE(a->expon,b->expon))
        {
        case -1://a의 지수보다 b의 지수가 더 클 때
            attach(b->coef, b->expon, &rear); //rear에 b의 계수와 지수를 넣는다
            b = b->link;     break;//b의 다음 노드로 넘어간다.
        case 0://a의 지수와 b의 지수가 같을 때
            sum = a->coef + b->coef;//지수가 같으므로 a와b의 계수를 더한다
            if (sum) attach(sum, a->expon, &rear);//더한 계수와 a의 지수를 rear에 넣는다
            a = a->link;b = b->link;    break;//a와b의 다음 노드로 넘어간다.
        case 1://a의 지수가 b의 지수보다 클 때
            attach(a->coef, a->expon, &rear);//rear에 a의 계수와 지수를 넣는다
            a = a->link;    break;//a의 다음노드로 넘어간다.
        }
        for (;a;a = a->link)attach(a->coef, a->expon, &rear);
        for (;b;b = b->link)attach(b->coef, b->expon, &rear);//a나 b의 항만 남았을때 반본문을 이용해 남은 항을 rear에 넣는다
        rear->link = NULL; //마지막항 즉 마지막 노드의 링크를 NULL로 정의해 마지막 항임을 알린다.
        temp = c;
        c = c->link;
        free(temp);//temp를 c로 초기화 한뒤에 메모리 할당을 해제한다

        return c;//다항식 계산을 마친 c를 반환한다

}

polyPointer create_poly() {
    float coeff;//계수
    int expone;//지수
    polyPointer poly,rear,temp;
    MALLOC(rear, sizeof(*rear));//rear를 메모리 할당해준다
    poly = rear;//poly를 rear로 초기화
    rear->expon = 10000;//첫다힝식의 지수는 큰수로 초기화한다.
    printf("지수를 음수로 입력할 경우 종료됩니다.\n");
    while (true) {
        printf("다항식에 들어갈 항을 지수 순서대로 적어주세요 --계수 : 지수-- -> ");
        scanf_s("%f %d", &coeff, &expone);
        if (expone>= rear->expon) {
            //이전항의 지수보다 입력한 지수가 클 때 다시 입력받도록 한다.
            printf("입력하신 지수는 다항식에 존재하는 지수보다 같거나 큽니다. 다시 입력해주세요\n");
            continue;
        }
        else if (expone < 0)  //입력한 지수가 음수라면
            break; //  반복문을 탈출해 입력을 종료한다.
        attach(coeff, expone, &rear);//입력받은 계수와 지수를 rear에 넣는다
    }
    rear->link = NULL;//마지막항 즉 마지막 노드의 링크를 NULL로 정의해 마지막 항임을 알린다.
    temp = poly;
    poly = poly->link;
    free(temp);//temp를 poly로 초기화 한뒤에 메모리 할당을 해제한다
    return poly;//입력을 마친 poly를 반환한다.
}
void print_poly(polyPointer poly) {
    while (poly != NULL) {//항이 끝날때까지 반복
        printf("%.2f x^%d", poly->coef, poly->expon);//계수와 지수 출력
        if (poly->link != NULL)//마지막항에는 '+'연산자를 출력하지 않는다
            printf(" + ");
        poly = poly->link;//다음 항으로 넘어간다.
    }
}


int main() {
    printf("첫번째 다항식 A(x)에 들어갈 항들을 입력해주세요\n");
    polyPointer a = create_poly();//A(x) 다항식을 만든다;
    printf("A(x) =  ");
    print_poly(a);//A(x) 다항식을 출력한다
    printf("\n");

    printf("두번째 다항식 B(x)에 들어갈 항들을 입력해주세요\n");
    polyPointer b = create_poly();//B(x) 다항식을 만든다;
    printf("B(x) =  ");
    print_poly(b);//B(x) 다항식을 출력한다
    printf("\n");

    polyPointer c = padd(a, b);//A(x) + B(x)를 C(x)로 한다.
    printf("C(x) =  ");
    print_poly(c);//C(x) 다항식을 출력한다.

}