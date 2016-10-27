#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define DEATH(mess) { perror(mess); exit(errno); }

int main (int argc, char *argv[])
{
	struct sockaddr_un uaddr;
	int sd, cd, rc;
	socklen_t alen = sizeof(struct sockaddr_un);
	char message[1024];
	
	uaddr.sun_family = AF_UNIX;
	strcpy(uaddr.sun_path, "/tmp/mysock");
	
	sd = socket(AF_UNIX, SOCK_STREAM, 0);
	unlink("/tmp/mysock");
	bind(sd, (struct sockaddr *)&uaddr, sizeof(uaddr));
	listen(sd, 5);
	
	for (;;)
	{
		cd = accept(sd, NULL, &alen);
		
		rc = recv(cd, message, sizeof(message), 0);
		write(STDOUT_FILENO, message, rc);
		sleep(1);
	}
	
	close(sd);
	exit(EXIT_SUCCESS);
	
}
