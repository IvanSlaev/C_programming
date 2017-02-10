#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, const char *argv[])
{
	int length, fd, rc;
	const char *nodename = "/dev/mycdrv";
	char *message = NULL;
	int size = getpagesize();

	printf("page size: %d\n", size);

	fd = open(nodename, O_RDWR);
	printf("Open file descriptor fd: %d\n", fd);
	
	message = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (message == MAP_FAILED)
	{
		perror("mmap operation failed\n");
		return -1;
	}
	
	fgets(message, size, stdin);
	
	if (msync(message, 2 * size, MS_SYNC) != 0) {
		close(fd);
	}

	printf("message after msync: %s\n", message);	

	munmap(message, size);
	close(fd);

	return 0;
}
