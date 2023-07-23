/*
    program : quickSort_ymh
    name : minhyuck yun
    last_edit : 23.07.23
*/

//������
#include <stdio.h>

#define SWAP(a, b, temp) temp = a, a = b, b = temp // SWAP ��ũ�θ� �����Ͽ� �� ������ ���� ��ȯ�ϴµ� ���˴ϴ�.

typedef struct {
    int key;
}element; // element��� �̸��� ����ü�� �����մϴ�. �� ����ü�� �����Ϸ��� �����͸� ���� �� ���˴ϴ�.

void quickSort(element a[], int left, int right); // �� ���� �Լ��� ������ �����մϴ�.

int main(void)
{
    int left = 0; // ������ �迭�� ���� �ε����� ������ �����Դϴ�.
    int right = 9; // ������ �迭�� �� �ε����� ������ �����Դϴ�.
    element a[10] = { 26, 5, 37, 1, 61, 11, 59, 15, 48, 19 }; // �����Ϸ��� ���� �����Ͱ� ��� �迭�Դϴ�.

    printf("�ʱⰪ\n");
    for (int i = 0; i < 10; i++)
        printf("%d  ", a[i]);
    printf("\n");

    quickSort(a, left, right); // �� ���� �Լ��� ȣ���Ͽ� �迭�� �����մϴ�.

    printf("���� ��\n");
    for (int i = 0; i < 10; i++)
        printf("%d  ", a[i]);
    printf("\n");
}

void quickSort(element a[], int left, int right)
{
    int pivot, i, j; // pivot�� ������ �Ǵ� ������ �ε���, i�� j�� ���� ���ʰ� �����ʿ��� pivot�� ���� ���ҵ��� �ε����� ����ŵ�ϴ�.
    element temp; // SWAP ��ũ�θ� ����Ͽ� �� ��ȯ �� �ӽ÷� ����� ����ü �����Դϴ�.

    if (left < right) // �迭�� ũ�Ⱑ 1 �̻��� ��쿡�� ������ �����մϴ�. ��, left�� right���� ���� ���� ��������� ������ �����մϴ�.
    {
        i = left; // i�� �迭�� ���� ������ �����մϴ�.
        j = right + 1; // j�� �迭�� ������ ������ �����մϴ�.
        pivot = a[left].key; // �迭�� ���� ���ʿ� �ִ� ���Ҹ� pivot���� �����մϴ�.

        do
        {
            do
                i++; // pivot���� ũ�ų� ���� ���Ҹ� ã�� ������ i�� ������ŵ�ϴ�.
            while (a[i].key < pivot);

            do
                j--; // pivot���� �۰ų� ���� ���Ҹ� ã�� ������ j�� ���ҽ�ŵ�ϴ�.
            while (a[j].key > pivot);

            if (i < j) // i�� j�� �������� ���� ��� (���� ������ ���ҵ��� �����ִ� ���)
                SWAP(a[i], a[j], temp); // i�� j�� �ش��ϴ� ���Ҹ� ��ȯ�մϴ�. �̸� ���� pivot�� �߽����� ������ ���� ��, �������� ū ���� ������ ���ĵ˴ϴ�.
        } while (i < j); // i�� j�� ������ ������ �ݺ��մϴ�.

        SWAP(a[left], a[j], temp); // pivot�� a[j]�� ��ȯ�մϴ�. �̷ν� pivot�� �ùٸ� ��ġ�� ��ġ�մϴ�.

        quickSort(a, left, j - 1); // pivot�� �߽����� ���� �κ� �迭�� ��������� �����մϴ�.
        quickSort(a, j + 1, right); // pivot�� �߽����� ������ �κ� �迭�� ��������� �����մϴ�.
    }
}