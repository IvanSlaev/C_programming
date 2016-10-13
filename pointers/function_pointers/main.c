#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	/* basic function to point to */
	int add(int a, int b)
	{
		return a + b;
	}
	
	int mult(int a, int b)
	{
		return a * b;
	}
	
	/* definition of a pointer */
	int (*pointer1)(int, int);
	/* ... */
	int (*pointerN)(int, int);
	
	/* point to function */
	pointer1 = &add;
	/* ... */
	pointerN = &mult;
	
	/* using the pointer */
	int sum = pointer1(4, 5);
	printf("Sum: %d\n", sum);
	int product = pointerN(4, 5);
	printf("Product: %d\n", product);
	
	/* using the pointer in function, you can even use different names
	 *  so you declare pointer as an argument and after calling the
	 * function you can give it  */
	int commonFunction(int (*point)(int, int))
	{
		int a = 4, b = 5;
		return point(a, b);
	}
	printf("In function\n");
	sum = commonFunction(pointer1);
	printf("Sum: %d\n", sum);
	product = commonFunction(pointerN);
	printf("Product: %d\n", product);
	
	return 0;
}
