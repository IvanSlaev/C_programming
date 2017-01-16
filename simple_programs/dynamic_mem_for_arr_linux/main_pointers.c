#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
	
	char * firstName;
	char * lastName;

	scanf("%ms %ms", &firstName, &lastName);
	printf("%s, %s\n", lastName, firstName);
	
	printf("size of firstName: %lu, size of lastName: %lu\n", strlen(firstName), strlen(lastName));
	
	free(firstName);
	free(lastName);
	
	return 0;
}
