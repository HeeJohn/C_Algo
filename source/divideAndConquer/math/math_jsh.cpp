/*#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) if(!((p)=(stackpointer)malloc(s))){fprintf(stderr,"Insufficient memory");exit(EXIT_FAILURE);}
typedef struct stack* stackpointer;
typedef struct stack {
	long long int data;
	stackpointer link;
}stack;

stackpointer fibonacci;//�Ǻ���ġ ������ ���� ����

void fibocalcul(int n);
void push(int data);
int main() {

	int n;
	printf("���° �Ǻ���ġ ������ ���ϰ�ͳ���? -> ");
	scanf_s("%d", &n);
	fibocalcul(n);
}
void fibocalcul(int n) {
	push(0);//1��
	push(1);//2��
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

int main()
{   int n, m;
	printf("n ^ m�� ���ϰڽ��ϴ� n��m�� ������� �ۼ��ϼ���\n -> ");
	scanf_s("%d %d", &n, &m);
	printf("%d ^ %d = %d ", n,m,pow(n,m));
}*/
#include <stdio.h>
int factorial(int n)
{
	if (n <= 1)                            //1! �� 1 �̹Ƿ� 1 ��ȯ
		return 1;
	else
		return (n * factorial(n - 1));    //���ȣ�� �̿��ؼ� n * (n-1)! ���
}
int main() {
	int n;
	printf("���丮�� n!�� ���ϰڽ��ϴ�. n�� �� �ڿ����� �Է����ּ��� -> ");
	scanf_s("%d", &n);
	printf("%d! = %d\n",n,factorial(n));

}