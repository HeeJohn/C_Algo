#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) if(!((p)=(polyPointer)malloc(s))){fprintf(stderr,"Insufficient memory");exit(EXIT_FAILURE);}//p�� �޸� �Ҵ��� ���ִ� ��ũ���Լ�
#define COMPARE(x,y) (((x) < (y)) ? -1: ((x) == (y)) ? 0 : 1)//x<y�� -1,x=y�� 0, �׷��������� 1�� ��ȯ�ϴ� ��ũ�� �Լ�
typedef struct polyNode* polyPointer;//polyNode���� ������ �ڷ��� polyPointer
typedef struct polyNode{
    float coef;
    int expon;
    polyPointer link;
};//���, ����, ��ũ�ʵ� ���Ե� ���

void attach(float coefficient, int exponent, polyPointer* ptr) {//ptr��忡 ����� ������ �ִ� �Լ�
    polyPointer temp;
    MALLOC(temp, sizeof(*temp));//temp�� �޸��Ҵ����ش�
    temp->coef = coefficient;//temp ����� ����� �ʱ�ȭ
    temp->expon = exponent;//temp ����� ������ �ʱ�ȭ
    (*ptr)->link = temp;//ptr����� ��ũ�� temp�� ����
    *ptr = temp;//�� temp�� ptr�� �ȴ� �Ѹ���� ���� ���� �Ѿ��
}
polyPointer padd(polyPointer a, polyPointer b) {
    polyPointer c, rear, temp;
    float sum;
    MALLOC(rear, sizeof(*rear));//rear�� �޸� �Ҵ����ش�
    c = rear;//c�� rear�� �ʱ�ȭ
    while (a && b)
        switch (COMPARE(a->expon,b->expon))
        {
        case -1://a�� �������� b�� ������ �� Ŭ ��
            attach(b->coef, b->expon, &rear); //rear�� b�� ����� ������ �ִ´�
            b = b->link;     break;//b�� ���� ���� �Ѿ��.
        case 0://a�� ������ b�� ������ ���� ��
            sum = a->coef + b->coef;//������ �����Ƿ� a��b�� ����� ���Ѵ�
            if (sum) attach(sum, a->expon, &rear);//���� ����� a�� ������ rear�� �ִ´�
            a = a->link;b = b->link;    break;//a��b�� ���� ���� �Ѿ��.
        case 1://a�� ������ b�� �������� Ŭ ��
            attach(a->coef, a->expon, &rear);//rear�� a�� ����� ������ �ִ´�
            a = a->link;    break;//a�� �������� �Ѿ��.
        }
        for (;a;a = a->link)attach(a->coef, a->expon, &rear);
        for (;b;b = b->link)attach(b->coef, b->expon, &rear);//a�� b�� �׸� �������� �ݺ����� �̿��� ���� ���� rear�� �ִ´�
        rear->link = NULL; //�������� �� ������ ����� ��ũ�� NULL�� ������ ������ ������ �˸���.
        temp = c;
        c = c->link;
        free(temp);//temp�� c�� �ʱ�ȭ �ѵڿ� �޸� �Ҵ��� �����Ѵ�

        return c;//���׽� ����� ��ģ c�� ��ȯ�Ѵ�

}

polyPointer create_poly() {
    float coeff;//���
    int expone;//����
    polyPointer poly,rear,temp;
    MALLOC(rear, sizeof(*rear));//rear�� �޸� �Ҵ����ش�
    poly = rear;//poly�� rear�� �ʱ�ȭ
    rear->expon = 10000;//ù�������� ������ ū���� �ʱ�ȭ�Ѵ�.
    printf("������ ������ �Է��� ��� ����˴ϴ�.\n");
    while (true) {
        printf("���׽Ŀ� �� ���� ���� ������� �����ּ��� --��� : ����-- -> ");
        scanf_s("%f %d", &coeff, &expone);
        if (expone>= rear->expon) {
            //�������� �������� �Է��� ������ Ŭ �� �ٽ� �Է¹޵��� �Ѵ�.
            printf("�Է��Ͻ� ������ ���׽Ŀ� �����ϴ� �������� ���ų� Ů�ϴ�. �ٽ� �Է����ּ���\n");
            continue;
        }
        else if (expone < 0)  //�Է��� ������ �������
            break; //  �ݺ����� Ż���� �Է��� �����Ѵ�.
        attach(coeff, expone, &rear);//�Է¹��� ����� ������ rear�� �ִ´�
    }
    rear->link = NULL;//�������� �� ������ ����� ��ũ�� NULL�� ������ ������ ������ �˸���.
    temp = poly;
    poly = poly->link;
    free(temp);//temp�� poly�� �ʱ�ȭ �ѵڿ� �޸� �Ҵ��� �����Ѵ�
    return poly;//�Է��� ��ģ poly�� ��ȯ�Ѵ�.
}
void print_poly(polyPointer poly) {
    while (poly != NULL) {//���� ���������� �ݺ�
        printf("%.2f x^%d", poly->coef, poly->expon);//����� ���� ���
        if (poly->link != NULL)//�������׿��� '+'�����ڸ� ������� �ʴ´�
            printf(" + ");
        poly = poly->link;//���� ������ �Ѿ��.
    }
}


int main() {
    printf("ù��° ���׽� A(x)�� �� �׵��� �Է����ּ���\n");
    polyPointer a = create_poly();//A(x) ���׽��� �����;
    printf("A(x) =  ");
    print_poly(a);//A(x) ���׽��� ����Ѵ�
    printf("\n");

    printf("�ι�° ���׽� B(x)�� �� �׵��� �Է����ּ���\n");
    polyPointer b = create_poly();//B(x) ���׽��� �����;
    printf("B(x) =  ");
    print_poly(b);//B(x) ���׽��� ����Ѵ�
    printf("\n");

    polyPointer c = padd(a, b);//A(x) + B(x)�� C(x)�� �Ѵ�.
    printf("C(x) =  ");
    print_poly(c);//C(x) ���׽��� ����Ѵ�.

}