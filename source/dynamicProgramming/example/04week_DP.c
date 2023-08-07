/*
    program : knapsack 
    name : yeongjin kim
    last edited : 23.07.31
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_ITEMS 100
#define MAX_CAPACITY 1000

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int knapsack(int weights[], int values[], int n, int capacity, int selected[]) // ����, ��ġ, ������ ����, �賶 �ѷ�, ���õ� ����
{
    int dp[MAX_ITEMS + 1][MAX_CAPACITY + 1] = { 0 };    // ������ ������ �賶�� �ѷ��� 1���� ����

    for (int i = 1; i <= n; i++) // ���� index ����
        for (int j = 1; j <= capacity; j++) // ���� 1���� �ִ� ���Ա��� i��° ���Ǳ����� ��ġ�� �����ؼ� ������ �ظ� ����
        {
            if (weights[i-1] <= j) // i��° ������ ���԰� j���� �۰ų� ���ٸ� j�� ũ�⸦ ���� �賶�� ���� �� �ִ� ������ �ظ� ����
                dp[i][j] = max(dp[i-1][j], dp[i-1][j - weights[i-1]] + values[i-1]);  
            // dp[i][j]�� �����߱� ������ max���� ���ϴ� dp[i-1][j]�� ������ ���� ���̴�
            // dp[i-1][j]�� i-1��° ���Ǳ��� ����� ������ ��ġ���� ���̴�
            // dp[i-1][j - weights[i-1]]�� j-weights[i-1]�� �賶ũ�⿡�� ��, i��° ������ ���� �ʾ����� j�賶 ũ�⿡�� ���� �� �ִ� ������ �ظ�
            // i��° ������ ��ġ�� ��ģ ���̹Ƿ� �̰Ͱ� dp[i-1][j]�� ���Ͽ� ū ���� dp[i][j]�� �����ϴ� ���̴�
            else
                dp[i][j] = dp[i-1][j]; // i��° ������ ���԰� j���� ũ�� ������ �ظ� ����
        }

    // ���������� ���õ� ���ǵ� ����
    int i = n, j = capacity;    // ������ ������ �賶�� �ѷ�
    while (i > 0 && j > 0) // i�� ������ �����̰� j�� �賶�� �ѷ��ε� 0�� �� �� ���⶧���� 0���� Ŀ���Ѵ�
    {
        if (dp[i][j] != dp[i - 1][j])   
            // i��° ���Ǳ��� ����� ������ �ִ� ��ġ�� i-1��° ���Ǳ��� ����� ������ �ִ� ��ġ�� �ٸ���
            // i��° ������ ������ ���̹Ƿ� selected �迭�� 1�� ����
        {
            selected[i - 1] = 1;    
            j -= weights[i - 1];    //�賶�� �ѷ��� i��° ������ ���Ը� ����
        }
        i--;    // ������ ������ �ϳ� �پ���
    }

    return dp[n][capacity];
}

int main()
{
    int n; // ������ ����
    int capacity; // �賶�� �뷮
    int weights[MAX_ITEMS]; // ������ ���� �迭
    int values[MAX_ITEMS]; // ������ ��ġ �迭
    int selected[MAX_ITEMS] = { 0 }; // ���õ� ������ �����ϱ� ���� �迭

    printf("������ ������ �Է��ϼ���: ");
    scanf("%d", &n);

    printf("�賶�� �뷮�� �Է��ϼ���: ");
    scanf("%d", &capacity);

    // ������ ������ �賶�� �뷮�� 0�̸� ���α׷� ����
    printf("���ǵ��� ���Կ� ��ġ�� �Է��ϼ���:\n");
    for (int i = 0; i < n; i++)
    {
        printf("���� %d : ", i + 1);
        scanf("%d %d", &weights[i], &values[i]);
        // ������ ���԰� 0�̸� ���α׷� ����
    }

    int result = knapsack(weights, values, n, capacity, selected);
    printf("�賶�� ���� �� �ִ� ���ǵ��� �ִ� ��ġ: %d\n", result);

    printf("���õ� ���ǵ�:\n");
    for (int i = 0; i < n; i++)
    {
        if (selected[i])
        {
            printf("���� %d\n", i + 1);
        }
    }

    return 0;
}
