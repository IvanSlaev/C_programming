#include <stdio.h>
#include <stdlib.h>

int main()
{
	int c1; 
	char c2 = 'A', c3 = 'B';
	/* char is integral promoted to int in expressions */
	printf("c1 = %c, as int = %d\n", c1, c1);
	printf("c2 = %c, as int = %d\n", c2, c2);
	printf("c3 = %c, as int = %d\n", c3, c3);
	/* here is an expression, in that you must consider chars as int */
	c1 = c2 + c3 - 9;
	printf("c1 = c2 + c3 - 9, that's an expression\n");
	printf("c1 = %c, as int = %d\n", c1, c1);
	printf("the next output contains an expression, so the size of c3 is 4 bytes\n");
	printf("sizeof 'A' for example = %ld\n", sizeof 'A');
	return 0;
}
