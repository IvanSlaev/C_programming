#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <errno.h>

#define SERV_PORT 7177
#define MAXLINE 1024
#define LISTENQ 8 //max number of client connections
#define DEATH(mess) { perror(mess); exit(errno); }

void *thread_handler(void *varfd)
{
	int n;
	char *buf;
	int connfd = *((int *)varfd);
	free(varfd);
	printf("Thread create for handling client \n");
	
	while ((n = recv(connfd, buf, MAXLINE,0)) > 0)
	{
		write(1, buf, n);
	}
	
	close(connfd);
	return NULL;
}

int main (int argc, char *argv[])
{
	int listenfd, *connectfd, backlog = 100, i = 0;
	struct sockaddr_in cliaddr, servaddr;
	socklen_t clilen;
	pthread_t thread;
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	
	listenfd = socket(PF_INET, SOCK_STREAM, 0);
	if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
	{
		DEATH("te tuka bace ne stana bainda");
	}
	
	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(listenfd, backlog);
	
	while (1)
	{
		clilen = sizeof(cliaddr);
		connectfd = malloc(sizeof(int));
		*connectfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
		
		pthread_create(&thread, NULL, thread_handler, connectfd);

        printf("Parent ready for another connection\n");
	}
	close(listenfd);
	exit(0);
}
