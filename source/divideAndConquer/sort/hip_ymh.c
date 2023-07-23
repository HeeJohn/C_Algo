/*
    program : hip_ymh
    name : minhyuck yun
    last_edit : 23.07.23
*/

//��������
#include <stdio.h>

#define SWAP(a, b, temp) temp = a, a = b, b = temp // SWAP ��ũ�θ� �����Ͽ� �� ������ ���� ��ȯ�ϴµ� ���˴ϴ�.

typedef struct {
    int key;
}element; // element��� �̸��� ����ü�� �����մϴ�. �� ����ü�� �����Ϸ��� �����͸� ���� �� ���˴ϴ�.

void heapSort(element a[], int n);
void adjust(element a[], int root, int n);

int main(void)
{
    element a[8] = { 0, 26, 5, 37, 1, 61, 11, 59 }; // �ε��� 0�� ������� ������, �����ʹ� �ε��� 1���� �����մϴ�.
    printf("�ʱⰪ\n");
    for (int i = 1; i < 8; i++)
        printf("%d  ", a[i]);
    printf("\n");

    heapSort(a, 7); // ���� ���� �Լ��� ȣ���Ͽ� �迭�� �����մϴ�.

    printf("���� ��\n");
    for (int i = 1; i < 8; i++)
        printf("%d  ", a[i]);
    printf("\n");
}

void heapSort(element a[], int n)
{
    int i, j;
    element temp;

    // �ʱ� ������ �����մϴ�.
    for (i = n / 2; i > 0; i--)
        adjust(a, i, n);

    // ���� ������ �����մϴ�.
    for (i = n - 1; i > 0; i--)
    {
        SWAP(a[1], a[i + 1], temp); // �ִ� ������ �ִ밪(��Ʈ ���)�� ���� ���ĵ��� ���� �κ��� ������ ���� ��ȯ�մϴ�.
        adjust(a, 1, i); // ��ȯ�� ��Ʈ ��带 �������� �ִ� ���� �Ӽ��� �����ϵ��� �����մϴ�.
    }
}

void adjust(element a[], int root, int n)
{
    int child, rootkey;
    element temp;
    temp = a[root];
    rootkey = a[root].key;
    child = 2 * root;

    while (child <= n)
    {
        if ((child < n) && (a[child].key < a[child + 1].key))
            child++; // �� �ڽ� �� �� ū ���� ���� �ڽ��� �����մϴ�.

        if (rootkey > a[child].key)
            break; // �ִ� ���� �Ӽ��� �����ϸ� ������ �����մϴ�.
        else
        {
            a[child / 2] = a[child]; // �θ� ���� �� ū �ڽ� ��带 ��ȯ�մϴ�.
            child *= 2; // �ڽ� ���� �̵��մϴ�.
        }
    }

    a[child / 2] = temp; // ���������� �θ� ���� ��ȯ�Ǿ�� �� ��ġ�� ���� root ��� ���� ��ġ�մϴ�.
}