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
	
	umask(0);
	mknod(FIFO_FILE, S_IFIFO|0666, 0);
	
	while(1)
	{
		file = fopen(FIFO_FILE, "r");
		fgets(readbuff, 100, file);
		printf("Received string: %s", readbuff);
		fclose(file);
		sleep(10);
	}

	return(0);
}
