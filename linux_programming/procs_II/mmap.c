#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
{
	int fd = -1, size = 4096, status;
	char *area;
	pid_t pid;
	
	area = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, fd, 0);
	
	pid = fork();
	if (pid == 0)
	{
		printf("This is the child, please write down a sentence so that it can be read by the Parent\n");
		fgets(area, 4096, stdin);
		printf("Child has written: %s", area);
		exit(EXIT_SUCCESS);
	}
	if (pid > 0)
	{
		wait(&status);
		printf("Parent has read: %s", area);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
