#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <signal.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>

int param = 0;

int slave(void *data)
{
	int i;
	printf("Starting off slave thread, pid=%d\n", getpid());
	for (i = 0; i < 10; i++)
	{
		param = i + 1000;
		sleep(1);
		printf("\nslave thread running: i=%d, param=%d secs, tid: %d\n", i, param, getpid());
	}
	printf("Slave thread saying goodbye\n");
	
	return 0;
}

int main (int argc, char **argv[])
{
	int i, tid, pagesize, stacksize;
	void *stack;
	
	printf("starting off master thread, pid=%d\n", getpid());
	
	pagesize = getpagesize();
	stacksize = 4 * pagesize;	
	
	posix_memalign(&stack, pagesize, stacksize);
	
	printf("Setting off a clone thread with stacksize: %d....\n", stacksize);
	tid = clone(slave, (char *)stack + stacksize - 1, SIGCHLD, 0);
	printf("with tid=%d", tid);
	if (tid < 0)
	{
		exit(1);
	}
	
	for (i = 0; i < 6; i++)
	{
		param = i;
		sleep(1);
		printf("\nmaster thread running: i=%d, param=%d secs, pid: %d\n", i, param, getpid());
	}
	
	printf("master killitself\n");
	free(stack);
	exit(0);
}
