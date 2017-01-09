#include <stdio.h>
#include <stdlib.h>

int sum(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

int (*return_operation(const char *operator))(int a, int b)
{
	switch (*operator) {
		case '+':
			return sum;
			break;
		case '-':
			return sub;
			break;
		default:
			printf("invalid operator\n");
	}
}

int main(int argc, char *argv[])
{
	int result;
	int a = atoi(argv[1]);
	int b = atoi(argv[3]);
	result = return_operation(argv[2])(a, b);
	printf("%d\n", result);
	return 0;
}
