#include <stdio.h>
#include <string.h>
#define MAX 501

typedef struct {
    short int vert;
    short int horiz;
}offsets;
offsets move[4] = { {0,1}, {1, 0}, {0, -1},{-1, 0} };
int M, N;
int map[MAX][MAX] ;
int cache[MAX][MAX];

void initialize() {
    for (int i = 0; i < N+2; i++) {
        for (int j = 0; j < M+2; j++) {
            cache[i][j] = 0;
        }
    }
}
void build() {
    for (int i = 0; i < N + 2; i++) {
        for (int j = 0; j < M + 2; j++) {
            if (i == 0 || i == N + 1 || j == 0 || j == M + 1) {
                map[i][j] = 0;
                continue;
            }
            scanf_s("%d", &map[i][j]);
        }
    }
}

int path(int x, int y)
{
    // ���� ��� (�������� ����)
    if (y == M && x == N) {
        return 1;
    }

    // �湮���� ���� �����̶�� ��� Ž��
    if (cache[x][y] == 0) {
        for (int i = 0; i < 4; i++) {
            int nx = x + move[i].vert;
            int ny = y + move[i].horiz;
            if (map[nx][ny] != 0 && map[x][y] > map[nx][ny]) {
                cache[x][y] += path(nx, ny);
            }
        }
    }

    // �湮�� ���̶�� �ش� ��ǥ���� ���������� ������ �� �ִ� ����� ���� ��ȯ
    return cache[x][y];
}
void printAll(int map) {
    printf("����� ����: %d\n", map);
    printf("�� �� �ִ� ��� Ƚ��-->\n");
    for (int i = 0; i < N + 2; i++) {
        for (int j = 0; j < M + 2; j++) {
            if (i == N && j == M) {
                printf("#\t");
                continue;
            }
            printf("%d\t", cache[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    printf("������ ���� ���� ���̸� �Է��ϼ���(����, ���δ� 500 ������ �ڿ���): ");
    scanf_s("%d %d", &M, &N);

    build();
    initialize();
    int result = path(1, 1);
    printAll(result);

    return 0;
}

/*
* #include <stdio.h>
#include <string.h>

#define MAX 501

typedef struct {
    short int vert;
    short int horiz;
}offsets;
offsets move[4] = { {0,1}, {1, 0}, {0, -1},{-1, 0} };

int M, N;
int map[MAX][MAX] = {
    {0,0,0,0,0,0,0},
    {0,50,45,37,32,30,0},
    {0,35,50,40,20,25,0},
    {0,30,30,25,17,28,0},
    {0,27,24,22,15,10,0},
    {0,0,0,0,0,0,0}
};
int cache[MAX][MAX];
void initialize() {
    for (int i = 0; i < N+2; i++) {
        for (int j = 0; j < M+2; j++) {
            cache[i][j] = 0;
        }
    }
}

int path(int x, int y)
{
    // ���� ��� (�������� ����)
    if (y == M && x == N) {
        return 1;
    }

    // �湮���� ���� �����̶�� ��� Ž��
    if (cache[x][y] == 0) {
        for (int i = 0; i < 4; i++) {
            int nx = x + move[i].vert;
            int ny = y + move[i].horiz;
            if (map[nx][ny] != 0 && map[x][y] > map[nx][ny]) {
                cache[x][y] += path(nx, ny);
            }
        }
    }

    // �湮�� ���̶�� �ش� ��ǥ���� ���������� ������ �� �ִ� ����� ���� ��ȯ
    return cache[x][y];
}

int main()
{
    printf("������ ���� ���� ���̸� �Է��ϼ���(����, ���δ� 500 ������ �ڿ���): ");
    scanf_s("%d %d", &M, &N);
 
    for (int i = 0; i < N+2; i++) {
        for (int j = 0; j < M+2; j++) {
            if()
            scanf_s("%d", &map[i][j]);
        }
    }

    initialize();

    printf("%d\n", path(1, 1));

    return 0;
}
* 
#include <stdio.h>

#define MAX_N 500

int map[MAX_N][MAX_N];
int dp[MAX_N][MAX_N];
int m, n;

// ���� ���� (��, ��, ��, ��)
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

// �޸������̼� �Լ� (Top-down)
int dfs(int r, int c) {
    // �̹� �湮�� ���� �ִٸ� �ش� ����� ��ȯ
    if (dp[r][c] != -1)
        return dp[r][c];

    // �������� ������ ��� 1 ��ȯ
    if (r == m - 1 && c == n - 1)
        return 1;

    dp[r][c] = 0; // �湮 ǥ��

    // ��, ��, ��, ��� �̵��Ͽ� ������ ����� ���� �����Ͽ� ����
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        // ������ ����ų� ���̰� �� ���� ��� �ǳʶ�
        if (nr < 0 || nc < 0 || nr >= m || nc >= n)
            continue;

        if (map[nr][nc] < map[r][c]) {
            dp[r][c] += dfs(nr, nc);
        }
    }

    return dp[r][c];
}

int main() {
    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &map[i][j]);
            dp[i][j] = -1; // dp �迭 �ʱ�ȭ
        }
    }

    int result = dfs(0, 0); // ������ (0, 0)�������� ��� Ž�� ����

    printf("%d\n", result);

    return 0;
}
*/
