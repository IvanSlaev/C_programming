#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define DEATH(mess) { perror(mess); exit(errno); }

void print_quad(unsigned int x);

int main (int argc, char *argv[])
{
	struct hostent *hent;
	int i;
	struct in_addr addrh;
	char **tmp;
	
	if (argc < 2)
	{
		printf("USAGE: %s address, try again!\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	printf("Getting information on %s\n", argv[1]);
	
	if (!(hent = gethostbyname(argv[1])))
	{
		herror("Failed to get the host name");
		exit(EXIT_FAILURE);
	}
	
	printf("\nh_name\t = %s\n", hent->h_name);
	printf("h_addrtype\t = %d\n", hent->h_addrtype);
	printf("h_length\t = %d\n\n", hent->h_length);
	
	if (*hent->h_aliases)
	{
		for (i = 0, tmp = hent->h_aliases; *tmp != NULL; i++, tmp++)
		{
			printf("h_aliases[%d]  = %s\n", i, *tmp);
		}
	}
	else
		{
			printf("h_aliases[%d]  = %s\n", 0, "No aliases found!");
		}
	printf("\n");
		
	for (i = 0; hent->h_addr_list[i] != NULL; i++)
	{
		memcpy(&addrh, hent->h_addr_list[i], hent->h_length);
		printf("h_addr_list[%d] = ", i);
		print_quad(addrh.s_addr);
	}
	
	printf("\n");
	exit(EXIT_SUCCESS);
}

void print_quad(unsigned int x)
{
	unsigned char b1, b2, b3, b4;
	
	b4 = (x & 0xFF000000) >> 24;
	b3 = (x & 0x00FF0000) >> 16;
	b2 = (x & 0x0000FF00) >> 8;
	b1 = (x & 0x000000FF);
	
	printf("%02x %02x %02x %02x", b1, b2, b3, b4);
	printf("   %03d.%03d.%03d.%03d", b1, b2, b3, b4);
	printf("\n");
}
