#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>

#define PRINTIT(a) fprintf(stderr,"     " #a   "\t= %d", mi->a);

void dump_mi (struct mallinfo *mi)
{
	PRINTIT(arena);
	PRINTIT(ordblks);
	PRINTIT(smblks);
	fprintf(stderr, "\n");
	PRINTIT(hblks);
	PRINTIT(hblkhd);
	PRINTIT(usmblks);
	fprintf(stderr, "\n");
	PRINTIT(fsmblks);
	PRINTIT(uordblks);
	PRINTIT(keepcost);
	fprintf(stderr, "\n");
}

void doit (int bytes)
{
	char *buf;
	struct mallinfo mi;
	fprintf(stderr, "\n Allocating %10d bytes ----- \n", bytes); 
	buf = malloc(bytes);
	malloc_stats();
	mi = mallinfo();
	dump_mi(&mi);
	free(buf);
}

int main (int argc, char *args[])
{
	
	doit(13);
	doit(13 * 1024);
	doit(13 * 1024 * 1024);
	exit(0);
}
