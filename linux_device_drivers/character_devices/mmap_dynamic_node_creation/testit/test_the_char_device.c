#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define DEATH(mess) { perror(mess); exit(errno); }

int main(int argc, const char *argv[])
{
	int length, fd1, fd2, rc;
	const char *nodename = "/dev/mycdrv";
	char message[] = "THIa MESSaGE IS USED aS TEST FOR THE CHARACTER DRIVER";

	length = sizeof(message);

	fd1 = open(nodename, O_RDWR);
	printf("%s%d\n", "first open file descriptor:", fd1);
	fd2 = open(nodename, O_RDWR);
	printf("%s%d\n", "second open file descriptor:", fd1);
	
	rc = write(fd1, message, length);
	printf("%s%d%s%d\n", "return from write:", rc, " on file descriptor:", fd1);
	memset(message, 0, length);
	
	rc = read(fd2, message, length);
	printf("%s%d%s%d\n", "return from read:", rc, " on file descriptor:", fd2);
	printf("%s%s\n", "Message:", message);
	return 0;
}
