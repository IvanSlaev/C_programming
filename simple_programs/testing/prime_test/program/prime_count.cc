#include <stdio.h>
#include <math.h>
#include "prime_count.h"

int GetCountOfPrimeNumbersWithin(int upper_limit)
 
{
	int numberOfPrimes = 0;
	int i ,j;

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
	}

	printf("%s%d: %d\n", "Prime numbers within ", upper_limit, numberOfPrimes);
	return 0;
}
