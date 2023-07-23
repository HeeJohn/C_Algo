/*
    program : guje_ymh
    name : minhyuck yun
    last_edit : 23.07.23
*/

//�ŵ�����
#include <stdio.h>

// �Լ� ���� ����
int je(int num, int n);

int main()
{
    int num, n, x;

    // ����ڷκ��� ���� �Է¹޽��ϴ�.
    printf("� ���� ���������ұ��?\n->");
    scanf_s("%d", &num);
    printf("�� �����ұ��?\n->");
    scanf_s("%d", &n);

    // je �Լ��� ȣ���Ͽ� num�� n ���� ���� ����մϴ�.
    x = je(num, n);

    // ����� ���� ����մϴ�.
    printf("����� ��\n=%2d", x);

    return 0;
}

/* ��� �Լ��� ����Ͽ� ���� num�� n �������� ����ϴ� �Լ� */
int je(int num, int n)
{
    if (n == 0)
        return 1; // n�� 0�� ���, num�� 0 ������ �׻� 1�̹Ƿ� 1�� ��ȯ�մϴ�.
    else
    {
        // ��������� num�� n-1 ���� ���� ����ϰ�, num�� ���Ͽ� num�� n ���� ���� ���մϴ�.
        return num * je(num, n - 1);
    }
}