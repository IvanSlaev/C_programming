#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define FILE_NAME "/etc/passwd"

#define BYTES_PL 16

#define DEATH(mess) { perror(mess); exit(errno); }

int main (int argc, char *args[])
{
	int fd, bytes_read, i;
	unsigned char line[BYTES_PL];
	char *filename = FILE_NAME;
	
	if (argc > 1)
		filename = args[1];
	
	printf("\n ***** FILE IN HEX DUMP: %s, BYTES PER LINE %d *****\n\n", filename, BYTES_PL);
	
	if ((fd = open(filename, O_RDONLY)) < 0)
		DEATH(filename);
		
	do 
	{
		if ((bytes_read = read (fd, line, BYTES_PL)) < 0)
			DEATH(filename);
			
		for (i = 0; i < bytes_read; i++)
		{
			printf("%2.2x ", line[i]);
		}
		
		printf("\n");
	}
	while (bytes_read > 0);
	
	close(fd);
	exit(0);
}
