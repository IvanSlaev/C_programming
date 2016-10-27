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
	int sd, msg_len;
	char message[MSG_LEN];
	struct sockaddr_in addr;
	struct hostent *hostent;
	
	sd = socket(PF_INET, SOCK_STREAM, 0);
	
	hostent = gethostbyname(argv[1]);
	addr.sin_family = AF_INET;
	addr.sin_port = htons (PORT_NUMBER);
	memcpy(&addr.sin_addr, hostent->h_addr, hostent->h_length);
	
	connect(sd, (struct sockaddr *)&addr, sizeof(addr));
	
	msg_len = strlen(fgets(message, MSG_LEN, stdin));
	send(sd, message, MSG_LEN, 0);
	
	close(sd);
	exit(EXIT_SUCCESS);
}
