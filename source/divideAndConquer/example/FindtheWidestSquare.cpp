#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX 100

int histo[MAX];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int divide(int left, int right) {
    if (left == right)
        return histo[left];

    int mid = (left + right) / 2;//�߾� �ε���
    int leftp = mid;//���� ������(��ġ)
    int rightp = mid;//������ ������(��ġ)
    int height = histo[mid];//�߾� ���簢���� ����
    int vol = max(divide(left, mid), divide(mid + 1, right));//�����Ѵ�

    while (left < leftp || rightp < right) {
        if (left < leftp && (rightp == right || histo[leftp - 1] > histo[rightp + 1])) { 
            leftp--;//���� ��ġ�� ���̰� �� ũ�ٸ� ���������͸� �������� ��ĭ �̵� 
            height = min(height, histo[leftp]);//���� ���̿� ���� ������ ������ ���� ���� ����
        }
        else {
            rightp++;//������ ��ġ�� ���̰� �� ũ�ٸ� ***
            height = min(height, histo[rightp]);
        }
        vol = max(vol, height * (rightp - leftp + 1));//���� �Ѱ��߿��� ã�� ���簢���� ������ ��ģ���߿��� ������� ���簢���� ������ Ȯ��
    }
    return vol;
}

int main(void) {
    int n;
    scanf_s("%d", &n);

        for (int i = 0; i < n; i++) {
            scanf_s("%d", &histo[i]);
        }
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < histo[i];j++)
                printf("��");
            printf("\n");
        }
        printf("%d\n", divide(0, n - 1));
        scanf_s("%d", &n);


    return 0;
}
