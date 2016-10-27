#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <errno.h>

#define DEATH(mess) { perror(mess); exit(errno); }

int main (int argc, char *argv[])
{
	int sd, msg_len;
	char message [1024];
	struct sockaddr_un uaddr;
	
	uaddr.sun_family = AF_UNIX;
	strcpy(uaddr.sun_path, argv[1]);
	
	if ((sd = socket(PF_UNIX, SOCK_STREAM, 0) < 0))
	{
		printf("Can't open socket\n");
	}
	
	printf("Socket opened\n");
	
	if (connect(sd, (struct sockaddr *)&uaddr, sizeof(uaddr)))
	{
		DEATH("Can't connect to host");
	}
	
	printf("type a message\n");
	msg_len = strlen(fgets(message, 1024, stdin));
	
	if (write(sd, message, msg_len))
	{
		DEATH("Failed writing to the socket");
	}
	
	close(sd);
	exit(0);
}
