#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct {
    int key;
} element;

void adjust(element a[], int root, int n);
void heapSort(element a[], int n);
void print(element a[], int n);

int main() {
    element a[11]; // �迭 ũ�⸦ 10���� ����
    for (int i = 1; i < 11; i++) { // Index�� 1���� �����ؼ� 10���� ä���ش�.
        scanf("%d", &a[i].key);
    }

    heapSort(a, 10); // �迭�� ũ�⸦ 10���� ����

    printf("\n\nSorted array: ");
    print(a, 10); // �迭�� ũ�⸦ 10���� ����

    return 0;
}

void adjust(element a[], int root, int n) {
    /* �ִ� ���� ������ ������ִ� �Լ� */
    int child, rootkey;
    element temp;
    temp = a[root];
    rootkey = a[root].key;
    child = 2 * root; // left child
    while (child <= n) {
        if ((child < n) && (a[child].key < a[child + 1].key))
            child++;
        if (rootkey > a[child].key) // root�� �ְ� Ʈ���� ��
            break;
        else {
            a[child / 2] = a[child]; // �ڽİ� �θ� �ٲٱ�
            child *= 2;
        }
    }
    a[child / 2] = temp;
    printf("\n���� �� (root %d): ", root); // 
    print(a, n); // �迭�� ũ�⸦ n���� ����
}

void heapSort(element a[], int n) {
    /* ���� ������ ���ִ� �Լ� */
    int i, j;
    element temp;

    printf("===========�ִ� ������ �����ϰڽ��ϴ�.=============\n");
    for (i = n / 2; i > 0; i--) {   // �ִ� ������ ���� �����ش�. 
        adjust(a, i, n);
    }
    printf("====================���� �Ϸ�======================\n\n");

    printf("==============���� ���� �ϰڽ��ϴ�.================\n");
    printf("�ʱ� ���� : ");
    print(a, 10);
    for (i = n - 1; i > 0; i--) {   // ���� ���� ���ش�. 
        SWAP(a[1], a[i + 1], temp);
        adjust(a, 1, i);
    }
}

void print(element a[], int n) {
    for (int i = 1; i <= n; i++) {
        printf("%d ", a[i].key);
    }
    printf("\n");
}