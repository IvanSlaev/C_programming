#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#define DEATH(mess) { perror(mess); exit(errno); }

void sig_int(int sig)
{
	printf("OUCH! - I got a SIGINT signal %d. I will sleep for 10 sec\n", sig);
	printf("Program will abort only if a SIGQUIT signal come rather I am sleeping or not!\n", sig);
	sleep(10);
}
void sig_quit(int sig)
{
	printf("OK.OK.OK I received it, aborting now.\n", sig);
	abort();
}

int main (int argc, char *argv[])
{
	struct sigaction act;
	
	memset(&act, 0, sizeof(act));
	
	/* install handler for SIG_INT (Ctrl+C) */
	act.sa_handler = sig_int;
	if (sigaction(SIGINT, &act, NULL) < 0)
	{
		DEATH("sigaction, sig_int");
	}
	/* install handler for SIG_QUIT (Ctrl+\) */
	act.sa_handler = sig_quit;
	if (sigaction(SIGQUIT, &act, NULL) < 0)
	{
		DEATH("sigaction, sig_quit");
	}
	
	while (1)
	{
		printf("Come on, try to stop me!\n");
		sleep(1);
	}
}
