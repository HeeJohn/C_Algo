#define _CRT_SECURE_NO_WARNINGS/*항공소프트웨어공학과 202000974 이재혁*/
#include <stdio.h>
int main()
{/* 설탕 배달 문제: 
    1. 3kg, 5kg 단위로만 배달 가능. 
	2. 최소 봉지로 배달해야 함.
*/


	int n;                //  목표 무게
	int min = -1;         //  최소 봉지(결과)
	int temp;             //  계산 과정에 사용할 변수
	int cnt;              //  봉지 개수 세는 변수
	int k = 0;            //  반복문 탈출을 위한 표시 변수

	printf("배달할 설탕의 무게를 입력하세요(kg): ");
	scanf("%d", &n);

	for (int i = n / 5;i >= 0;i--)              
	{/* 5kg 봉지 수가 가장 많을 때(없을 수 있음)부터 0이 될 때까지 반복(답을 찾으면 반복문 탈출) */
		temp = n - i * 5;
		cnt = i;
		for (int j = 0;temp >= 0;j++)
		{ /* 3kg 봉지 계산 반복문(없을 수 있음) */
			if (temp == 0)
			{ /* temp가 0이면 답을 찾은 것이다 */
				min = cnt;
				k = 1;
				break;
			}
			temp -= 3;
			cnt++;
		}
		if (k)          // 값을 찾았다면(반복문 탈출을 위해) 
			break;
	}

	printf("최소 봉지: %d", min);

	return 0;
}