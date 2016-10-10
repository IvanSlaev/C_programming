#include <stdio.h>
#include <stdlib.h>

int main () {

	int i, howMany;
	int sum;
	float average = 0.0;
	int * pointsArray;

	printf("How many?\n");
	scanf("%d", &howMany);

	pointsArray = (int *) malloc(howMany * sizeof(int));

	printf("So enter them mother fucker\n");

	for(i=0; i<howMany; i++)
	{
		scanf(" %d", &pointsArray[i]);
		sum += pointsArray[i];
	}
	
	average = (float)sum / (float)howMany;
	printf("Average is: %lf\n", average);
	
	return 0;
}
