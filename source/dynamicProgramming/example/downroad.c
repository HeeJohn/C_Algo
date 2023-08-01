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
    // 기저 사례 (목적지에 도달)
    if (y == M && x == N) {
        return 1;
    }

    // 방문하지 않은 지점이라면 계속 탐색
    if (cache[x][y] == 0) {
        for (int i = 0; i < 4; i++) {
            int nx = x + move[i].vert;
            int ny = y + move[i].horiz;
            if (map[nx][ny] != 0 && map[x][y] > map[nx][ny]) {
                cache[x][y] += path(nx, ny);
            }
        }
    }

    // 방문한 곳이라면 해당 좌표에서 목적지까지 도달할 수 있는 경로의 개수 반환
    return cache[x][y];
}
void printAll(int map) {
    printf("경로의 개수: %d\n", map);
    printf("갈 수 있는 경로 횟수-->\n");
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
    printf("지도의 가로 세로 길이를 입력하세요(가로, 세로는 500 이하의 자연수): ");
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
    // 기저 사례 (목적지에 도달)
    if (y == M && x == N) {
        return 1;
    }

    // 방문하지 않은 지점이라면 계속 탐색
    if (cache[x][y] == 0) {
        for (int i = 0; i < 4; i++) {
            int nx = x + move[i].vert;
            int ny = y + move[i].horiz;
            if (map[nx][ny] != 0 && map[x][y] > map[nx][ny]) {
                cache[x][y] += path(nx, ny);
            }
        }
    }

    // 방문한 곳이라면 해당 좌표에서 목적지까지 도달할 수 있는 경로의 개수 반환
    return cache[x][y];
}

int main()
{
    printf("지도의 가로 세로 길이를 입력하세요(가로, 세로는 500 이하의 자연수): ");
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

// 방향 벡터 (상, 하, 좌, 우)
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

// 메모이제이션 함수 (Top-down)
int dfs(int r, int c) {
    // 이미 방문한 적이 있다면 해당 결과를 반환
    if (dp[r][c] != -1)
        return dp[r][c];

    // 도착점에 도달한 경우 1 반환
    if (r == m - 1 && c == n - 1)
        return 1;

    dp[r][c] = 0; // 방문 표시

    // 상, 하, 좌, 우로 이동하여 가능한 경로의 수를 누적하여 구함
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        // 범위를 벗어나거나 높이가 더 높은 경우 건너뜀
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
            dp[i][j] = -1; // dp 배열 초기화
        }
    }

    int result = dfs(0, 0); // 시작점 (0, 0)에서부터 경로 탐색 시작

    printf("%d\n", result);

    return 0;
}
*/
