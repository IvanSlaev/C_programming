#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define DEATH(mess) { perror(mess); exit(errno); }

int main (int argc, char *argv[])
{
	struct sockaddr_un uaddr;
	int msg_len, sd;
	char message[1024];
	
	uaddr.sun_family = AF_UNIX;
	strcpy(uaddr.sun_path, "/tmp/mysock");
	
	sd = socket(PF_UNIX, SOCK_STREAM, 0);
	connect(sd, (struct sockaddr *)&uaddr, sizeof(uaddr));
	
	msg_len = strlen(fgets(message, 1024, stdin));
	send(sd, message, msg_len, 0);
	
	close(sd);
	exit(EXIT_SUCCESS);
}
