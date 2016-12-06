#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

#define DEATH(mess) { perror(mess); exit(errno); }

struct my_data {
	int i;
	long x;
	char s[256];
} my_data;

#define MYIOC_TYPE 'k'

int main(int argc, const char *argv[])
{
	int fd, rc;
	int MY_IOCTL;
	char *nodename = "/dev/mycdrv";
	if (argc > 1) 
	{
		nodename = argv[1];
	}

	fd = open(nodename, O_RDWR);
	printf("I opened the device node, file descriptor: %d\n", fd);

	//retrieve the original value
	MY_IOCTL = (int)_IOR(MYIOC_TYPE, 1, struct my_data);
	rc = ioctl(fd, MY_IOCTL, &my_data);
	printf("Reading from ioctl, rc = %d\n", rc);
	printf("my_data.i = %d, my_data.x = %d, my_data.s = %s\n", my_data.i, my_data.x, my_data.s);

	// Done reading
	// Now writing
	// but first let's fill the data structure
	my_data.i = 10;
	my_data.x = -700;
	strcpy(my_data.s, "a string");
	printf("Sending from user-space:\n");
	printf("my_data.i = %d, my_data.x = %d, my_data.s = %s\n", my_data.i, my_data.x, my_data.s);

	MY_IOCTL = (int)_IOW(MYIOC_TYPE, 1, struct my_data);
	rc = ioctl(fd, MY_IOCTL, &my_data);
	printf("Sending from user-space: rc = %d\n", rc);
	
	// reread the device and see what will come out
	MY_IOCTL = (int)_IOR(MYIOC_TYPE, 1, struct my_data);
	rc = ioctl(fd, MY_IOCTL, &my_data);
	printf("(re)Reading from ioctl, rc = %d\n", rc);
	printf("my_data.i = %d, my_data.x = %d, my_data.s = %s\n", my_data.i, my_data.x, my_data.s);
	close(fd);
	return 0;
}
