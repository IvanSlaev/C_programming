#include <stdio.h>
#include <stdlib.h>

static void take_char_array(char ca[])
{
	printf("Address of ca = \t%p\n", ca);
	printf("Address of &ca = \t%p\n", &ca);
	printf("Address of &(ca[0]) = \t%p\n", &(ca[0]));
	printf("Address of &(ca[1]) = \t%p\n", &(ca[1]));
	printf("Address of ++ca = \t%p\n", ++ca);
}

int main(int argc, const char *argv[])
{
	char arr[10] = "1234567890";
	take_char_array(arr);
	return 0;
}
