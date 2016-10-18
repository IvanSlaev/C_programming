#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
	printf("Starting the daemon");
	daemon(0, 0);
	pause();
	printf("got out of pause\n");
	exit(0);
}
