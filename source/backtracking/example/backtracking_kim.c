/*
    program: backtracking
    name: kimminwoo
    last_edit: 23.07.14
*/
#include <iostream>
using namespace std;

int N, S, val[20];
int cnt, currentSum;

void dfs(int current) {
    if (current == N) return;

    // 현재까지의 합이 S면 결과 +1
    if (currentSum + val[current] == S) cnt++;

    // 이번 원소를 포함시키지 않고 시도
    dfs(current + 1);

    // 이번 원소를 포함시키고 시도
    currentSum += val[current];
    dfs(current + 1);

    // 마지막에 다시 이번 원소를 빼 줘야 함
    currentSum -= val[current];
}

int main() {
    scanf("%d %d", &N, &S);
    for (int i = 0; i < N; i++)
        scanf("%d", val + i);
    dfs(0);
    printf("%d\n", cnt);
}