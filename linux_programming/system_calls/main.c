#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

int main (int argc, char *args[])
{
	int pid;
	
	pid = syscall(SYS_getpid);
	
	printf("PID: %d", pid);
}
