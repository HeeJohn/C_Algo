/*
	program:fibonacci
	name:kimminwoo
	last_edit:23.07.22
*/

#include <stdio.h>

int fibonacci(int x);

void main() {
	int n;
	
	printf("몇번째까지 더할지 입력하시오\n");
	scanf_s("%d", &n);

	for (int i = 0; i < n; i++)
		printf("%d  ", fibonacci(i));


}

int fibonacci(int x)
{
	if (x <= 0)
		return 0;
	else if (x == 1)
		return 1;
	else
		return fibonacci(x - 1) + fibonacci(x - 2);
}