#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define DEATH(mess) { perror(mess); exit(errno); }

void my_exit_fun_1(void)
{
	printf("I am in my_exit_fun_1\n");
}
void my_exit_fun_2(void)
{
	printf("I am in my_exit_fun_2\n");
}

int main (int argc, char *argv[])
{
	printf("beginning the atexit program .... \n");
	
	if (atexit(my_exit_fun_1) < 0)
	{
		DEATH("atexit");
	}
	printf("Installed my_exit_fun_1\n");
	
	if (atexit(my_exit_fun_2) < 0)
	{
		DEATH("atexit");
	}
	printf("Installed my_exit_fun_2\n");
	
	printf("Here, the program exits\n");
	
	exit(EXIT_SUCCESS);
}
