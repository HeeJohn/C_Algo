#define _CRT_SECURE_NO_WARNINGS/*항공소프트웨어공학과 202000974 이재혁*/
#include <stdio.h>
#define MAX 1000*1000    // 최댓값(모든 집의 모든 색깔들의 비용이 1000이고 집의 수가 1000일 때)  

int arr[1001][4];           // 입력받는 배열
int memo[1001][4];         //  동적프로그래밍에 사용할 배열

int min(int x, int y) {
	/* 최소값 찾는 함수 */
	return x < y ? x : y;
}

int main() {
	int N;
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= 3; j++)
			scanf("%d", &arr[i][j]);    // 값 입력받기


	memo[1][1] = arr[1][1];     // 빨강(첫번째 집)
	memo[1][2] = arr[1][2];    // 초록(첫번째 집)
	memo[1][3] = arr[1][3];   // 파랑(첫번째 집)

	for (int i = 2; i <= N; i++) {
		memo[i][1] = min(memo[i - 1][2], memo[i - 1][3]) + arr[i][1];        // i번째 집이 빨강인 경우(i-1번째는 파랑과 초록 중 최소)
		memo[i][2] = min(memo[i - 1][1], memo[i - 1][3]) + arr[i][2];       // i번째 집이 초록인 경우(i-1번째는 빨강과 파랑 중 최소)
		memo[i][3] = min(memo[i - 1][1], memo[i - 1][2]) + arr[i][3];      // i번째 집이 파랑인 경우(i-1번째는 빨강과 초록 중 최소)
	}

	// 출력
	int min = MAX + 1;
	for (int i = 1; i <= 3; i++)
		if (memo[N][i] < min)
			min = memo[N][i];
	printf("%d", min);
	return 0;
}