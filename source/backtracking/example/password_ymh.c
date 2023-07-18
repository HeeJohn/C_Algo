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

int L, C;               // ��ȣ�� ���̿� ��� ������ ������ ����
char pass[max];         // ��� ������ ���ڿ�
char ans[max];          // ������ ��ȣ ����
int a[max];             // ����� ���� ǥ�� �迭

// �迭 ��� �� �Լ�
int cmp(const void* lhs, const void* rhs) {
    if (*(char*)lhs > *(char*)rhs)
        return 1;
    else
        return -1;
}

// ����ڷκ��� �ʱ� ���ڿ� �Է¹ޱ�
void Input_Base_pass() {
    printf("��ȣ�� ������ ���ڿ��� ������ �Է��ϼ���.(3�� �̻� 15�� ����)\n->");
    scanf("%d", &L);
    printf("��ȣ�� ����� ���ڸ� �� �� �� ���� �Է��ϼ���.(���ڿ� ���� �̻� 15�� ����)\n->");
    scanf("%d", &C);
    for (int i = 0; i < C; i++) {
        printf("��ȣ�� ����� ���ڸ� ������ ����Ͽ� �Է����ּ���.");
        scanf(" %c", &pass[i]);
    }
    // �Է¹��� ���ڿ��� ���ĺ� ������ ����
    qsort(pass, C, sizeof(char), cmp);
}

// DFS�� ���� ��ȣ ���� ����
void dfs(int depth, int start) {
    // ��ȣ�� ���̰� ��ǥ ���̿� ������ ���
    if (depth == L) {
        bool flag = false;
        int cnt = 0;
        for (int i = 0; i < depth; i++) {
            // ��ȣ�� ������ ���ԵǾ� �ִ��� Ȯ��
            if (ans[i] == 'a' || ans[i] == 'e' || ans[i] == 'i' || ans[i] == 'o' | ans[i] == 'u') {
                flag = true;
            }
            else
                cnt++;  // ������ ���� ����
        }
        // ������ �ּ� 1���̰�, ������ ������ 2�� �̻��� ���
        if (flag && cnt >= 2) {
            // ��ȣ ���
            for (int i = 0; i < depth; i++)
                printf("%c", ans[i]);
            printf("\n");
            return;
        }
        else
            return;
    }

    // DFS ��� ȣ��
    for (int i = start; i < C; i++) {
        if (!a[i]) {
            a[i] = 1;                   // ����� ���� ǥ��
            ans[depth] = pass[i];       // ���� ��ȣ ���տ� ���� �߰�
            dfs(depth + 1, i + 1);      // ���� ���̷� ����
            a[i] = 0;                   // ����� ���� ǥ�� ����
        }
    }
}

int main() {
    Input_Base_pass();      // �ʱ� ���ڿ� �Է¹ޱ�
    dfs(0, 0);              // DFS�� ���� ��ȣ ���� ����

    return 0;
}