#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <errno.h>

#define DEATH(mess) { perror(mess); exit(errno); }

int main (int argc, char *argv[])
{
	int sd, cd, rc, servlen;
	char message [1024];
	struct sockaddr_un uaddr;
	socklen_t alen = sizeof(struct sockaddr_un);
	
	unlink("/tmp/mysocket");
	uaddr.sun_family = AF_UNIX;
	strcpy(uaddr.sun_path, "/tmp/mysock");
	
	sd = socket(PF_UNIX, SOCK_DGRAM, 0);
	unlink("/tmp/mysock");
	bind(sd,(struct sockaddr *)&uaddr, sizeof(uaddr));

	for (;;)
	{
		rc = recvfrom (sd, message, sizeof(message), 0, (struct sockaddr *)&uaddr, &alen);
		write(STDOUT_FILENO, message, rc);
	}
	
	close(sd);
	exit(EXIT_SUCCESS);
}
