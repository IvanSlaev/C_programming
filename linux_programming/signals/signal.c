#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sig_int(int sig)
{
	printf("OUCH! - I got a SIGINT signal %d.\n", sig);
	printf("I will stop only if a SIGQUIT signal come.\n", sig);
}
void sig_quit(int sig)
{
	printf("OK.OK.OK I received it, aborting now.\n", sig);
	abort();
}

int main (int argc, char *argv[])
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
	while (1)
	{
		printf("Come on, try to stop me!\n");
		sleep(1);
	}
}
