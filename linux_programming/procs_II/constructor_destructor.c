#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void constructor_fun1(void) __attribute__ ((constructor));
void constructor_fun2(void) __attribute__ ((constructor));
/* Imagine this is the program, from here going up is the direction 
 * constructors are invoking, and goind down is for destructors' invokation */ 
void destructor_fun1(void) __attribute__ ((destructor));
void destructor_fun2(void) __attribute__ ((destructor));

int main (int argc, char *argv[])
{
	printf("\nI am the program itself\n\n");
	exit(0);
}

void constructor_fun1(void)
{
	printf("I will start the programm - 1\n");
}
void constructor_fun2(void)
{
	printf("I will start the programm - 2\n");
}
void destructor_fun1(void)
{
	printf("I will finish the programm - 1\n");
}
void destructor_fun2(void)
{
	printf("I will finish the programm - 2\n");
}
