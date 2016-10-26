#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>

#define DEATH(mess) { perror(mess); exit(errno); }

static char running = 1;
static unsigned long counter = 0; /* if not volatile won't work when optimization is turned on */
static useconds_t micsec = 1000; /* say how much microseconds thread will sleep */

sem_t c_sem;

/* computational thread */
void *process(void *arg)
{
	while (running)
	{
		sem_wait(&c_sem);
		counter++;
		sem_post(&c_sem);
		usleep(micsec);
	}
	pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	int i;
	pthread_t threadID;
	void *retval;
	sem_init(&c_sem, 0, 1);
	
	/*Start up the processing thread. */
	if (pthread_create(&threadID, NULL, process, "0"))
	{
		DEATH("pthread_create")
	}
	
	for (i = 0; i < 10; i++)
	{
		sem_wait(&c_sem);
		printf("Counter: %lu, \n", counter);
		sem_post(&c_sem);
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
