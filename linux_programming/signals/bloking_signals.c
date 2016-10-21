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
	printf("Program will abort only if a SIGQUIT signal come but only after I wake up!\n", sig);
	sleep(10);
	printf("OOOOOAAAh I woke up, now you can send me a SIGQUIT signal in order to abort the program!");
}
void sig_quit(int sig)
{
	printf("OK.OK.OK I received it, aborting now.\n", sig);
	abort();
}

int main (int argc, char *argv[])
{
	int rc;
	struct sigaction act_quit, act_int;
	sigset_t sigmask;
	
	memset(&act_quit, 0, sizeof(act_quit));
	memset(&act_int, 0, sizeof(act_int));
	
	/* set up signal mask to block SIGQUIT while SIGINT */
	rc = sigemptyset(&sigmask);
	printf("rc = %d from sigemptyset\n", rc);
	rc = sigaddset(&sigmask, SIGQUIT);
	printf("rc = %d from sigaddset\n", rc);
	
	/* install signal handlers */
	act_int.sa_handler = sig_int;
	act_int.sa_mask = sigmask; 
	if (sigaction(SIGINT, &act_int, NULL) < 0)
	{
		DEATH("sigaction, sig_int");
	}
	printf("SIGINT handler installed\n");
	
	act_quit.sa_handler = sig_quit;
	if (sigaction(SIGINT, &act_quit, NULL) < 0)
	{
		DEATH("sigaction, sig_quit");
	}
	printf("SIGQUIT handler installed\n");
	
	while (1)
	{
		printf("Come on, try to stop me!\n");
		sleep(1);
	}
}
