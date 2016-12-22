#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#define SIZE 2122
#define CHK 250

#define DEATH(mess) { perror(mess); exit(errno); }

int main(int argc, const char *argv[])
{
	int j, length, fd, rc;
	int vector[SIZE];
	off_t offset;

	length = sizeof(int) * SIZE;
	offset = sizeof(int) * CHK;
	fd = open("/dev/mybdrv", O_RDWR);

	for (j = 0; j < SIZE; j++) 
	{
		vector[j] = j;
	}

	rc = write(fd, vector, length);
	printf(" *** return code from write = %d\n", rc);

	rc = lseek(fd, offset, SEEK_SET);
	printf(" *** return code from lseek(%d) = %d\n", (int)offset, rc);
	
	rc = read(fd, vector + CHK, sizeof(int));
	printf(" *** return code from read vec[%d] = %d, vec[%d] = %d\n", CHK, rc, CHK, vector[CHK]);

	close(fd);

	return 0;
}
