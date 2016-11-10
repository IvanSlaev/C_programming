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
	
	/* using the function pointers in functions (a.k.a callback funcs), 
	 * you can even use different names
	 *  so you declare pointer as an argument and after calling the
	 * function you can give it  */
	void print(int (*point)(int, int))
	{
		int a = 4, b = 5;
		printf("Sum: %d\n", point(a, b)); 
	}
	printf("In function\n");
	print(pointer1);
	print(pointerN);
	
	return 0;
}
