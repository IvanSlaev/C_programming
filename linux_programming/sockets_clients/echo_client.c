#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define DEATH(mess) { perror(mess); exit(errno); }

int main (int argc, char *argv[])
{
	int sd, msg_len;
	char message [1024];
	struct sockaddr_in addr;
	struct hostent *hostent;
	
	if ((sd = socket(PF_INET, SOCK_STREAM, 0) < 0))
	{
		printf("Can't open socket\n");
	}
	
	printf("Socket opened\n");
	
	if (!(hostent = gethostbyname(argv[1])))
	{
		DEATH("Host info not obtained");
	}
	
	printf("Got the host just fine\n");
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(7);
	memcpy(&addr.sin_addr, hostent->h_addr, hostent->h_length);
	
	if (connect(sd, (struct sockaddr *)&addr, sizeof(addr)))
	{
		DEATH("Can't connect to host");
	}
	
	printf("type a message\n");
	msg_len = strlen(fgets(message, 1024, stdin));
	if (write(sd, message, msg_len))
	{
		DEATH("Failed writing to the socket");
	}
	
	memset(message, 0, 1024);
	
	printf("\nWe are going to read the same message back");
	
	msg_len = read(sd, message, 1024);
	
	if (msg_len < 0)
	{
		DEATH("Failed reading from the socket");
	}
	
	write(STDOUT_FILENO, message, msg_len);
	
	close(sd);
	exit(0);
}
