#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main (int argc, char *argv[])
{
	pid_t mypid, pid;
	int rc;
	
	/*info about myself*/
	mypid = getpid();
	printf("pgroup from getpgid(pid) = %d\n", getpgid(mypid));
	printf("pgroup from getpgrp() = %d\n", getpgrp());
	
	if (argc < 1)
	{
		exit(EXIT_FAILURE);
	}
	if ((pid = atoi(argv[1])) < 0)
	{
		printf("give a running pid as an #1 argument\n");
		exit(EXIT_FAILURE);
	}
	
	printf("pgroup for pid: %d = %d\n", pid, getpgid(pid));
	
	/*try to change the pgroup to my group*/
	
	rc = setpgid(pid, mypid);
	printf("rc from setpgid(pid, mypid): %d\n", rc);
	printf("pgroup for pid: %d = %d\n\n", pid, getpgid(pid));
	exit(EXIT_SUCCESS);
}
