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
	strcpy(uaddr.sun_path, "/tmp/mysock");
	
	sd = socket(PF_UNIX, SOCK_DGRAM, 0);
	
	msg_len = strlen(fgets(message, 1024, stdin));
	sendto(sd, message, msg_len, 0,(struct sockaddr *)&uaddr, sizeof(uaddr));

	close(sd);
	exit(0);
}
