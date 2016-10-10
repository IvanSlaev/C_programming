#include <stdio.h>

int main () {

	int balls[4] = {0, 1, 2, 3};

	printf("Element \t Address \t Value \n");
	
	int i;
	for(i=0; i<4; i++)
	{
		printf("balls[%d] \t %p \t %d \n", i, &balls[i], balls[i]);
	}

	printf("\nballs \t\t %p\n", balls);

	printf("\n*balls \t\t %d\n", *balls);

	printf("\n*(balls+2) \t %d\n", *(balls + 2));

	return 0;
}
