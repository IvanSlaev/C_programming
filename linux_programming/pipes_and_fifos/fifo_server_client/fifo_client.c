#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/stat.h>

#define FIFO_FILE       "MYFIFO"

int main (int argc, char *argv[])
{
	FILE *file;
	char readbuff[100];
	
	if (argc < 1)
	{
		printf("USAGE: fifoclient [string]\n");
		exit(1);
	}
	if ((file = fopen(FIFO_FILE, "w")) == NULL)
	{
		perror("fifo not exist");
		printf("fifo not exist");
		exit(1);
	}
	
	fputs(argv[1], file);
		
	fclose(file);
	return(0);
}
