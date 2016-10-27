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
	strcpy(uaddr.sun_path, argv[1]);
	
	if ((sd = socket(PF_UNIX, SOCK_STREAM, 0) < 0))
	{
		DEATH("Can't open socket");
	}
	printf("Socket opened\n");
	
	servlen=strlen(uaddr.sun_path) + 
                     sizeof(uaddr.sun_family);
	if(bind(sd,(struct sockaddr *)&uaddr,servlen)<0)
       error("binding socket"); 

	printf("Binded successfully\n");
	
	listen(sd, 5);
	
	for (;;)
	{
		cd = accept(sd, NULL, &alen);
		rc = read (cd, message, sizeof(message));
		write(STDOUT_FILENO, message, rc);
		close(cd);
	}
	
	close(sd);
	exit(EXIT_SUCCESS);
}
