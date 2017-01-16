#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
	int c = 0, count = 0;
	char firstName[20];
	char lastName[20];
	
	
	c = getchar();
	while (c != 0x0D || count < 10) {
		firstName[count++] = c;
		c = getchar();
	}
	
	count = 0;
	c = getchar();
	while (c != 0x0D || count < 10) {
		lastName[count++] = c;
		c = getchar();
	}
	
	int i;
	for (i = 0; i < 10; i++) {
		putchar((int)firstName[i]);
		if (i == 9) {
			printf("\n");
		}
	}
	for (i = 0; i < 10; i++) {
		putchar((int)lastName[i]);
		if (i == 9) {
			printf("\n");
		}

	}

	return 0;
}
