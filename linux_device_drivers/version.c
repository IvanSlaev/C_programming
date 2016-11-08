#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <linux/version.h>

#define DEATH(mess) { perror(mess); exit(errno); }

int main(int argc, const char *argv[])
{
	printf("LINUX_VERSION_CODE = %d\n", LINUX_VERSION_CODE);

	if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 0)) 
	{
		printf("%s\n", "Linux kernel version < 2.6");
	}
	else
	{
		printf("%s\n", "Linux kernel version > 2.6");
	}
	return 0;
}
