#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define DEATH(mess) { perror(mess); exit(errno); }

int main(int argc, const char *argv[])
{
	int length, fd1, rc;
	const char *nodename = "/dev/mycdrv";
	char message[] = "THIS MESSAGE IS USED AS TEST FOR THE CHARACTER DRIVER";

	length = sizeof(message);

	fd1 = open(nodename, O_RDWR);
	printf("%s%d\n", "first open file descriptor:", fd1);
	
	if (write(fd1, &message, length) < 0) 
	{
		printf("failed tio write on file descriptor %d\n", fd1);	
	}
	close(fd1);
	return 0;
}
