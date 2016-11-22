#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define DEATH(mess) { perror(mess); exit(errno); }

#define MAXIRQS 30
#define NB (MAXIRQS * sizeof(int))

int main(int argc, const char *argv[])
{
	int fd, i;
	int *interrupts = malloc(NB);
	char *nodename = "/dev/mycdrv";

	if ((fd = open(nodename, O_RDONLY)) < 0)
	{
		DEATH("opening failed");
	}
	if (read(fd, interrupts, NB) != NB) 
	{
		DEATH("reading failed");
	}

	for (i = 0; i < MAXIRQS; i++) 
	{
		if (interrupts[i] >= 0) 
		{
			 printf("%4d %10d\n", i, interrupts[i]);
	
		}
	}

	 exit(0);
}
