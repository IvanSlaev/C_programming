#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#define DEATH(mess) { perror(mess); exit(errno); }

volatile char running = 1;
volatile static unsigned long counter = 0; /* if not volatile won't work when optimization is turned on */
static useconds_t micsec = 1000; /* say how much microseconds thread will sleep */

/* computational thread */
void *process(void *arg)
{
	while (running)
	{
		counter++;
		usleep(micsec);
	}
	pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	int i;
	pthread_t threadID;
	void *retval;
	
	/*Start up the processing thread. */
	if (pthread_create(&threadID, NULL, process, "0"))
	{
		DEATH("pthread_create")
	}
	
	for (i = 0; i < 10; i++)
	{
		printf("Counter: %lu, \n", counter);
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
