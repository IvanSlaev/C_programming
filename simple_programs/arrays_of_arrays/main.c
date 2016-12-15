#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define DEATH(mess) { perror(mess); exit(errno); }

int main(int argc, const char *argv[])
{
	int i, j;
	for (i = 1; i < argc; i++) 
	{
		int sum = 0;
		int size = strlen(argv[i]);
		for (j = 0; j < size; j++) 
		{	
			sum += argv[i][j] - 48;
		}
		printf("%d\n", sum);
	}
	return 0;
}
