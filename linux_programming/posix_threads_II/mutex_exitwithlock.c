#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#define DEATH(mess) { perror(mess); exit(errno); }

static char running = 1;
static unsigned long counter = 0; /* if not volatile won't work when optimization is turned on */
static useconds_t micsec = 1000; /* say how much microseconds thread will sleep */
pthread_mutex_t c_mutex;
int i;

/* computational thread */
void *process(void *arg)
{
	while (running)
	{
		pthread_mutex_lock(&c_mutex);
		if (i > 4)
		{
			pthread_exit(NULL);
		}
		counter++;
		pthread_mutex_unlock(&c_mutex);
		usleep(micsec);
	}
	pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	pthread_t threadID;
	void *retval;
	
	pthread_mutex_init(&c_mutex, NULL);
	
	/*Start up the processing thread. */
	if (pthread_create(&threadID, NULL, process, "0"))
	{
		DEATH("pthread_create")
	}
	
	for (i = 0; i < 10; i++)
	{
		pthread_mutex_unlock(&c_mutex);
		pthread_mutex_lock(&c_mutex);
		printf("Counter: %lu, \n", counter);
		pthread_mutex_unlock(&c_mutex);
		fflush(stdout);
		sleep(1);
	}
	
	/* Tell the process thread to quit */
	running = 0;
	
	/* Wait for process thread to quit */
	if (pthread_join(threadID, &retval))
	{
		DEATH("pthread_join");
	}
	
	return 0;
}
