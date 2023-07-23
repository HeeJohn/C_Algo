/*
    program : peck_ymh
    name : minhyuck yun
    last_edit : 23.07.23
*/

// ���丮��
#include <stdio.h>

// �Լ� ���� ����
int peck(int num);

int main()
{
    int num, x;

    // ����ڷκ��� ���� �Է¹޽��ϴ�.
    printf("� ���� ���丮���ұ��?\n->");
    scanf_s("%d", &num);

    // peck �Լ��� ȣ���Ͽ� num�� ���丮�� ���� ����մϴ�.
    x = peck(num);

    // ����� ���� ����մϴ�.
    printf("����� ��\n=%2d", x);

    return 0;
}

/* ��� �Լ��� ����Ͽ� ���� num�� ���丮���� ����ϴ� �Լ� */
int peck(int num)
{
    if (num == 0)
        return 1; // ���丮���� base case: 0!�� �׻� 1�̹Ƿ� 1�� ��ȯ�մϴ�.
    else
    {
        // ��������� (num - 1)�� ���丮�� ���� ����ϰ�, num�� ���Ͽ� num�� ���丮�� ���� ���մϴ�.
        return num * peck(num - 1);
    }
}