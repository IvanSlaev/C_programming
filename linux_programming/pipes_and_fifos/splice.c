#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#define DEATH(mess) { perror(mess); exit(errno); }

int main (int argc, char *argv[])
{
	char infile[128] = "./infile", outpipe[128] = "./outpipe";
	int rc, fd_in, fd_out, nbuf = INT_MAX;
	
	if (argc > 1)
	{
		strcpy(infile, argv[1]);
	}
	if (argc > 2)
	{
		strcpy(outpipe, argv[2]);
	}
	if (argc > 3)
	{
		nbuf = atoi(argv[3]);
	}
	
	printf("Input file: %s, Output file: %s\n", infile, outpipe);
	
	if ((fd_in = open(infile, O_RDONLY)) < 0)
	{
		DEATH("open fd_in");
	}
	if ((fd_out = open(outpipe, O_WRONLY)) < 0)
	{
		DEATH("open fd_out");
	}
	
	do
	{
		if ((rc = splice(fd_in, NULL, fd_out, NULL, nbuf, 0)) < 0)
		{
			DEATH("splice");
		}
		printf("Transferred %8d bytes\n", rc);
	} while (rc > 0);
	
	close(fd_in);
	close(fd_out);
	
	printf("DONE\n");
	return 0;
}
