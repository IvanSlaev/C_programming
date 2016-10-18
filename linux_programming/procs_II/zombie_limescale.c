#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define DEATH(mess) { perror(mess); exit(errno); }

int main (int argc, char *argv[])
{
	pid_t pid;
	
	printf("\nThis is the parent, about to fork. PID: %d\n", getpid());
	fflush(stdout);
	pid = fork();
	
	if (pid > 0)
	{
		printf("\nThis is the parent, after the fork. Child pid=%d, Parent pid=%d\n", pid, getpid());
		sleep(10);
		printf("\nThis is the parent, waking up and exiting\n", pid, getpid());
		exit(EXIT_SUCCESS);
	}
	else if (pid == 0)
	{
		printf("\nThis is the child, after the fork. Child pid=%d, Parent pid=%d\n", getpid(), getppid());
		exit(EXIT_SUCCESS);
	}
	DEATH("fork");
}
