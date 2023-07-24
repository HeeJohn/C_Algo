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

    // ��������� ���� S�� ��� +1
    if (currentSum + val[current] == S) cnt++;

    // �̹� ���Ҹ� ���Խ�Ű�� �ʰ� �õ�
    dfs(current + 1);

    // �̹� ���Ҹ� ���Խ�Ű�� �õ�
    currentSum += val[current];
    dfs(current + 1);

    // �������� �ٽ� �̹� ���Ҹ� �� ��� ��
    currentSum -= val[current];
}

int main() {
    scanf("%d %d", &N, &S);
    for (int i = 0; i < N; i++)
        scanf("%d", val + i);
    dfs(0);
    printf("%d\n", cnt);
}