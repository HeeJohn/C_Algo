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

int knapsack(int weights[], int values[], int n, int capacity, int selected[]) // 무게, 가치, 물건의 개수, 배낭 총량, 선택된 물건
{
    int dp[MAX_ITEMS + 1][MAX_CAPACITY + 1] = { 0 };    // 물건의 개수와 배낭의 총량이 1부터 시작

    for (int i = 1; i <= n; i++) // 물건 index 증가
        for (int j = 1; j <= capacity; j++) // 무게 1부터 최대 무게까지 i번째 물건까지의 가치를 조합해서 최적의 해를 구함
        {
            if (weights[i-1] <= j) // i번째 물건의 무게가 j보다 작거나 같다면 j의 크기를 가진 배낭에 넣을 수 있는 최적의 해를 대입
                dp[i][j] = max(dp[i-1][j], dp[i-1][j - weights[i-1]] + values[i-1]);  
            // dp[i][j]로 대입했기 때문에 max에서 비교하는 dp[i-1][j]는 이전에 구한 해이다
            // dp[i-1][j]는 i-1번째 물건까지 고려한 최적의 가치해의 값이다
            // dp[i-1][j - weights[i-1]]는 j-weights[i-1]의 배낭크기에서 즉, i번째 물건을 넣지 않았을때 j배낭 크기에서 얻을 수 있는 최적의 해를
            // i번째 물건의 가치와 합친 것이므로 이것과 dp[i-1][j]를 비교하여 큰 값을 dp[i][j]에 대입하는 것이다
            else
                dp[i][j] = dp[i-1][j]; // i번째 물건의 무게가 j보다 크면 기존의 해를 대입
        }

    // 최종적으로 선택된 물건들 추적
    int i = n, j = capacity;    // 물건의 개수와 배낭의 총량
    while (i > 0 && j > 0) // i는 물건의 개수이고 j는 배낭의 총량인데 0이 될 수 없기때문에 0보다 커야한다
    {
        if (dp[i][j] != dp[i - 1][j])   
            // i번째 물건까지 고려한 물건의 최대 가치와 i-1번째 물건까지 고려한 물건의 최대 가치가 다를때
            // i번째 물건을 선택한 것이므로 selected 배열에 1을 대입
        {
            selected[i - 1] = 1;    
            j -= weights[i - 1];    //배낭의 총량에 i번째 물건의 무게를 빼줌
        }
        i--;    // 물건의 개수도 하나 줄어든다
    }

    return dp[n][capacity];
}

int main()
{
    int n; // 물건의 개수
    int capacity; // 배낭의 용량
    int weights[MAX_ITEMS]; // 물건의 무게 배열
    int values[MAX_ITEMS]; // 물건의 가치 배열
    int selected[MAX_ITEMS] = { 0 }; // 선택된 물건을 추적하기 위한 배열

    printf("물건의 개수를 입력하세요: ");
    scanf("%d", &n);

    printf("배낭의 용량을 입력하세요: ");
    scanf("%d", &capacity);

    // 물건의 개수와 배낭의 용량이 0이면 프로그램 종료
    printf("물건들의 무게와 가치를 입력하세요:\n");
    for (int i = 0; i < n; i++)
    {
        printf("물건 %d : ", i + 1);
        scanf("%d %d", &weights[i], &values[i]);
        // 물건의 무게가 0이면 프로그램 종료
    }

    int result = knapsack(weights, values, n, capacity, selected);
    printf("배낭에 담을 수 있는 물건들의 최대 가치: %d\n", result);

    printf("선택된 물건들:\n");
    for (int i = 0; i < n; i++)
    {
        if (selected[i])
        {
            printf("물건 %d\n", i + 1);
        }
    }

    return 0;
}
