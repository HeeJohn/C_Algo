/*
    program : password_ymh
    name : minhyuck yun
    last_edit : 23.07.15
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define max 18

int L, C;               // 암호의 길이와 사용 가능한 문자의 개수
char pass[max];         // 사용 가능한 문자열
char ans[max];          // 생성된 암호 조합
int a[max];             // 사용한 문자 표시 배열

// 배열 요소 비교 함수
int cmp(const void* lhs, const void* rhs) {
    if (*(char*)lhs > *(char*)rhs)
        return 1;
    else
        return -1;
}

// 사용자로부터 초기 문자열 입력받기
void Input_Base_pass() {
    printf("암호로 지정할 문자열의 갯수를 입력하세요.(3개 이상 15개 이하)\n->");
    scanf("%d", &L);
    printf("암호에 사용할 문자를 총 몇 개 쓸지 입력하세요.(문자열 갯수 이상 15개 이하)\n->");
    scanf("%d", &C);
    for (int i = 0; i < C; i++) {
        printf("암호에 사용할 문자를 공백을 사용하여 입력해주세요.");
        scanf(" %c", &pass[i]);
    }
    // 입력받은 문자열을 알파벳 순서로 정렬
    qsort(pass, C, sizeof(char), cmp);
}

// DFS를 통해 암호 조합 생성
void dfs(int depth, int start) {
    // 암호의 길이가 목표 길이에 도달한 경우
    if (depth == L) {
        bool flag = false;
        int cnt = 0;
        for (int i = 0; i < depth; i++) {
            // 암호에 모음이 포함되어 있는지 확인
            if (ans[i] == 'a' || ans[i] == 'e' || ans[i] == 'i' || ans[i] == 'o' | ans[i] == 'u') {
                flag = true;
            }
            else
                cnt++;  // 자음의 개수 증가
        }
        // 모음이 최소 1개이고, 자음의 개수가 2개 이상인 경우
        if (flag && cnt >= 2) {
            // 암호 출력
            for (int i = 0; i < depth; i++)
                printf("%c", ans[i]);
            printf("\n");
            return;
        }
        else
            return;
    }

    // DFS 재귀 호출
    for (int i = start; i < C; i++) {
        if (!a[i]) {
            a[i] = 1;                   // 사용한 문자 표시
            ans[depth] = pass[i];       // 현재 암호 조합에 문자 추가
            dfs(depth + 1, i + 1);      // 다음 깊이로 진행
            a[i] = 0;                   // 사용한 문자 표시 해제
        }
    }
}

int main() {
    Input_Base_pass();      // 초기 문자열 입력받기
    dfs(0, 0);              // DFS를 통해 암호 조합 생성

    return 0;
}