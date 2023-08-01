/*
    program : pebo_ymh
    name : minhyuck yun
    last_edit : 23.07.23
*/

//�Ǻ���ġ
#include <stdio.h>

// �Լ� ���� ����
int pivo(int num, int* temp);

int main()
{
    int temp[2] = { 0, 1 }; // �Ǻ���ġ ������ ����ϱ� ���� �ӽ� ����
    int num;
    printf("�Ǻ���ġ ������ �� Ƚ���� �Է����ּ���.\n->");
    scanf_s("%d", &num); // ����ڷκ��� �Ǻ���ġ ������ �ε��� num�� �Է�
    printf("0 1 ");
    printf("\n����� = %d", pivo(num + 1, temp)); // num+1�� ���ڷ� �Ͽ� �Ǻ���ġ ������ num��° ���� ����ϰ� ���

    return 0;
}

/* �Ǻ���ġ ������ ����ϴ� ��� �Լ� */
int pivo(int num, int* temp)
{
    int result;
    if (num <= 1)
        return temp[0]; // �ε����� 0 �Ǵ� 1�� ���, �ʱⰪ temp[0]�� ��ȯ

    else if (num == 2)
        return temp[1]; // �ε����� 2�� ���, �ʱⰪ temp[1]�� ��ȯ

    else {
        pivo(num - 1, temp); // ��������� num-1��° �Ǻ���ġ ���� ���� ���
        result = temp[0] + temp[1]; // num��° �Ǻ���ġ ���� ���� ���
        printf("%d ", result);
        temp[0] = temp[1]; // temp �迭�� ������Ʈ�Ͽ� ���� ����� ���� �غ�
        temp[1] = result; // temp �迭�� ������Ʈ�Ͽ� ���� ����� ���� �غ�
    }
    return result; // num��° �Ǻ���ġ ���� ���� ��ȯ
}