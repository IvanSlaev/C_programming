#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

#define PORT_NUMBET 7177
#define MAX_NUM_CONNS 10000
#define MSG_MAXSIZE 1024
#define MAX_NWRITES 10
 
#define DEATH(mess) { perror(mess); exit(errno); }
#define GET_ELAPSED_TIME(tv1, tv2) ((double)((tv2.tv_sec - tv1.tv_sec) + .000001 * (tv2.tv_usec - tv1.tv_usec)))

int ncons = 3, *sdvec;
char message[MSG_MAXSIZE], hostname[1024];
int nwrites = MAX_NWRITES;

double open_socket(struct sockaddr_in addr)
{
	int i;
	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);
	for (i = 0; i < ncons; i++)
	{
		if ((sdvec[i] = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		{
			DEATH("socket");
		}
		printf("Open socket %d\n", sdvec[i]);
		if ((connect(sdvec[i], (struct sockaddr *)&addr, sizeof(struct sockaddr_in	))) == -1)
		{
			DEATH("connect");
		}
		printf("Connected to socket %d successfully\n", sdvec[i]);
		
		usleep(1000);
	}
	gettimeofday(&tv2, NULL);
	return GET_ELAPSED_TIME(tv1, tv2);
}

double write_random_socket(void)
{
	int i, k, count;
	struct timeval tv1, tv2;
	srand(getpid());
	
	gettimeofday(&tv1, NULL);
	
	for (k = 0; k < nwrites; k++)
	{
		i = rand() % ncons;
		
		sprintf(message, "Hi, I'm PID %d, socket %3d (k=%3d), on %s\n", getpid(), sdvec[i], k, hostname);
		send(sdvec[i], message, strlen(message), 0);
		count = recv(sdvec[i], message, MSG_MAXSIZE, 0);
		printf("Socket descriptor %d\n", sdvec[i]);
		fflush(stdout);
		write(STDOUT_FILENO, message, count);	
	}

	gettimeofday(&tv2, NULL);
	return GET_ELAPSED_TIME(tv1, tv2);
}

double close_socket(void)
{
	int i;
	struct timeval tv1, tv2;
	
	gettimeofday(&tv1, NULL);
	
	for (i = 0; i < ncons; i++)
	{
		close(sdvec[i]);
	}
	
	gettimeofday(&tv2, NULL);
	return GET_ELAPSED_TIME(tv1, tv2);
}


int main (int argc, char *argv[])
{
	double open_time, write_time, close_time, elapsed_time;
	struct sockaddr_in s_addr;
	struct hostent *s_hostent = NULL;
	struct rlimit rlp;
	
	if (argc > 2)
	{
		ncons = atoi(argv[2]);
	}
	if (ncons > MAX_NUM_CONNS)
	{
		ncons = MAX_NUM_CONNS;
	}
	if (argc > 3)
	{
		nwrites = atoi(argv[3]);
	}
	
	rlp.rlim_cur = rlp.rlim_max = ncons + 8;
	
	if (setrlimit(RLIMIT_NOFILE, &rlp) < 0)
	{
		DEATH("Failed to set max number of file descriptors, run as root\n");
	}
	
	gethostname(hostname, 128);
	
	printf("On %s, opening %d connections to %s with %d writes randomly distributed\n", hostname, ncons, argv[1], nwrites);
	
	memset(&s_addr, 0, sizeof(struct sockaddr_in));
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(PORT_NUMBET);
	
	if (!(s_hostent = gethostbyname(argv[1])))
	{
		DEATH("gethostbyname");
	}
	
	memcpy(&s_addr.sin_addr, s_hostent->h_addr, s_hostent->h_length);
	
	sdvec = malloc(ncons * sizeof(int));
	open_time = open_socket(s_addr);
	
	fprintf(stderr, "Opened %6d connections in %12f seconds, now going to fire %d writes\n", ncons, open_time, nwrites);
	
	write_time = write_random_socket();
	
	fprintf(stderr, "Finished %6d writes    in %12f seconds\n", nwrites, write_time);
	
	close_time = close_socket();
	
	fprintf(stderr, "Closed %6d writes    in %12f seconds\n", ncons, close_time);
	
	free(sdvec);
	
	elapsed_time = open_time + write_time + close_time;
	fprintf(stderr, "              TOTALS: %12f   %12f   %12f   %12f\n", open_time, write_time, close_time, elapsed_time);
	
	exit(EXIT_SUCCESS);
}
