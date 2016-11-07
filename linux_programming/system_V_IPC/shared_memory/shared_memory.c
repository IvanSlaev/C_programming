#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define DEATH(mess) { perror(mess); exit(errno); }
#define SEGSIZE 1024

int open_segment(key_t keyval, int segsize)
{
	return shmget(keyval, segsize, IPC_CREAT | 0660);
}

char *attach_segment(int shmid)
{	
	return shmat(shmid, 0, 0);
}

void write_to_shm(int shmid, char *segptr, char *text)
{
	strcpy(segptr, text);
	printf("%s\n", "Done writing");
}

void read_from_shm(int shmid, char *segptr)
{
	printf("\n%s\n", segptr);
	printf("%s\n", "Done reading");
}

void remove_shm(int shmid, char *segptr)
{
	shmctl(shmid, IPC_RMID, 0);
	printf("%s\n", "Shared memory segment marked for deletion");
}

int main(int argc, const char *argv[])
{
	key_t key;
	int shmid, cntr;
	char *segptr;
	
	key = ftok(".", 'S');

	if ((shmid = shmget(key, SEGSIZE, IPC_CREAT|IPC_EXCL|0660)) == -1) 
	{
		printf("%s\n", "Shared memory segment exists. I will try to open is as a client");

		if ((shmid = shmget(key, SEGSIZE, 0)) == -1) 
		{
			printf("%s\n", "Problem opening even as a client");
			DEATH("shmget");
		}
	}
	printf("Shmid = %d\n", shmid);
	segptr = attach_segment(shmid); 
	
	// write to shared segment
	write_to_shm(shmid, segptr, "To be or not to be");
	sleep(10);
	// Read
	read_from_shm(shmid, segptr);
	sleep(10);
	printf("%s\n", "Sorry but I need to remove it. It must disappear because no process maps it anymore");
	remove_shm(shmid, segptr);
	return 0;
}
