#include <stdio.h>
#include <pthread.h>

pthread_t threads[3];
int coin_flip = 0;

static void *thread1(void *_)
{
	printf("Thread 1: %d \n", coin_flip);
} 

static void *thread2(void *_)
{
	printf("Thread 2: %d \n", coin_flip);
}

static void *thread3(void *_)
{
	printf("Thread 3: %d \n", coin_flip);
}

int main()
{
	pthread_create(&threads[0], NULL, thread1, NULL);
	pthread_create(&threads[1], NULL, thread2, NULL);
	pthread_create(&threads[2], NULL, thread3, NULL);
	
	pthread_exit(NULL);

	return 0;
}
