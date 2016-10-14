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
	int fd, bytes_read, i, start_addr = 0;
	unsigned char line[BYTES_PL];
	char *filename = FILE_NAME;
	
	if (argc > 1)
		filename = args[1];

	if (argc > 2)
		start_addr = atoi(args[2]);
	
	printf("\n ***** FILE IN HEX DUMP: %s, BYTES PER LINE: %d, AT OFFSET: %d (=0x%x) *****\n\n", filename, BYTES_PL, BYTES_PL, start_addr );
	
	if ((fd = open(filename, O_RDONLY)) < 0)
		DEATH(filename);
		
		
	if ((lseek(fd, start_addr, SEEK_SET)) == -1)
		DEATH(filename);
		
	printf("starting as 0x%x:\n", start_addr);
	
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
