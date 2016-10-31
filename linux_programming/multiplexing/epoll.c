#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <sys/epoll.h>
#include <limits.h>


#define MAX_CONNS 10

struct my_data
{
	int fd;
	char *filename;
};

int main (int argc, char *argv[])
{
	int fd, epfd, nfd, nev, rfd, maxbytes, nbytes, maxevents, rc, i, timeout = INT_MAX;
	char *buffer, *filename;
	struct epoll_event ep_event[MAX_CONNS], *ep;
	struct my_data *tptr;
	
	if (argc < 2 || argc >= MAX_CONNS)
	{
		fprintf(stderr, "give at least one filename and not more than %d\n", MAX_CONNS);
		exit(-1);
	}
	
	nfd = argc - 1;
	maxevents = 4 * nfd;
	maxbytes = getpagesize() - 1;
	buffer = malloc(maxbytes - 1);
	
	epfd = epoll_create(nfd);
	printf("epfd from epoll_create - %d\n", epfd);
	
	for (i = 0; i < nfd; i++)
	{
		filename = argv[i+1];
		if ((fd = open(filename, O_RDONLY)) < 0)
		{
			fprintf(stderr, "Opening %s failed: %s\n", filename, strerror(errno));
			exit(1);
		}
		printf("Opened %s successfully\n", filename);
		
		tptr = malloc(sizeof(struct my_data));
		tptr->fd = fd;
		tptr->filename = filename;
		ep_event[i].data.ptr = tptr;
		ep_event[i].events = EPOLLIN;
		
		rc = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ep_event[i]);
		printf("rc from epoll_ctl = %d, for i=%d\n", rc, i);
		printf("fd = %d for filename = %s\n", fd, filename);
		
	}
	
	for (;;)
	{
		nev = epoll_wait(epfd, ep_event, maxevents, timeout);
		printf("nev from epoll_wait = %d\n", nev);
		
		for (i = 0; i < nev; i++)
		{
			ep = &ep_event[i];
			
			if (ep->events && EPOLLIN)
			{
				tptr = ep->data.ptr;
				rfd = tptr->fd;
				filename = tptr-> filename;
				
				nbytes = read(rfd, buffer, maxbytes);
				if (nbytes <= 0)
				{
					printf("Reached end of data, terminating\n");
					exit(-1);
				}
				printf("Got data: %2d:%10s: %s", rfd, filename, buffer);
			}
		}
	}
}
