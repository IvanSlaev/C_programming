#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#define DEATH(mess) { perror(mess); exit(errno); }

void sig_act(int sig, siginfo_t *si, void *a)
{
	printf("In handler - PID: %d, SIGNAL: %d\n", getpid(), sig);
	
	printf("si_signo = \t%d\n", si->si_signo);
	printf("si_code = \t%d\n", si->si_code);
	printf("si_pid = \t%d\n", si->si_pid);
	printf("si_uid = \t%d\n", si->si_uid);
	printf("si_value = \t%d\n", si->si_value.sival_int);
	printf("si_int = \t%d\n", si->si_int);
}

int main (int argc, char *argv[])
{
	struct sigaction act;
	int i;
	union sigval sv;
	
	memset(&act, 0, sizeof(act));
	act.sa_sigaction = sig_act;
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &act, NULL) < 0)
	{
		DEATH("sigaction");
	}
	
	printf("pid=%d Successfully installed signal handler for SIGINT\n", getpid());
	
	for (i = 0; i < 3; i++)
	{
		printf("This is a pointless message\n");
		sv.sival_int = i * 100;
		printf("sigqueue returns %d\n", sigqueue(getpid(), SIGINT, sv));
		sleep(1);
	}
	exit(0);
}