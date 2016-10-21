#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#define NUMSIGS 64

void sig_handler(int);

int sig_count[NUMSIGS + 1];
volatile static int line = 0;
volatile int signumbuf[6400], sigcountbuf[6400];

int main (int argc, char *argv[])
{
	sigset_t sigmask_new, sigmask_old;
	struct sigaction sigact, oldact;
	int signum, rc, i;
	pid_t pid;
	
	pid = getpid();
	
	/* block all posible signals */
	rc = sigfillset(&sigmask_new);
	rc = sigprocmask(SIG_SETMASK, &sigmask_new, &sigmask_old);
	
	/* Assign elements of sigaction structs */
	memset(&sigact, 0, sizeof(struct sigaction));
	sigact.sa_handler = sig_handler;
	sigact.sa_flags = 0;	/* no flags */
	sigact.sa_mask = sigmask_new;	/* block signals in the handler itself */
	
	/*
	 * Now, use sigaction to create reference to local signal
	 * handlers * and raise the signal to myself
	 */
	 
	printf("\n Installing signal handler and Raising signal for signal number:\n\n");
	for (signum = 1; signum <= NUMSIGS; signum++)
	{
		if (signum == SIGKILL || signum == SIGSTOP || signum == 32 || signum == 33)
		{
			printf(" Oops");
			continue;
		}
		
		sigaction(signum, &sigact, &oldact);
		
		/* send the signal to myself 3 times */
		rc = raise(signum);
		rc = raise(signum);
		rc = raise(signum);
		if (rc)
		{
			printf("Failed on signal %d\n", signum);
		}
		else
		{
			printf("%3d", signum);
			if (signum % 16 == 0 && signum != 0)
			{
				printf("\n");
			}
		}
	}
	
	fflush(stdout);
	
	/* restore original mask */
	rc = sigprocmask(SIG_SETMASK, &sigmask_old, NULL);
	
	printf("\nSignal Number (Times Procesed)\n");
	printf("***********************************************************\n");
	for (i = 0; i < NUMSIGS; i++)
	{
		printf("%4d:%1d", i, sigcountbuf[i]);
		if (i % 8 == 0 && signum != 0)
		{
			printf("\n");
		}
	}
	printf("\n");
	
	printf("\nHistory: Signal Number (Count Procesed)\n");
	printf("***********************************************************\n");
	for (i = 0; i < line; i++)
	{
		printf("%4d(%1d)", signumbuf[i], sigcountbuf[i]);
		if (i % 8 == 0)
		{
			printf("\n");
		}
	}
	
	printf("signals processed %d times", line);
	printf("\n");
	
	exit(0);
}

void sig_handler(int sig)
{
	sig_count[sig]++;
	signumbuf[line] = sig;
	sigcountbuf[line] = sig_count[sig];
	line++;
}
