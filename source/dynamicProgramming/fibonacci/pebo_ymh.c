/*
    program : pebo_ymh
    name : minhyuck yun
    last_edit : 23.07.23
*/

//피보나치
#include <stdio.h>

// 함수 원형 선언
int pivo(int num, int* temp);

int main()
{
    int temp[2] = { 0, 1 }; // 피보나치 수열을 계산하기 위한 임시 변수
    int num;
    printf("피보나치 수열을 할 횟수를 입력해주세요.\n->");
    scanf_s("%d", &num); // 사용자로부터 피보나치 수열의 인덱스 num을 입력
    printf("0 1 ");
    printf("\n결과값 = %d", pivo(num + 1, temp)); // num+1을 인자로 하여 피보나치 수열의 num번째 값을 계산하고 출력

    return 0;
}

/* 피보나치 수열을 계산하는 재귀 함수 */
int pivo(int num, int* temp)
{
    int result;
    if (num <= 1)
        return temp[0]; // 인덱스가 0 또는 1인 경우, 초기값 temp[0]을 반환

    else if (num == 2)
        return temp[1]; // 인덱스가 2인 경우, 초기값 temp[1]을 반환

    else {
        pivo(num - 1, temp); // 재귀적으로 num-1번째 피보나치 수열 값을 계산
        result = temp[0] + temp[1]; // num번째 피보나치 수열 값을 계산
        printf("%d ", result);
        temp[0] = temp[1]; // temp 배열을 업데이트하여 다음 계산을 위해 준비
        temp[1] = result; // temp 배열을 업데이트하여 다음 계산을 위해 준비
    }
    return result; // num번째 피보나치 수열 값을 반환
}