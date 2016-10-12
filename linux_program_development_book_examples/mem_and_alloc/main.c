#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *args[])
{
	int pageSize;
	
	pageSize = getpagesize();
	
	printf("Page size: %d\n", pageSize);
}
