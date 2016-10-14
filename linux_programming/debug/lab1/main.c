#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

int main (int argc, char *args[])
{
	char *buf;
	int size = 800, index = 801;
	
	if ( argc > 1 )
		index = atoi (argv[1]);
	if ( argc > 2 )
		size = atoi (argv[2]);
	
	buf = malloc (size);
	
	printf("I alloc %d bytes, I'm going to use %d elements\n", size, index);
	
	buf[index] = 1;
	
	printf("buf[index] = %d\n", buf[index]);
	
	exit(0);
}
