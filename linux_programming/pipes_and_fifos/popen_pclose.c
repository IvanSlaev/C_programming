#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	int cntr;
	FILE *file_fp;
	char *string[] = { "echo", "bravo", "alpha", "charlie", "delta"};
	
	/* Create one way pipe line with call to popen() */
	if ((file_fp = popen("sort", "w")) == NULL)
	{
		perror("popen");
		exit(1);
	}
	for(cntr=0; cntr<5; cntr++)
	{
		fputs(string[cntr], file_fp);
		fputc('\n', file_fp);
	}
	/* Close the pipe */
	pclose(file_fp);
        
	return(0);
}
