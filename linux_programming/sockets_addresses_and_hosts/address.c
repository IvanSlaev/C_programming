#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main (int argc, char *argv[])
{
	int rc;
	char *here;
	struct in_addr addr;
	
	if (argc < 2)
	{
		printf("USAGE: %s IP address, try again.\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	here = argv[1];
	printf("The original address is:            %s\n", here);
	
	if (!(rc = inet_aton(here, &addr)))
	{
		printf("inet_aton failed\n");
		exit(EXIT_FAILURE);
	}
	printf("From inet_aton: %x\n", ntohl(addr.s_addr));

	printf("From inet_addr: %x\n", inet_addr(here));
	
	printf("The return address from inet_ntoa is: %s\n", inet_ntoa(addr));
	
	exit(EXIT_SUCCESS);
}
