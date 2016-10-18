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
		exit(EXIT_SUCCESS);
	}
	else if (pid == 0)
	{
		printf("\nThis is the child, after the fork. Child pid=%d, Parent pid=%d\n", getpid(), getppid());
		printf("My father is: %d\n", getppid());
		int x = 0;
		while (x < 20)
		{
			printf("%d\n", x);
			sleep(1);
			x++;
			if (x == 10)
			{
				printf("My father died, but init adopted me :)\n");
				printf("He is my father now, and his PID is: %d\n", getppid());
			}
		}
		printf("\nChild terminates.\n");
		exit(EXIT_SUCCESS);
	}
	DEATH("fork");
	return 0;
}
