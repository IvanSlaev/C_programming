#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#define DEATH(mess) { perror(mess); exit(errno); }

void sighand(int sig)
{
	printf("I'm executing signal handler in thread %ld\n", pthread_self());
}

void *fun(void *args)
{
	printf("Thread %ld starting\n", pthread_self());
	pause();
	printf("Thread %ld exiting\n", pthread_self());
	pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	int i;
	
	pthread_t threads[10];
	sigset_t sigmask;
	struct sigaction act;
	
	act.sa_handler = sighand;
	if (sigaction(SIGINT, &act, NULL) < 0)
	{
		printf("Failed to install signal handler\n");
		exit(-1);
	}
	
	printf("Master thread id = %ld\n", (long)pthread_self());
	
	for (i = 0; i < 10; i++)
	{
		pthread_create(&threads[i], NULL, fun, NULL);
	}
	
	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGINT);
	pthread_sigmask(SIG_BLOCK, &sigmask, NULL);
	
	for (i = 0; i < 10; i++)
	{
		kill(getpid(), SIGINT);
		sleep(1);
	}
	
	for (i = 0; i < 10; i++)
	{
		pthread_join(threads[i], NULL);
		printf("Master thread joined with thread %d\n", i);
	}
	
	exit(0);
}
