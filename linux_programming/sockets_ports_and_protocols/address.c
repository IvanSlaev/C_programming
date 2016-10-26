#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define HOST "localhost"
#define SERVICE "80"
#define PROT "ftp"


static int resolve(const char *host, const char *service, const char *proto, struct sockaddr_in *addr);

int main (int argc, char *argv[])
{
	char *host = HOST;
	char *service = SERVICE;
	char *protocol = PROT;
	struct sockaddr_in addr;
	unsigned short port;
	unsigned long address;
	int err;
	
	err = resolve(host, service, protocol, &addr);
	
	if (!err)
	{
		port = ntohs(addr.sin_port);
		address = ntohl(addr.sin_addr.s_addr);
		printf("sin_family = %12d\n", addr.sin_family);
		printf("sin_addr   = %12lu (0x%08lX) (%s)\n", address, address, inet_ntoa(addr.sin_addr));
		printf("sin_port   = %12hu (0x%08hX)\n", port, port);
	}
	
	return err;
}

static int resolve(const char *host, const char *service, const char *proto, struct sockaddr_in *addr)
{
	unsigned short port;
	struct hostent *hostentry = NULL;
	struct servent *serventry = NULL;
	extern int h_errno;
	
	addr->sin_family = AF_INET;
	
	if (!(hostentry = gethostbyname(host)))
	{
		herror(host);
		return h_errno;
	}
	memcpy(&addr->sin_addr, hostentry->h_addr, hostentry->h_length);
	
	port = (unsigned short)atoi(service);
	
	if (port > 0)
	{
		
		
		addr->sin_port = htons(port);
	}
	else
	{
		serventry = getservbyname(service, proto);
		
		if (serventry = NULL)
		{
			fprintf(stderr, "Failed in get service port");
			return 1;
		}
		addr->sin_port = serventry->s_port;
	}
	
	return 0;
}
