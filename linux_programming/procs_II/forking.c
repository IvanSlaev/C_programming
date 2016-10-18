#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define DEATH(mess) { perror(mess); exit(errno); }

int main (int argc, char *argv[])
{
	int wait_stat;
	pid_t pid, ch_pid;
	
	printf("\nNow we are going to fork a process\n");
	
	pid = fork();
	
	if (pid > 0)
	{
		printf("\nThis is the parent, after the fork. Child pid=%d, Parent pid=%d\n", pid, getpid());
		ch_pid = wait(&wait_stat);
		printf("ch_pid= %d\n", (int)ch_pid);
		printf("wait_stat= %d\n", wait_stat);
		if (WIFEXITED(wait_stat))
		{
			printf("\nChild exited with code %d\n", WIFEXITED(wait_stat));
		}
		else
		{
			printf("\nChild exited abnormally\n");
		}
		exit(EXIT_SUCCESS);
		
	}
	else if (pid == 0)
	{
		printf("\nThis is the child, after the fork. Child pid=%d, Parent pid=%d\n", getpid(), getppid());
		exit(EXIT_SUCCESS);
	}
	DEATH("fork");
}
