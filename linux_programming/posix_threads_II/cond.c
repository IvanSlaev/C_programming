#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_WORKERS 3

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static volatile int counter = 0, exiting = 0;

void *decrementer(void *arg)
{
	int counterVar;
	
	for (;;)
	{
		pthread_mutex_lock(&lock);
		while (!exiting && (counter <= 0))
		{
			pthread_cond_wait(&cond, &lock);
		}
		if (exiting)
		{
			pthread_mutex_unlock(&lock);
			pthread_exit(0);
		}
		
		counterVar = --counter;
		pthread_mutex_unlock(&lock);
		
		printf("Thread %ld decrementing to %d.\n", pthread_self(), counter);
		usleep(1000);
	}
	
}

int main (int argc, char *argv[])
{
	pthread_t threads[NUM_WORKERS];
	int i, val;
	
	for (i = 0; i < NUM_WORKERS; i++)
	{
		pthread_create(&threads[i], NULL, decrementer, NULL);
	}
	
	for (;;)
	{
		switch (scanf("%d", &val))
		{
			case 1:
				pthread_mutex_lock(&lock);
				counter += val;
				pthread_cond_broadcast(&cond);
				pthread_mutex_unlock(&lock);
				break;
				
			case EOF:
				pthread_mutex_lock(&lock);
				exiting = 1;
				pthread_cond_broadcast(&cond);
				pthread_mutex_unlock(&lock);
				for (i = 0; i < NUM_WORKERS; i++)
				{
					pthread_join(threads[i], NULL);
					printf("Thread %ld joined\n", threads[i]);
				}
				exit(0);
				
				break;
				
			default:
				fprintf(stderr, "You must enter number or EOF to end the program.\n");
				exit(1);
		}
	}
}
