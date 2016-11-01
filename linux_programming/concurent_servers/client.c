#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_PORT 7177
#define MAXLINE 1024
 
#define DEATH(mess) { perror(mess); exit(errno); }


int main (int argc, char *argv[])
{
	int sockfd, n;
	int maxfd;
	fd_set rset;
	struct sockaddr_in servaddr;
	char sendline[MAXLINE], buf[MAXLINE];
	
	//Create a socket for the client
	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Problem in creating the socket");
		exit(2);
	}
	
	//Creation of the socket
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(SERV_PORT); //convert to big-endian order
	
	//Connection of the client to the socket
	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("Problem in connecting to the server");
		exit(3);
	}
	
	FD_ZERO(&rset);
	FD_SET(STDIN_FILENO, &rset);
	FD_SET(sockfd, &rset);
	maxfd = sockfd;
	
	while (1)
	{
		int res = select(maxfd + 1, &rset, NULL, NULL, NULL);
		
			if (FD_ISSET(sockfd, &rset))
			{
				n = recv(sockfd, buf, MAXLINE, 0);
				write(1, buf, n);
				memset(buf, 0, sizeof(buf));
			}
			if (FD_ISSET(STDIN_FILENO, &rset))
			{
				fgets(buf, MAXLINE, STDIN_FILENO);
				send(sockfd, buf, strlen(buf), 0);
				memset(buf, 0, sizeof(buf));
			}
	}
	
	exit(0);
}
