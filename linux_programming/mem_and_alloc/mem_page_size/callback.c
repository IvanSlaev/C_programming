#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printPageSize(int (*getitfirst)())
{
	int pageSize;
	
	pageSize = getitfirst();
	
	printf("Page size: %d\n", pageSize);
}


int main (int argc, char *args[])
{
	printPageSize(&getpagesize);
}
