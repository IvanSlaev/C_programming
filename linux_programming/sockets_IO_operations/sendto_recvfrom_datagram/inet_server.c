#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define MSG_LEN 1024
#define PORT_NUMBER 7177
#define DEATH(mess) { perror(mess); exit(errno); }

int main (int argc, char *argv[])
{
	int sd, cd, rc, yes = 1;
	char message[MSG_LEN];
	struct sockaddr_in addr, con_addr;
	socklen_t alen = sizeof(struct sockaddr_in);
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT_NUMBER);
	
	sd = socket (PF_INET, SOCK_STREAM, 0);
	
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
	bind(sd, (struct sockaddr *)&addr, sizeof(addr));
	listen(sd, 5);
	
	for (;;)
	{
		printf("Accepting input on port: %d\n", PORT_NUMBER);
		cd = accept(sd, (struct sockaddr *)&con_addr, &alen);
		
		rc = recvfrom(cd, message, sizeof(message), 0, (struct sockaddr *)&con_addr, &alen);
		printf("Message: %s", message);
		
		printf("Receive the end of input\n");
		close(cd);
	}
	
	close(sd);
	exit(EXIT_SUCCESS);
}
