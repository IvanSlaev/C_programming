#include <stdio.h>
#include <stdlib.h>

#define MB (1024*1024)

int main (int argc, char *args[])
{
	int j;
	char *buf;
	/* allocate 4 MB at a time */
	for (int i = 0; ; i++)
	{
		if (i%100 == 0)
		{
			printf("%d ", i);
		}
		buf = malloc(MB);
	}
	
}
