#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <libaio.h>
#include <sys/stat.h>
#include <linux/aio_abi.h>

#define NBYTES 32
#define NBUF 100

#define DEATH(mess) { perror(mess); exit(errno); }

void printbufis(char **buf, int nbytes)
{
	int i;
	fflush(stdout);
	for (i = 0; i < NBUF; i++) 
	{
		write(STDOUT_FILENO, buf[i], nbytes);
		printf("\n");
	}
	printf("\n");
}

int main(int argc, const char *argv[])
{
	int fd, rc, i, k, nbytes = NBYTES, maxevents = NBUF;
	char *buf[NBUF], *filename = "/dev/mycdrv";
	struct iocb *iocbray[NBUF], *iocb;
	off_t offset;
	io_context_t ctx = 0;
	struct io_event events[2 * NBUF];
	struct timespec timeout = { 0, 0 };

	printf("Opening: %s\n", filename);
	if ((fd == open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) < 0) 
	{
		printf("Problem opening %s\n", filename);
		exit(-1);
	}

	for (i = 0; i < NBUF; i++) 
	{
		iocbray[i] = malloc(sizeof(struct iocb));
		buf[i] = malloc(nbytes);
		sprintf(buf[i], "%4d%4d", i, i);
		write(fd, buf[i], nbytes);
		memset(buf[i], 0, nbytes);
	}
	printf("\n");

	rc = io_setup(maxevents, &ctx);
	printf("rc from io_seput = %d\n", rc);
	printf("reading initial data from the file\n");

	for (i = 0; i < NBUF; i++) 
	{
		iocb = iocbray[i];
		offset = i * nbytes;
		io_prep_pread(iocb, fd, (void *)buf[i], nbytes, offset);
		rc = io_submit(ctx, 1, &iocb);
	}

	while ((rc = io_getevents(ctx, NBUF, NBUF, events, &timeout)) > 0) 
	{
		printf("rc from io_getevents on the write = %d\n", rc);
	}

	printbufs(buf, nbytes);

	rc = io_destroy(ctx);
	close(fd);
	exit(0);
}
