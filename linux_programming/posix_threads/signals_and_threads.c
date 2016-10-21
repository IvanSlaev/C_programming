#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#define DEATH(mess) { perror(mess); exit(errno); }

void *sigfun(void *args)
{
	int sigreceived;
	
	sigset_t sigmask;
	sigfillset(&sigmask);
	printf("Signal handling thread %ld starting\n", pthread_self());
	while (1)
	{
		sigwait(&sigmask, &sigreceived);
		printf("Signal Handling Thread %ld received signal %d\n", pthread_self(), sigreceived);
	}
	printf("Signal Handling Thread %ld exiting\n", pthread_self());
	pthread_exit(NULL);
}

void *fun(void *args)
{
	printf("		Thread %ld starting\n", pthread_self());
	pause();
	printf("		Thread %ld exiting\n", pthread_self());
	pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	int i;
	
	pthread_t threads[10];
	sigset_t sigmask;
	
	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGINT);
	pthread_sigmask(SIG_BLOCK, &sigmask, NULL);
	
	printf("Master thread id = %ld\n", (long)pthread_self());
	
	pthread_create(&threads[0], NULL, sigfun, NULL);
	printf("I created signal handling thread id=%ld\n", (long)threads[0]);
	
	for (i = 1; i < 10; i++)
	{
		pthread_create(&threads[i], NULL, fun, NULL);
		printf("I created thread %ld", (long)threads[i]);
	}
	
	sleep(1);
	printf("Sending SIGINT (Ctrl+C)\n");
	
	kill(getpid(), SIGINT);
	
	sleep(3);
	
	exit(0);
}
