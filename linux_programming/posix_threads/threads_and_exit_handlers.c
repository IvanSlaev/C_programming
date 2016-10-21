#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

void init_fun(void) __attribute__ ((constructor));
void exit_fun(void) __attribute__ ((destructor));

void init_fun(void)
{
	printf("Hello from init_fun\n");
}
void exit_fun(void)
{
	printf("Hello from exit_fun\n");
}

#define DEATH(mess) { perror(mess); exit(errno); }

volatile char running = 1;
volatile static unsigned long counter = 0; /* if not volatile won't work when optimization is turned on */
static useconds_t micsec = 1000; /* say how much microseconds thread will sleep */

/* computational thread */
void *process(void *arg)
{
	printf("Process init\n");
	while (running)
	{
		counter++;
		usleep(micsec);
	}
	printf("Process exit\n");
	pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	int i;
	pthread_t threadID;
	void *retval;
	
	printf("Main init\n");
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
	printf("Main exit\n");
	return 0;
}
