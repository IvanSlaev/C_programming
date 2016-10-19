#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void ouch(int sig)
{
	printf("OUCH! - I got a signal %d\n", sig);
	signal(sig, SIG_DFL);
}

int main (int argc, char *argv[])
{
	signal(SIGINT, ouch);
	while (1)
	{
		printf("Hello World\n");
		sleep(1);
	}
}
