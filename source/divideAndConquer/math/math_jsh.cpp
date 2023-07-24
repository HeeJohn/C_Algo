#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) if(!((p)=(stackpointer)malloc(s))){fprintf(stderr,"Insufficient memory");exit(EXIT_FAILURE);}
typedef struct stack* stackpointer;
typedef struct stack {
	long long int data;
	stackpointer link;
}stack;

stackpointer fibonacci;//피보나치 수열을 담을 스택

void fibocalcul(int n);
void push(int data);
int pow(double x, int n);
int factorial(int n);
int main() {

	int n;
	printf("몇번째 피보나치 수열을 구하고싶나요? -> ");
	scanf_s("%d", &n);
	fibocalcul(n);
	
	
	printf("n ^ m을 구하겠습니다 n과m을 순서대로 작성하세요\n -> ");
	scanf_s("%d %d", &n, &m);
	printf("%d ^ %d = %d ", n,m,pow(n,m));


	printf("팩토리얼 n!을 구하겠습니다. n에 들어갈 자연수를 입력해주세요 -> ");
	scanf_s("%d", &n);
	printf("%d! = %d\n",n,factorial(n));
}
void fibocalcul(int n) {
	push(0);//1항
	push(1);//2항
	int data;

	for (int i = 2;i < n;i++) {
		data = fibonacci->data + fibonacci->link->data;
		push(data);

	}
}
void push(int data) {
	stackpointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = data;
	if (data == 0)
		temp->link = NULL;
	else
		temp->link = fibonacci;
	fibonacci = temp;
	printf("%d\n", data);
}

#include <stdio.h>

int pow(double x, int n)
{
	if (n == 0) return 1;
	else if ((n % 2) == 0)
		return pow(x * x, n / 2);
	else return x * pow(x * x, (n - 1) / 2);
}

#include <stdio.h>
int factorial(int n)
{
	if (n <= 1)                            //1! 은 1 이므로 1 반환
		return 1;
	else
		return (n * factorial(n - 1));    //재귀호출 이용해서 n * (n-1)! 계산
}
