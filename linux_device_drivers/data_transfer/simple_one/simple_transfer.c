#define _GNU_SOURCE
#define SECTOR_SIZE 512

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>

#define DEATH(mess) { perror(mess); exit(errno); }

int main(int argc, const char *argv[])
{
	void *buf;
	int fdin, fdout, rc_read, rc_write;
	int size = getpagesize();

	if (argc > 1) 
	{
		size = atoi(argv[1]);
	}

	printf("open input = %d\n", fdin = open("test_read", O_RDONLY));
	printf("open output = %d\n\n", fdout = open ("test_write", O_DIRECT | O_RDWR | O_CREAT | O_TRUNC, 0666));

	posix_memalign(&buf, SECTOR_SIZE, size);

	while ((rc_read = read(fdin, buf, size)) > 0) 
	{
		rc_write = write(fdout, buf, rc_read);
		printf("in = %d, out = %d\n", rc_read, rc_write);
		printf("%s\n", (char *)buf);
		if (rc_read != rc_write) 
		{
			printf("BAD value - sector not aligned\n");
		}
	}
	close(fdin);
	close(fdout);
	return 0;
}
