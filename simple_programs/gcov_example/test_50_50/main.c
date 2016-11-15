#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
 
{
	int upper_limit = 20;
	int i;

	if (argc > 1) 
	{
		upper_limit = atoi(argv[1]);
	}

	for(i = 0; i < upper_limit; i++)
	{
		if (i < upper_limit / 2) 
		{
			printf("%s\n", "lower");
		}
		else
		{
			printf("%s\n", "upper");
		}
	}

	return 0;
}
