#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main (int argc, char *argv[])
{
	/*create file descriptors array*/
	int fd[2], nbytes;
	pid_t childpid;
	char readbuffer[100];
	char string[] = "You are my father?";
	
	pipe(fd);
	
	if ((childpid = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
	if (childpid == 0)
	{
                /* Child process closes up input side of pipe */
                close(fd[0]);

                /* Send "string" through the output side of pipe */
                write(fd[1], string, (strlen(string)+1));
                exit(0);
	}
	if (childpid > 0)
	{
		/* Parent process closes up output side of pipe */
                close(fd[1]);

                /* Read in a string from the pipe */
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("char: %lu\n", sizeof (char));
                printf("Child say: %s\n", readbuffer);
	}
}
