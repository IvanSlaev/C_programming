#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <sys/epoll.h>

#define MAX_CONNS 10

struct my_data
{
	int fd;
	char *filename;
};

int main (int argc, char *argv[])
{
	
	
	for (i = 1; i < argc; i++)
	{
		fd[i] = open(argv[i], O_RDONLY);
		if (fd[i] < 0)
		{
			fprintf(stderr, "Openning %s failed: %s\n", argv[i], strerror(errno));
			exit(0);
		}
		else
		{
			printf("Opened %s successfully\n", argv[i]);
		}
		FD_SET(fd[i], &permSet);
		
		if (fd[i] > maxFd)
		{
			maxFd = fd[i];
		}
	}
	
	for (;;)
	{
		testSet = permSet;
		
		i = select(maxFd + 1, &testSet, NULL, NULL, NULL);
		assert(i > 0);
		
		for (i = 0; i < argc; ++i)
		{
			if (FD_ISSET(fd[i], &testSet))
			{
				byteCount = read(fd[i], buffer, READ_AMT);
				assert(byteCount > 0);
				
				buffer[byteCount] = '\0';
				printf("Got data from %s: %s\n", argv[i], buffer);
			}
		}
	}
}
