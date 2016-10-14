#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define FILE_NAME "/etc/timezone"
#define BYTES_PL 16

#define DEATH(mess) { perror(mess); exit(errno); }

int main (int argc, char *args[])
{
	FILE *fp;
	int i = 0, start_addr = 0;
	char c;
	char *filename = FILE_NAME;
	
	if (argc > 1)
		filename = args[1];

	if (argc > 2)
		start_addr = atoi(args[2]);
	
	printf("\n ***** FILE IN HEX DUMP: %s, BYTES PER LINE: %d, AT OFFSET: %d (=0x%x) *****\n\n", filename, BYTES_PL, BYTES_PL, start_addr );
	
	if (!(fp = fopen(filename, "r")))
		DEATH(filename);
		
		
	if ((fseek(fp, start_addr, SEEK_SET)) == -1)
		DEATH(filename);
		
	printf("starting at 0x%x:\n", start_addr);
	
	while ((c = fgetc(fp)) != EOF)
	{
		printf("%2.2x-%c ", c, c); 
		if (i % BYTES_PL == 0 && i != 0)
			printf("\n");
		i++;
	}
	
	printf("\n");
	close(fp);
	exit(0);
}
