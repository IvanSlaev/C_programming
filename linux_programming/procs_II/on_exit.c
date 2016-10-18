#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define DEATH(mess) { perror(mess); exit(errno); }

void my_on_exit(void)
{
	printf("I am in my_on_exit func\n");
}

int main (int argc, char *argv[])
{
	int exit_code, arg1 = 1;
	
	if (argc > 1)
	{
		exit_code = atoi(argv[1]);
	}
	else
	{
		printf("Usage: %s exit_code\n", argv[0]);
		exit(1);
	}
	
	printf("beggining the on exit program\n");
	if (on_exit((void*)my_on_exit, &arg1) < 0)
	{
		DEATH("on_exit failed\n");
	}
	
	printf("on_exit installed\n");
	
	exit(exit_code);
}
