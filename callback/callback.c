#include <stdio.h>
#include <stdlib.h>

void CallingFunction(int (*numberSource)()) {
	printf("sum: %d\n", numberSource() + numberSource());
}

int FirstNumber()
{
	return 5000;
}

int SecondNumber()
{
	return 2500;
}

int main()
{
	CallingFunction(&FirstNumber);
	CallingFunction(&SecondNumber);
	return 0;
}
