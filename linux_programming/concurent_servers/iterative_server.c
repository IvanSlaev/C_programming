#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERV_PORT 7177
#define MAXLINE 1024
#define LISTENQ 8 //max number of client connections

int main(int argc, char *argv[])
{
	int listenfd, connfd, n;
	int maxfd;
	fd_set rset;
	socklen_t clilen;
	char buf[MAXLINE], sendline[MAXLINE];
	struct sockaddr_in cliaddr, servaddr;
	
	//creation of the socket
	listenfd = socket(PF_INET, SOCK_STREAM, 0);
	
	//preparation of the socket address
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	
	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(listenfd, LISTENQ);
	printf("Server running... waiting for connection\n");
	
	FD_ZERO(&rset);
	FD_SET(STDIN_FILENO, &rset);
	FD_SET(listenfd, &rset);
	maxfd = listenfd;
	
	while (1)
	{
		int res = select(maxfd + 1, &rset, NULL, NULL, NULL);
		
			if (FD_ISSET(listenfd, &rset))
			{
				clilen = sizeof(cliaddr);
				connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
				n = recv(connfd, buf, MAXLINE,0);
				write(1, buf, n);
				memset(buf, 0, sizeof(buf));
				close(connfd);
			}
			if (FD_ISSET(STDIN_FILENO, &rset))
			{
				fgets(buf, MAXLINE, STDIN_FILENO);
				send(listenfd, buf, strlen(buf), 0);
				memset(buf, 0, sizeof(buf));
			}
	}
	
	close(listenfd);
}
