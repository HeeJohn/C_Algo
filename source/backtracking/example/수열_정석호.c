#include <stdio.h>
#include <Windows.h>
//1부터 N까지 자연수 중에서 중복 없이 M개를 고른 수열
int n, m;
int result[1000];
int visit_just_number[1000];

void permutation(int digit)
{
	int i;

	if (digit == m)//순열의 자리가 다 찼다면 순열을 출력한다.
	{
		for (int i = 0; i < m; i++)
			printf("%d ", result[i]);
		printf("\n");
	}
	else
	{
		for (i = 1; i <= n; i++)
		{
			if (visit_just_number[i] == false)//방문하지 않은 숫자라면
			{
				result[digit] = i;//순열에 숫자를 넣는다
				visit_just_number[i] = true;//방문했다고 표시를 남긴다
				permutation(digit + 1);//다음 자릿수로 넘어간다.
				visit_just_number[i] = false;//재귀 호출이 끝나면 방문 여부를 false로 초기화 해서 다른 자리에 올 수 있게 한다.
			}
		}
	}
}
void inputNM(void) {
	printf("1부터 N까지 자연수 중에서 중복 없이 M개를 고른 수열을 모두 찾을것입니다.\n");
	printf("N과M을 입력해주세요.(조건 : N>=M) : ");
	scanf_s("%d %d", &n, &m);
	while (m > n) {
		printf("다시 입력주세요!!\n"); system("pause");system("cls");
		printf("1부터 N까지 자연수 중에서 중복 없이 M개를 고른 수열을 모두 찾을것입니다.\n");
		printf("N과M을 입력해주세요.(조건 : N>=M) : ");
		scanf_s("%d %d", &n, &m);
	}
}

int main(void)
{
	inputNM();//입력함수
	permutation(0);
	return 0;
}