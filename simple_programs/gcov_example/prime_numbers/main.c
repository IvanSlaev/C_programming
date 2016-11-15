#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, const char *argv[])
 
{
	int upper_limit = 0;
	int numberOfPrimes = 0;
	int i ,j;
	int never_executed = 0;

	if (argc > 1) 
	{
		upper_limit = atoi(argv[1]);
	}

	time_t t = clock();
	for(i = upper_limit - 1; i > 1; i--)
	{
		int flag = 0;
		for(j = 2; j < sqrt(i); j++)
		{
			if(i % j == 0)
			{
				flag = 1;
				break;
			}
		}
		if(flag == 0) 
			numberOfPrimes++;
		if(flag == 100)
			never_executed = 0;
	}

	printf("%s%d: %d\n", "Prime numbers within ", upper_limit, numberOfPrimes);
	printf("%s%lf s.\n", "Calculated in: ",(double)((double)clock() - t)/CLOCKS_PER_SEC);
	printf("never_executed = %d, must be 0\n", never_executed);
	return 0;
}
