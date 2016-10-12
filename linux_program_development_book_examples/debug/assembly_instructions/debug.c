#include <stdio.h>

void printMessage(int v)
{
	int g = v + 5;
	g = g + 3;
	printf("The value of g is %d\n", g);
}

int main()
{
	
	int a = 0;
	int b = 1;
	int c = 2;
	int d = 3;

	
	
	printMessage(a);
	printMessage(b);
	printMessage(c);
	printMessage(d);

	return 0;
}
