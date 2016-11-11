#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define DEATH(mess) { perror(mess); exit(errno); }

int main(int argc, const char *argv[])
{
	int length = 20, position = 0, fd, rc;
	char *message, *nodename = "/dev/mycdrv";

// the message
	message = malloc(length);
	memset(message, 'x', length);
	message[length - 1] = '\0';
// oppening device node
	fd = open(nodename, O_RDWR);
	printf("%s%d\n", "open file descriptor:", fd);
// seeking
	rc = lseek(fd, position, SEEK_SET);
	printf("%s%d\n", "Returned from lseek=", rc);
// writeing
	rc = write(fd, message, length);
	printf("%s%d%s%d\n", "return from write:", rc, " on file descriptor:", fd);
// reset message to null
	memset(message, 0, length);
// seeking
	rc = lseek(fd, position, SEEK_SET);
	printf("%s%d\n", "Returned from lseek=", rc);
// reading
	rc = read(fd, message, length);
	printf("%s%d%s%d\n", "return from read:", rc, " on file descriptor:", fd);
	printf("%s%s\n", "Message:", message);
	close(fd);
	return 0;
}
